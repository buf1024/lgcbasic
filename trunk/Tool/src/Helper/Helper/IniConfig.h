//=============================================================================
/**
* @file	    IniConfig.h
* @brief	Ini Configuration File
* @author	heidong
* @version	1.0
* @date		2010-10-16 0:19:12
*/
//=============================================================================
#pragma once
#include <list>
#include <map>
#include <string>
#include <fstream>

#ifdef _UNICODE
#define Std_String std::wstring
#else
#define Std_String std::string
#endif

namespace lgc
{
	/**Represent a single Section of an ini configration file*/
	class Section
	{
		typedef std::map< Std_String, Std_String >::iterator KVIterator;
	public:
		/**Construct a section with an specific section name
		*@param strSectionName section name, default to empty
		*/
		Section(Std_String strSectionName = _T(""));
		~Section();
	public:
		/**Set a section name
		*@param strSectionName the section name
		*/
		void SetSectionName(const Std_String strSectionName);
		/**Get a section name
		*@return the secion name
		*/
		Std_String GetSectionName() const;

		/**@name Get and Set function*/
		/**@{*/
		/**Insert/update a specific key with a specific value
		*@param strKey Key
		*@param strValue the string value
		*/
		void Insert(const Std_String strKey, Std_String strValue);
		/**Insert/update a specific key with a specific value
		*@param strKey Key
		*@param chValue the character value
		*/
		void Insert(const Std_String strKey, TCHAR chValue);
		/**Insert/update a specific key with a specific value
		*@param strKey Key
		*@param nValue the int value
		*/
		void Insert(const Std_String strKey, int nValue);
		/**Insert/update a specific key with a specific value
		*@param strKey Key
		*@param lValue the long value
		*/
		void Insert(const Std_String strKey, long lValue);
		/**Insert/update a specific key with a specific value
		*@param strKey Key
		*@param lValue the double dValue
		*/
		void Insert(const Std_String strKey, double dValue);
		/**Get a specific key value, if the key not found, return the default one
		*@param strKey Key
		*@param strValue The return value
		*@param strDefault The default value
		*@return true if find the specific key, otherwise false
		*/
		bool GetValue(const Std_String strKey, Std_String& strValue, Std_String strDefault = _T(""));

		/**Delete the specific key/value pair
		*@param strKey Key
		*/
		void Delete(const Std_String strKey);
		/**Empty the section*/
		void Empty();
		/**@}*/
		/**Load the specific section from the file.
		*we should set the specific section first
		*@param strFilePath the file path
		*@return true if load successfully, otherwise false
		*/
		bool Load(Std_String strFilePath);
		/**Save the section to the specific file
		*@param strFilePath the file path
		*@return true if save successfully, otherwise false
		*/
		bool Save(Std_String strFilePath);

	private:
		Std_String m_strSectionName;
		std::map< Std_String, Std_String > m_mapKeyValue;
	};

	/**Represent Ini Confuration File*/
	class IniConfig
	{
		typedef std::list<Section*>::iterator ICIterator;
	public:
		/**Init IniConfig class with the specific file.
		*@param strFilePath the file path
		*/
		IniConfig(Std_String strFilePath = _T(""));
		~IniConfig();

		/**Set the file path
		*@param strFilePath the file path
		*/
		void SetFilePath(const Std_String strFilePath);
		/**Get the file path
		*@return the file path
		*/
		Std_String GetFilePath() const;

		/**Insert the specific section
		*@param pSec The specific section
		*@return true if successfull inserted, otherwise is the section equals false.
		*/
		bool Insert(Section* pSec);
		/**Delete the specific section.*
		*@param strSection the specific secion name
		*/
		void Delete(const Std_String strSection);
		/**Get the specific section
		*@param strSecName The specific section name
		*@return The specific section name, or NULL if not found.
		*/
		Section* GetSection(const Std_String strSecName);


		/**Load the specific IniConfig from the file.
		*@param strFilePath the file path
		*@return true if load successfully, otherwise false
		*/
		bool Load(const Std_String strFilePath);
		/**Save the IniConfig to the specific file
		*@param strFilePath the file path
		*@return true if save successfully, otherwise false
		*/
		bool Save(const Std_String strFilePath);
	private:
		void ClearUp();
	private:
		Std_String m_strFilePath;
		std::list<Section*> m_lstSections;
	};
}