////////////////////////////////////////////////////////////////////////////////////////
// 
// 
// FileName    : DirWatcher.h
// Purpose     : Watch the changes of some directory
// Version     : 2011-05-31 (19:46) 1.0 Created
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
/** @file DirWatcher.h */
#pragma once

#include <Windows.h>
/** Callback function. The parameter is FILE_NOTIFY_INFORMATION structure.
 * 
 * FILE_ACTION_ADDED                The file was added to the directory.
 * FILE_ACTION_REMOVED              The file was removed from the directory.
 * FILE_ACTION_MODIFIED             The file was modified. This can be a change
 *                                  in the time stamp or attributes.
 * FILE_ACTION_RENAMED_OLD_NAME The file was renamed and this is the old name.
 * FILE_ACTION_RENAMED_NEW_NAME The file was renamed and this is the new name.
 */
typedef void (*DirNotifyRoutine)(LPVOID);

/** Directory watcher class */
class DirWatcher
{
public:
    /** Construct a watcher object
     *
     * @param pszDir    the directory the want to watch
     * @param lpFun     the callback function when directory chanage
     * @param dwFilter  the filter of the watch option
     * 
     * FILE_NOTIFY_CHANGE_FILE_NAME     Any file name change in the watched directory or subtree
     *                                  causes a change notification wait operation to return.
     *                                  Changes include renaming, creating, or deleting a file.
     * FILE_NOTIFY_CHANGE_DIR_NAME      Any directory-name change in the watched directory or subtree
     *                                  causes a change notification wait operation to return. Changes
     *                                  include creating or deleting a directory.
     * FILE_NOTIFY_CHANGE_ATTRIBUTES    Any attribute change in the watched directory or subtree
     *                                  causes a change notification wait operation to return.
     * FILE_NOTIFY_CHANGE_SIZE          Any file-size change in the watched directory or subtree
     *                                  causes a change notification wait operation to return. The
     *                                  operating system detects a change in file size only when the
     *                                  file is written to the disk. For operating systems that use
     *                                  extensive caching, detection occurs only when the cache is
     *                                  sufficiently flushed.
     * FILE_NOTIFY_CHANGE_LAST_WRITE    Any change to the last write-time of files in the watched
     *                                  directory or subtree causes a change notification wait
     *                                  operation to return. The operating system detects a change to
     *                                  the last write-time only when the file is written to the disk.
     *                                  For operating systems that use extensive caching, detection
     *                                  occurs only when the cache is sufficiently flushed.
     * FILE_NOTIFY_CHANGE_LAST_ACCESS   Any change to the last access time of files in the watched
     *                                  directory or subtree causes a change notification wait operation
     *                                  to return.
     * FILE_NOTIFY_CHANGE_CREATION      Any change to the creation time of files in the watched
     *                                  directory or subtree causes a change notification wait operation
     *                                  to return.
     * FILE_NOTIFY_CHANGE_SECURITY      Any security-descriptor change in the watched directory or
     *                                  subtree causes a change notification wait operation to return.
     */
    DirWatcher(const TCHAR* pszDir, DirNotifyRoutine lpFun,
        DWORD dwFilter =
        FILE_NOTIFY_CHANGE_FILE_NAME    |  
        FILE_NOTIFY_CHANGE_DIR_NAME     |  
        FILE_NOTIFY_CHANGE_ATTRIBUTES   |  
        FILE_NOTIFY_CHANGE_SIZE         |  
        FILE_NOTIFY_CHANGE_LAST_WRITE   |  
        FILE_NOTIFY_CHANGE_LAST_ACCESS  |  
        FILE_NOTIFY_CHANGE_CREATION     |  
        FILE_NOTIFY_CHANGE_SECURITY);
    ~DirWatcher(void);

public:
    /** Start a new thread to watch 
     *
     * @return true if start watcher, false otherwise
     */
    bool StartWatch();
    /** Stop watch */
    void StopWatch();

private:
    bool CreateWatchThread();

private:
    static unsigned int __stdcall WatcherRoutine(LPVOID lpParams);

private:
    HANDLE              mDir;
    HANDLE              mThreadHndler;
    DWORD               mFilter;
    DirNotifyRoutine    mNotifyRoutine;
};
