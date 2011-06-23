#include "DirWatcher.h"
#include <crtdbg.h>
#include <process.h>

DirWatcher::DirWatcher(const TCHAR* pszDir, DirNotifyRoutine lpFun, DWORD dwFilter)
: mDir(INVALID_HANDLE_VALUE)
, mThreadHndler(INVALID_HANDLE_VALUE)
, mFilter(dwFilter)
, mNotifyRoutine(lpFun)
{
    _ASSERT(lpFun != NULL);

    mDir = CreateFile(pszDir, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
        NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);

    _ASSERT(mDir != INVALID_HANDLE_VALUE);
    _ASSERT(mNotifyRoutine != NULL);
}

DirWatcher::~DirWatcher(void)
{
    if (mDir != INVALID_HANDLE_VALUE)
    {
        CloseHandle(mDir);
    }
    if (mThreadHndler != INVALID_HANDLE_VALUE)
    {
        TerminateThread(mThreadHndler, 0L);
    }
}

bool DirWatcher::StartWatch()
{
    bool bRet = false;
    if (mThreadHndler != INVALID_HANDLE_VALUE)
    { 
        ResumeThread(mThreadHndler);       
        bRet = true;
    }
    else
    {
        if (mDir != INVALID_HANDLE_VALUE)
        {
            if (CreateWatchThread())
            {
                return StartWatch();
            }
        }
    }
    return bRet;
}
void DirWatcher::StopWatch()
{
    if (mThreadHndler != INVALID_HANDLE_VALUE)
    {
        TerminateThread(mThreadHndler, 0);
        mThreadHndler = INVALID_HANDLE_VALUE;
    }
}

bool DirWatcher::CreateWatchThread()
{
    mThreadHndler = (HANDLE)_beginthreadex(NULL, 0, WatcherRoutine, (void*)this,
        CREATE_SUSPENDED, 0);

    _ASSERT(mThreadHndler != INVALID_HANDLE_VALUE);

    return mThreadHndler != INVALID_HANDLE_VALUE;
}

unsigned int __stdcall DirWatcher::WatcherRoutine(LPVOID lpParams)
{
    DirWatcher* pWatcher = (DirWatcher*)lpParams;

    const int nLen = (sizeof(FILE_NOTIFY_INFORMATION) + MAX_PATH)*2;
    char pBytes[nLen] = {0};

    while(true)
    {
        DWORD dwBytesRet = 0L;
        BOOL bRet = ReadDirectoryChangesW(pWatcher->mDir,
            pBytes, nLen, TRUE, pWatcher->mFilter, &dwBytesRet, NULL, NULL);

        if (bRet && pWatcher->mNotifyRoutine)
        {
            FILE_NOTIFY_INFORMATION* pInfo = (FILE_NOTIFY_INFORMATION*)pBytes;
            pWatcher->mNotifyRoutine(pInfo);
        }      
    }

    return 0L;
}
