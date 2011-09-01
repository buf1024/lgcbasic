////////////////////////////////////////////////////////////////////////////////////////
// 
// GCLib -- Personal basic library project
// 
// FileName    : HashImpl.h
// Purpose     : 
// Version     : 2010-11-9 20:09:04 1.0 Created
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
/** @file HashImpl.h */

#ifndef _HASHIMPL_H_
#define _HASHIMPL_H_

#include <StdString.h>


class HashImpl
{
public:
    HashImpl(){}
    virtual ~HashImpl(){}
public:
    virtual StdString GetStringHash(std::string strValue) = 0;
    virtual StdString GetStringHash(std::wstring strValue) = 0;
    virtual StdString GetFileHash(StdString strFile) = 0;

};

#endif
