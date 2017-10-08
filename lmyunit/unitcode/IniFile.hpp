#ifndef __INI_FILE_HEADER__
#define  __INI_FILE_HEADER__

#include "tools.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <sstream>
#include <string>

using namespace std;
//20100625 qzj mdf . 
//2010_08_23_11:32:02 add by qzj
//代码整理。 

class IniFile 
{
public:
	typedef std::map<std::string, std::string> KeyValueMap;
	typedef std::map<std::string, KeyValueMap> SectionMap;
	IniFile() {}
	//默认只读取文件
	IniFile(const std::string& filename, bool append = false);
	~IniFile();

public:
	template <typename G> G   get(const std::string& section, const std::string& key) const;
	template <typename G> G   get(const std::string& section, const std::string& key, G defaultValue) const;

	template <typename G> void set(const std::string& section, const std::string& key, G value);

public:
	void save() const;
	void save(const std::string& filename) const;

	void save(const std::string& filename, int append=1) const;
	void save(std::ostream& out) const;

	void load(const std::string& filename, bool createFile =0);
	int  getSectionCount() const;
	int  getSections(vector<string> &out) const;

	bool hasSection(const std::string& section) const;
	bool hasKey(const std::string& section, const std::string& key) const;
	//const SectionMap& getSectionMap() const;
	int  getSectionMap() const;
	void removeSection(const std::string& section);
	void Dump();
private:
	
protected:
	void load_istream(std::istream& in);
	SectionMap m_dic;
	std::string m_filename;
};

//###############################################################################
 class IniFileError: public std::exception
{
public:
  IniFileError(): m_msg("Unspecified IniFile Error"){}

  IniFileError(const char* msg): m_msg(msg){}

  const char* what() const throw()
  {
    return m_msg;
  }

private:
  const char* m_msg;
};

/***************************************************
* Description	
* @param 	section:
* 			key:
* 			defaultValue: 默认值
* @return 	
* *************************************************/
template <typename G > G  IniFile::get(const std::string& section, const std::string& key, G defaultValue) const
{
	if (!hasKey(section, key)) 
	{
    	return defaultValue;
	} 
	else 
	{
		std::istringstream stream(m_dic.find(section)->second.find(key)->second);
		G t = G();
		stream >> t;
		if (!stream)
		{
			//throw IniFileError<char>("Invalid value when getting key");
			 printf("key is null");
		}
		return t;
	}
}

/***************************************************
* Description: 获取对应的值 
* @param 	
* 		section:
* 		key:
* @return 	
* *************************************************/
template <typename G> G IniFile::get(const std::string& section, const std::string& key) const
{
  return this->get(section, key, G());
}


/***************************************************
* Description: 内存中设置 ini 中的值	
* @param :
* 		section
* 		key	
* @return 	
* *************************************************/
template< typename G> void IniFile::set(const std::string& section, const std::string& key, G value)
{
	std::ostringstream stream;
	stream << value;
	if (!stream)
	{
		throw IniFileError("Invalid value when setting key");
	}
	
	if (m_dic.find(section) == m_dic.end()) 
	{
		m_dic[section] = KeyValueMap();
	}
	m_dic[section][key] = stream.str();
}


#endif

