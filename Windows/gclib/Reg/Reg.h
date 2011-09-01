////////////////////////////////////////////////////////////////////////////////////////
// 
// GCLib -- Personal basic library project
// 
// FileName    : Reg.h
// Purpose     : 
// Version     : 2010-10-15 20:16:23 1.0 Created
//               2011-01-09 11:21:10 1.1 Add Returned enum key functions
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
/** @file Reg.h */
#pragma once

#include <list>
#include <map>
#include <functional>
#include <Singleton.h>
#include <StdString.h>
#include <CmmWinHdr.h>

/**
 *Take example:
 *
 *[HKEY_CURRENT_USER\Software\Google]
 *[HKEY_CURRENT_USER\Software\Google\Common]
 *[HKEY_CURRENT_USER\Software\Google\Common\Rlz]
 *[HKEY_CURRENT_USER\Software\Google\Common\Rlz\Events]
 *[HKEY_CURRENT_USER\Software\Google\Common\Rlz\Events\N]
 *"N1A"=dword:00000001
 *[HKEY_CURRENT_USER\Software\Google\Common\Rlz\PTimes]
 *"N"=hex(b):80,0a,a1,e1,c8,3e,cb,01
 *[HKEY_CURRENT_USER\Software\Google\Common\Rlz\RLZs]
 *"N1"="1N1GGPY_zhCN389"
 *
 *"N1"="1N1GGPY_zhCN389" is RegData
 *[HKEY_CURRENT_USER\Software\Google\Common\Rlz\RLZs] is RegNode
 */

/**
 * RegData encapsulates all type of data.
 */	
class RegData
{
public:
    RegData();
    ~RegData();
    RegData(const RegData& other);
public:
    RegData& operator = (const RegData& other);
    bool operator == (const RegData& other);
    bool operator != (const RegData& other);

public:		
    /**@name operations*/
    /**@{*/
    /**
     * Check whether the RegData is valid.
     * @return true is is valid, otherwise false.
     */
    bool IsDataValid() const;

    /**
     * Convenient function to set the value, We should use this function instead of others
     * @param nType The Type of the RegData, correspond type please reference MSDN
     * @param strKey The Name
     * @param pData The data
     * @param dwDataLen The length of the data
     */
    void SetValue(DWORD dwType, const StdString strKey, const void* pData, DWORD dwDataLen);
    /**
     * The Type of the RegData
     * @param nType The Type of the RegData, correspond type please reference MSDN
     */
    void SetDataType(DWORD nType);
    /**
     * Get The type of RegData
     * @return The type of RegData
     */
    DWORD GetDataType() const;

    /**
     * Set the Name of the RegData Item
     * @param strKeyName The Name
     */
    void SetKeyName(const StdString strKeyName);
    /**
     * Get the key name of the RegData Item
     * @return The RegData Name
     */
    StdString GetKeyName() const;

    /**
     * Set the RegData Item Value
     * @param pData The data
     * @param dwLength The length of the data
     */
    void SetData(const VOID* pData, DWORD dwLength);
    /**
     * Get the RegData Item Value
     * @return the RegData Item Value
     */
    const VOID* GetData() const;	

    /**
     * Set the length of the RegData
     * @param nLengh The length
     */
    void SetDataLength(DWORD nLength);
    /**
     * Get the Data length
     * @return the length of the RegData
     */
    DWORD GetDataLength() const;
    /**@}*/

private:

    //The Type
    DWORD m_nType;	
    //The KeyName
    StdString m_strKeyName;
    //The Data
    VOID* m_pRegData;
    //The Length of the data
    DWORD m_nLength;
};

/*Data comparer. Use internal, Client should avoid calling this Class*/
template<typename TheClass>
class RegDataCompare : public std::binary_function<TheClass*, TheClass*, bool>
{
public:
    /*Compare function*/
    bool operator()(TheClass* pLeft, TheClass* pRight) const;
};


/**
 * The RegNode Data.
 *
 * When a new object is construct, It tries to retrieve as much data as possible.
 * We usually use the RegFactory to create a new object of the type
 */
class RegNode
{	
    typedef std::list<RegData*>::iterator REGDataIterator;
    typedef std::map<StdString, RegNode*>::iterator REGNodeIterator;
public:
    /**@name Constructor & Destructor*/
    /**@{*/
    /**
     * Constructor
     * @param hKey The Reg Key
     * @param bUpdata The flag specific whether update data when the object is deconstruct
     */
    RegNode(HKEY hRootKey, StdString strCurSubKey, HKEY hKey, bool bUpdate = false);
    /**Destructor, Release resource*/
    virtual ~RegNode();
    /**@}*/
public:
    /**
     * Add a new regdata the the node
     * @param pRegData The RegData
     * @param bOverwrite The flag specific whether update the data to a new one if it exists
     * @return true if successfully added, false otherwise.
     */
    bool AddRegData(RegData* pRegData, bool bOverwrite = true);
    /**
     * Convenient function to set the value
     * @param nType The Type of the RegData, correspond type please reference MSDN
     * @param strKey The Name
     * @param pData The data
     * @param dwDataLen The length of the data
     * @param bOverwrite The flag specific whether update the data to a new one if it exists
     * @return true if successfully added, false otherwise.
     */
    bool AddRegData(DWORD dwType, const StdString strKey, const void* pData, DWORD dwDataLen, bool bOverwrite = true);
    /**
     * Get the specific key value
     * @param strKey The Key
     * @param regData The value get from the node
     * @return true if the value is successfully copy to the target.
     */
    bool GetRegData(const StdString strKey, RegData& regData);

    /**
     * Add an new node. if the node exist, just return it.
     * @param strKey The subkey name
     * @return the existing/New NodeData, or NULL if fail
     */
    RegNode* AddNode(const StdString strKey);
    /**
     * Delete the specific subkey
     * @param strKey The subkey, if it is empty delete itself
     * @return true if the specific key is delete, otherwise false
     */
    bool DeleteNode(const StdString strKey = _T(""));
    /**
     * Get the specific key node data
     * @param strKey The subkey
     * @return the RegNode or NULL if does not exist.
     */
    RegNode* GetNode(const StdString strKey);
    //2011-01-09
    int GetNodes(std::list<RegNode*>& rgpNodes);
    //2011-01-09

    /**
     * Save the data
     * @return true is successfully save, false otherwise
     */
    bool Save();

    //2011-01-09
    /**
     * Get keys of the group items
     * @param rpgKeys the keys return
     * @return the size of the keys return
     */
    int GetGroupKeys(std::list<StdString>& rgpKeys);
     /**
     * Get keys of the data items
     * @param rpgKeys the keys return
     * @return the size of the keys return
     */
    int GetNodeKeys(std::list<StdString>& rgpKeys);
    //2011-01-09

    /**@name properties*/
    /**@{*/
    /**
     * Get the relative sub key
     */
    StdString GetRelativeSubKey();
    /**
     * Get the ROOT key
     */
    HKEY GetRootHKEY();
    /**
     * Get the CURRENT key
     */
    HKEY GetCurrentHKEY();
    /**@}*/
    

    /**Store changes whether this item is destroy*/
    bool GetDestroySave();
    /**Set whether save the changes when the item is destroy*/
    void SetDestroySave(bool bUpdate);

    /**Check whether the item is valid*/
    bool IsValid() const;

protected:
    void InitData();
    void ClearUp();

protected:
    HKEY m_hKey;
    bool m_bUpdate;

    /****/
    HKEY m_hRootKey;
    StdString m_strSubKey;
    /****/

private:
    std::list<RegData*> m_lstRegData;
    std::map<StdString, RegNode*> m_mapRegNode;

};

/**The Factory of RegUtil*/
class RegFactory : public Singleton<RegFactory>
{
public:

    /**
    * To Create or Get an existing RegGoupData
    * @param hKey The Root Reg KEY
    * @param strSubKey The subkey path
    * @param bUpdate The flag specific whether save the changed values when object is deconstuct.
    * @return an existing/new RegGroupData, NULL if fails.
    */
    RegNode* CreateRegNode(HKEY hKey, const StdString strSubKey, bool bUpdate = false);
    /**To Get an existing RegGoupData
    * @param hKey The Root Reg KEY
    * @param strSubKey The subkey path
    * @param bUpdate The flag specific whether save the changed values when object is deconstuct.
    * @return an existing/new RegNode, NULL if fails.
    */
    RegNode* GetRegNode(HKEY hKey, const StdString strSubKey, bool bUpdate = false);
};
