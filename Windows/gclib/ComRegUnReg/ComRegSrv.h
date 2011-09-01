////////////////////////////////////////////////////////////////////////////////////////
// 
// GCLib -- Personal basic library project
// 
// FileName    : ComRegSrv.h
// Purpose     : 
// Version     : ?????????????????? 1.0 Created
//               2011-06-07 (10:11) 1.1 And some comment
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
/** @file ComRegSrv.h */
#pragma once
#include "StdString.h"
#include <Guiddef.h>

/**
 * Register the component in the registry.
 * @param clsid             Class ID
 * @param strFileName       DLL module handle
 * @param strThreadingModel ThreadingModel
 * @param strProgID         IDs
 * @param strDescription    Description String
 * @return S_OK if register successfully
 */
HRESULT RegisterServer(const CLSID& clsid,                  // Class ID
					   const StdString strFileName,         // DLL module handle
					   const StdString strThreadingModel,   // ThreadingModel
					   const StdString strProgID,           //   IDs
					   const StdString strDescription);     // Description String


/**
 * Remove the component from the registry.
 * @param clsid             Class ID
 * @param strProgID         IDs
 * @return S_OK if register successfully
 */
HRESULT UnregisterServer(const CLSID& clsid,                // Class ID
						 const StdString strProgID);        //   IDs

