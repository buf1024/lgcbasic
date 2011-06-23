////////////////////////////////////////////////////////////////////////////////////////
// 
// GCLib -- Personal basic library project
// 
// FileName    : Hash.h
// Purpose     : 
// Version     : 2010-11-9 20:08:32 1.0 Created2-0
//             £º2011-06-5 11:11:11 1.1 Adjust basic common header usage
//                                      Remove namespace
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
/** @file Hash.h */

#ifndef _HASH_H_
#define _HASH_H_

#include <StdString.h>


class HashImpl;
/**
* The interface of some hash algorithm
*/
class Hash
{
public:
    /**
    * Constructor, provide some kind of implementation
    * @param pImpl The specific implementation
    */
    Hash(HashImpl* pImpl);
    ~Hash();
public:
    /**
    * Compute the ASCII form of string hash code
    * @param strValue The string need to compute
    * @return the correspond hash value
    */
    StdString GetStringHash(std::string strValue);
    /**
    * Compute the wide char form of string hash code
    * @param strValue The string need to compute
    * @return the correspond hash value
    */
    StdString GetStringHash(std::wstring strValue);
    /**
    * Compute the specific file hash code
    * @param strFile The file need to compute
    * @return the correspond hash value, if the file does not exist or errors occur return empty string
    */
    StdString GetFileHash(StdString strFile);
private:
    HashImpl* m_pImpl;

};

#endif
