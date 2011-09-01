//=============================================================================
/**
* @file	    Reg.cpp
* @brief	
* @author	heidong
* @version	1.0
* @date		2010-10-15 20:16:53
*/
//=============================================================================
#include "Reg.h"
#include <algorithm>
#include <shlwapi.h>

#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "shlwapi.lib")


//=============================================================================
//RegData
RegData::RegData()
: m_nType(0)
, m_strKeyName(_T(""))
, m_pRegData(NULL)
, m_nLength(0)
{
	
}
RegData::~RegData()
{
	if (m_pRegData)
	{
		delete[] m_pRegData;
	}
	
}
RegData::RegData(const RegData& other)
{
	*this = other;
}
RegData& RegData::operator = (const RegData& other)
{
	if (*this != other)
	{
		m_nType = other.m_nType;
		m_nLength = other.m_nLength;
		m_strKeyName = other.m_strKeyName;

		if(m_pRegData)
		{
			delete[] m_pRegData;
		}
		if (other.m_pRegData == NULL)
		{		
			m_pRegData = NULL;
		}
		else
		{
			m_pRegData = new CHAR[m_nLength];
			memcpy(m_pRegData, other.m_pRegData, m_nLength);
		}
	}
	return *this;
}

bool RegData::operator == (const RegData& other)
{
	bool bRet = false;
	if (m_strKeyName == other.m_strKeyName)
	{
		bRet = true;		
	}
	return bRet;
}
bool RegData::operator != (const RegData& other)
{
	return !(*this == other);
}


void RegData::SetValue(DWORD dwType, const StdString strKey, const void* pData, DWORD dwDataLen)
{
	SetDataType(dwType);
	SetKeyName(strKey);
	SetData(pData, dwDataLen);
}
bool RegData::IsDataValid() const
{
	return (m_nLength != 0 && m_pRegData != NULL);
}

void RegData::SetDataType(DWORD nType)
{
	m_nType = nType;
}
DWORD RegData::GetDataType() const
{
	return m_nType;
}

void RegData::SetKeyName(const StdString strKeyName)
{
	m_strKeyName = strKeyName;
}
StdString RegData::GetKeyName() const
{
	return m_strKeyName;
}

void RegData::SetData(const VOID* pData, DWORD dwLength)
{
	if (m_pRegData)
	{
		delete[] m_pRegData;
	}
	SetDataLength(dwLength);
	m_pRegData = new BYTE[m_nLength];
	memcpy(m_pRegData, pData, m_nLength);
}
const VOID* RegData::GetData() const
{
	return m_pRegData;
}

void RegData::SetDataLength(DWORD nLength)
{
	m_nLength = nLength;
}
DWORD RegData::GetDataLength() const
{
	return m_nLength;
}
//=============================================================================
//RegDataCompare
template <typename TheClass>
bool RegDataCompare<TheClass>::operator ()(TheClass* pLeft, TheClass* pRight) const
{
	bool bRet = false;
	if (pLeft && pRight)
	{
		bRet = (*pLeft == *pRight);
	}
	else
	{
		if (!pLeft && !pRight)
		{
			bRet = true;
		}
	}
	return bRet;
}
//=============================================================================
//RegNode
RegNode::RegNode(HKEY hRootKey, StdString strCurSubKey, HKEY hKey, bool bUpdate)
: m_hRootKey(hRootKey)
, m_hKey(hKey)
, m_strSubKey(strCurSubKey)
, m_bUpdate(bUpdate)
{
	m_lstRegData.clear();
	m_mapRegNode.clear();
	InitData();

}
RegNode::~RegNode()
{
	if (m_bUpdate)
	{
		Save();
	}
	ClearUp();
}
bool RegNode::AddRegData(RegData* pRegData, bool bOverwrite)
{
	if(!IsValid()) return false;
	bool bRet = false;	
	if (pRegData)
	{
		REGDataIterator iter = std::find_if(m_lstRegData.begin(), m_lstRegData.end(),
			std::bind2nd(RegDataCompare<RegData>(), pRegData));
		if (iter != m_lstRegData.end())
		{
			if (bOverwrite)
			{
				delete *iter;
				m_lstRegData.erase(iter);
				m_lstRegData.push_back(pRegData);
				bRet = true;
			}
		}
		else
		{
			m_lstRegData.push_back(pRegData);
			bRet = true;
		}
		
	}
	return bRet;
}

bool RegNode::AddRegData(DWORD dwType, const StdString strKey, const void* pData, DWORD dwDataLen, bool bOverwrite)
{
	RegData* pNodeData = new RegData;
	pNodeData->SetValue(dwType, strKey, pData, dwDataLen);
	bool bRet = AddRegData(pNodeData, bOverwrite);
	if(bRet == false) delete pNodeData;
	return bRet;
}

bool RegNode::GetRegData(const StdString strKey, RegData& regData)
{
	if(!IsValid()) return false;
	bool bRet = false;

	for(REGDataIterator iter = m_lstRegData.begin();
		iter != m_lstRegData.end(); ++iter)
	{
		const StdString strTmp = (*iter)->GetKeyName();
		if(strTmp == strKey)
		{
			regData = *(*iter);
			bRet = true;
			break;
		}

	}
	return bRet;
}


void RegNode::InitData()
{
	
	DWORD dwMaxValueNameLen;
	DWORD dwMaxValueLen;
	DWORD dwMaxKeyNameLen;
	if (RegQueryInfoKey(m_hKey, NULL, NULL, NULL, NULL, &dwMaxKeyNameLen, NULL, NULL,
		&dwMaxValueNameLen, &dwMaxValueLen, NULL, NULL) == ERROR_SUCCESS)
	{
		
		DWORD dwIdex = 0L;
		DWORD dwType;
		TCHAR* pszValueName = new TCHAR[dwMaxValueNameLen + 1]; 
		BYTE* pbData = new BYTE[dwMaxValueLen];
		LONG lRet;
		
		//Value
		DWORD dwValueNameLen = dwMaxValueNameLen + 1;
		DWORD dwByteLen = dwMaxValueLen;
		do
		{
			lRet = RegEnumValue(m_hKey, dwIdex++, pszValueName, &dwValueNameLen,
				NULL, &dwType, pbData, &dwByteLen);
			if (lRet != ERROR_NO_MORE_ITEMS)
			{
				dwValueNameLen = dwMaxValueNameLen + 1;
				dwByteLen = dwMaxValueLen;

				RegData* pNodeData = new RegData;
				pNodeData->SetValue(dwType, pszValueName, pbData, dwByteLen);
				AddRegData(pNodeData);
			}
			
		}while(lRet != ERROR_NO_MORE_ITEMS);
		delete[] pszValueName;
        delete[] pbData;

		//Key
		if (dwMaxKeyNameLen > 0)
		{
			dwIdex = 0L;
			TCHAR* pszKeyName = new TCHAR[dwMaxKeyNameLen + 1]; 		
			DWORD dwKeyNameLen = dwMaxKeyNameLen + 1;
			do
			{			
				lRet = RegEnumKeyEx(m_hKey, dwIdex++, pszKeyName, &dwKeyNameLen,
					NULL, NULL, NULL, NULL);
				if (lRet != ERROR_NO_MORE_ITEMS)
				{
					m_mapRegNode.insert(std::make_pair(pszKeyName, (RegNode *)NULL));
					dwKeyNameLen = dwMaxKeyNameLen + 1;
				}

			}while(lRet != ERROR_NO_MORE_ITEMS);
			delete[] pszKeyName;
		}

	}
}

bool RegNode::Save()
{
	if(!IsValid()) return false;
	bool bRet = true;
	for (REGDataIterator iter = m_lstRegData.begin();
		iter != m_lstRegData.end(); ++iter)
	{
		if (RegSetValueEx(m_hKey, (*iter)->GetKeyName().c_str(), 0L,
			(*iter)->GetDataType(), (const BYTE*)(*iter)->GetData(),
			(*iter)->GetDataLength()) != ERROR_SUCCESS)
		{
			bRet = false;
			break;
		}
	}
	if (bRet)
	{
		for(REGNodeIterator iter = m_mapRegNode.begin();
			iter != m_mapRegNode.end(); ++iter)
		{
			RegNode* pNode = iter->second;
			if ( pNode != NULL)
			{
				if (pNode->Save() == false)
				{
					bRet = false;
					break;
				}
			}
		}
	}	
	return bRet;
}

RegNode* RegNode::GetNode(const StdString strKey)
{
	if(!IsValid()) return NULL;
	RegNode* pNode = NULL;
	if (!strKey.empty())
	{
		REGNodeIterator iter;
		for(iter = m_mapRegNode.begin();
			iter != m_mapRegNode.end(); ++iter)
		{
			if (iter->first == strKey)
			{
				if (iter->second == NULL)
				{
					HKEY hKeyRet;
					if(RegOpenKeyEx(m_hKey, strKey.c_str(), 0, KEY_ALL_ACCESS, &hKeyRet) != ERROR_FILE_NOT_FOUND)
					{
						StdString subKey(m_strSubKey);
						subKey.append(_T("\\"));
						subKey.append(strKey);
						RegNode* pNodeData = new RegNode(m_hRootKey, subKey, hKeyRet, m_bUpdate);
						m_mapRegNode[iter->first] = pNodeData;
					}
				}
				pNode = m_mapRegNode[iter->first];
				break;
			}
		}
		if (iter == m_mapRegNode.end())
		{
			HKEY hKeyRet;
			if(RegOpenKeyEx(m_hKey, strKey.c_str(), 0, KEY_ALL_ACCESS, &hKeyRet) != ERROR_FILE_NOT_FOUND)
			{
				StdString subKey(m_strSubKey);
				subKey.append(_T("\\"));
				subKey.append(strKey);
				RegNode* pNodeData = new RegNode(m_hRootKey, subKey, hKeyRet, m_bUpdate);
				m_mapRegNode.insert(std::make_pair(strKey, pNodeData));
				pNode = pNodeData;
			}
		}
	}
	return pNode;
}
//2011-01-09
int RegNode::GetNodes(std::list<RegNode*>& rgpNodes)
{
    rgpNodes.clear();
    std::list<StdString> rgpKeys;
    GetGroupKeys(rgpKeys);
    for(std::list<StdString>::iterator iter = rgpKeys.begin();
        iter != rgpKeys.end(); ++iter)
    {
        RegNode* pNode = GetNode(*iter);
        if (pNode)
        {
            rgpNodes.push_back(pNode);
        }
    }
    return rgpNodes.size();

}
//2011-01-09

RegNode* RegNode::AddNode(const StdString strKey)
{
	if(!IsValid()) return NULL;
	RegNode* pNode = NULL;
	pNode = GetNode(strKey);
	if (pNode == NULL)
	{
		HKEY hRetKey;
		if (RegCreateKeyEx(m_hKey, strKey.c_str(), 0L, NULL,
			REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hRetKey, NULL) == ERROR_SUCCESS)
		{
			StdString subKey(m_strSubKey);
			subKey.append(_T("\\"));
			subKey.append(strKey);			
			RegNode* pNodeData = new RegNode(m_hRootKey, subKey, hRetKey, m_bUpdate);
			m_mapRegNode.insert(std::make_pair(strKey, pNodeData));
			pNode = pNodeData;
		}
	}
	return pNode;
}

bool RegNode::DeleteNode(const StdString strKey)
{
	if(!IsValid()) return false;
	bool bRet = false;
	if (!strKey.empty())
	{
		bool bDelete = false;
		REGNodeIterator iter;
		for(iter = m_mapRegNode.begin();
			iter != m_mapRegNode.end(); ++iter)
		{
			if (strKey == iter->first)
			{
				bRet = SHDeleteKey(m_hKey, strKey.c_str()) == ERROR_SUCCESS;
				if (iter->second != NULL)
				{
					delete iter->second;
				}
				m_mapRegNode.erase(iter);
				bDelete = true;
				break;
			}
		}
		if (bDelete == false)
		{
			bRet = SHDeleteKey(m_hKey, strKey.c_str()) == ERROR_SUCCESS;
		}
	}
	else
	{
		bRet = SHDeleteKey(m_hRootKey, m_strSubKey.c_str()) == ERROR_SUCCESS;
		ClearUp();
	}
	return bRet;
}

void RegNode::ClearUp()
{
	if(!IsValid()) return;

	RegCloseKey(m_hKey);
	m_hKey = NULL;

	for(REGDataIterator iter = m_lstRegData.begin();
		iter != m_lstRegData.end(); ++iter)
	{
		delete *iter;
	}
	m_lstRegData.clear();

	for(REGNodeIterator iter = m_mapRegNode.begin();
		iter != m_mapRegNode.end(); ++iter)
	{
		if (iter->second)
		{
			delete iter->second;
		}
		
	}
	m_mapRegNode.clear();
}

StdString RegNode::GetRelativeSubKey()
{
	return m_strSubKey;
}
HKEY RegNode::GetRootHKEY()
{
	return m_hRootKey;
}
HKEY RegNode::GetCurrentHKEY()
{
	return m_hKey;
}

bool RegNode::IsValid() const
{
	return m_hKey != NULL;
}

bool RegNode::GetDestroySave()
{
	return m_bUpdate;
}
void RegNode::SetDestroySave(bool bUpdate)
{
	m_bUpdate = bUpdate;
}


int RegNode::GetGroupKeys(std::list<StdString>& rgpKeys)
{
    rgpKeys.clear();
    for(REGNodeIterator iter = m_mapRegNode.begin();
        iter != m_mapRegNode.end(); ++iter)
    {
        rgpKeys.push_back(iter->first);
    }
    return rgpKeys.size();
}
int RegNode::GetNodeKeys(std::list<StdString>& rgpKeys)
{
    rgpKeys.clear();
    for(REGDataIterator iter = m_lstRegData.begin();
        iter != m_lstRegData.end(); ++iter)
    {
        rgpKeys.push_back((*iter)->GetKeyName());
    }
    return rgpKeys.size();
}
//=============================================================================
//RegFactory
RegNode* RegFactory::CreateRegNode(HKEY hKey, const StdString strSubKey, bool bUpdate)
{
	RegNode* pNode = NULL;
	HKEY hKeyRet;
	DWORD dwType;		
	if (RegCreateKeyEx(hKey, strSubKey.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS, NULL, &hKeyRet, &dwType) == ERROR_SUCCESS)
	{

		pNode = new RegNode(hKey, strSubKey, hKeyRet, bUpdate);

	}
	return pNode;
}

RegNode* RegFactory::GetRegNode(HKEY hKey, const StdString strSubKey, bool bUpdate)
{
	RegNode* pNode = NULL;
	HKEY hKeyRet;

	if (RegOpenKeyEx(hKey, strSubKey.c_str(), 0, KEY_ALL_ACCESS, &hKeyRet) != ERROR_FILE_NOT_FOUND)
	{
		pNode = new RegNode(hKey, strSubKey, hKeyRet, bUpdate);
	}
	return pNode;
}

