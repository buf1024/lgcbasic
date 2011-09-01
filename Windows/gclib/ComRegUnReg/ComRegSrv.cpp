////////////////////////////////////////////////////////////////////////////////////////
// 
// GCLib -- Personal basic library project
// 
// FileName    : ComRegSrv.cpp
// Purpose     : 
// Version     : ?????????????????? 1.0 Created
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
#include "ComRegSrv.h"
#include "Reg.h"
#include <shlwapi.h>

#pragma comment(lib, "shlwapi.lib")

// Register the component in the registry.
//
HRESULT RegisterServer(const CLSID& clsid,					// Class ID
					   const StdString strFileName,		    // DLL module handle
					   const StdString strThreadingModel,	// ThreadingModel
					   const StdString strProgID,			//   IDs
					   const StdString strDescription)		// Description String
{
	HRESULT hRet = S_FALSE;
	if(!PathFileExists(strFileName.c_str()))	return hRet;
	
	TCHAR* pszBuf = NULL;
	hRet = StringFromCLSID(clsid, &pszBuf);
	//CLSID Not Right
	if (hRet != S_OK)
	{
		return hRet;
	}
	StdString strClsID = pszBuf;
	CoTaskMemFree(pszBuf);


	StdString strSubKey;
	StdString strValue;
	RegFactory* pFactory = NULL;
	RegNode* pNode = NULL;
	RegNode* pSubNode = NULL;

	pFactory = RegFactory::GetInstPtr();

	//CLSID
	strSubKey.append(_T("CLSID\\"));
	strSubKey.append(strClsID);
	strValue = strDescription;        //Description

	pNode = pFactory->CreateRegNode(HKEY_CLASSES_ROOT,	strSubKey.c_str(), true);
	pNode->AddRegData(REG_SZ, _T(""), strValue.c_str(), (strValue.length()+1)*sizeof(TCHAR));

	strSubKey = _T("InprocServer32");
	strValue = strFileName;					//InprocServer32
	pSubNode = pNode->AddNode(strSubKey.c_str());	
	_ASSERT(pSubNode != NULL);
	pSubNode->AddRegData(REG_SZ, _T(""), strValue.c_str(), (strValue.length()+1)*sizeof(TCHAR));

	if(!strThreadingModel.empty())
	{
		strSubKey = _T("ThreadingModel");
		strValue = strThreadingModel;		//ThreadingModel
		pSubNode->AddRegData(REG_SZ, strSubKey.c_str(), strValue.c_str(), (strValue.length()+1)*sizeof(TCHAR));
	}
	if (!strProgID.empty())
	{
		strSubKey = _T("ProgID");
		strValue = strProgID;
		pSubNode = pNode->AddNode(strSubKey.c_str()); //ProgID
		_ASSERT(pSubNode != NULL);
		pSubNode->AddRegData(REG_SZ, _T(""), strValue.c_str(), (strValue.length()+1)*sizeof(TCHAR));

		//ProgID
		strSubKey = strProgID;
		RegNode* pNodeProgID = pFactory->CreateRegNode(HKEY_CLASSES_ROOT, strSubKey.c_str(), true);
		_ASSERT(pNodeProgID != NULL);
		strValue = strDescription;        //Description
		pNodeProgID->AddRegData(REG_SZ, _T(""), strValue.c_str(), (strValue.length()+1)*sizeof(TCHAR));

		strSubKey = _T("CLSID");
		strValue = strClsID;
		pSubNode = pNodeProgID->AddNode(strSubKey.c_str()); //CLSID
		_ASSERT(pSubNode != NULL);
		pSubNode->AddRegData(REG_SZ, _T(""), strValue.c_str(), (strValue.length()+1)*sizeof(TCHAR));

		delete pNodeProgID;
	}
	delete pNode;
	RegFactory::ReleaseRC();

	return S_OK;
}


//
// Remove the component from the registry.
//
HRESULT UnregisterServer(const CLSID& clsid,				// Class ID
						 const StdString strProgID)		    //   IDs
{
	HRESULT hRet = S_FALSE;
	TCHAR* pszBuf = NULL;
	hRet = StringFromCLSID(clsid, &pszBuf);
	//CLSID Not Right
	if (hRet != S_OK)
	{
		return hRet;
	}
	StdString strSubKey = _T("CLSID\\");
	strSubKey += pszBuf;
	CoTaskMemFree(pszBuf);

	RegFactory* pFactory = RegFactory::GetInstPtr();
	RegNode* pClsID = pFactory->GetRegNode(HKEY_CLASSES_ROOT, strSubKey.c_str());
	RegNode* pProgID = pFactory->GetRegNode(HKEY_CLASSES_ROOT, strProgID.c_str());
	if (pClsID != NULL)
	{
		pClsID->DeleteNode();
		delete pClsID;
	}
	if(pProgID != NULL)
	{
		pProgID->DeleteNode();
		delete pProgID;
	}
	RegFactory::ReleaseRC();
	return S_OK;

}