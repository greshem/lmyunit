#ifndef __INI_FILE_HEADER__
#define  __INI_FILE_HEADER__

#include "Tools.hpp"
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
//�������� 

template <typename T>  class IniFile 
{
public:
	typedef std::map<std::string, std::string> KeyValueMap;
	typedef std::map<std::string, KeyValueMap> SectionMap;
	IniFile<T>() {}
	//Ĭ��ֻ��ȡ�ļ�
	IniFile<T>(const std::string& filename, bool append = false);
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
template <typename T> class IniFileError: public std::exception
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
//###############################################################################



/***************************************************
* Description	
* @param 	section:
* 			key:
* 			defaultValue: Ĭ��ֵ
* @return 	
* *************************************************/
template <typename  T> template <typename G > G  IniFile<T>::get(const std::string& section, const std::string& key, G defaultValue) const
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
* Description: ��ȡ��Ӧ��ֵ 
* @param 	
* 		section:
* 		key:
* @return 	
* *************************************************/
template <typename  T> template <typename G> G IniFile<T>::get(const std::string& section, const std::string& key) const
{
  return this->get(section, key, G());
}


/***************************************************
* Description: �ڴ������� ini �е�ֵ	
* @param :
* 		section
* 		key	
* @return 	
* *************************************************/
template <typename T> template< typename G> void IniFile<T>::set(const std::string& section, const std::string& key, G value)
{
	std::ostringstream stream;
	stream << value;
	if (!stream)
	{
		throw IniFileError<char>("Invalid value when setting key");
	}
	
	if (m_dic.find(section) == m_dic.end()) 
	{
		m_dic[section] = KeyValueMap();
	}
	m_dic[section][key] = stream.str();
}

/****************************************************************************
* Description	�����е�keyvalue ��dump ����. 
* @param 	
* @return 	
****************************************************************************/
template <typename T> void IniFile<T>::Dump()
{
	//m_dic;_
	map<string, map<string, string> >::iterator it1;
	map<string, string>::iterator it2;

	for(it1=m_dic.begin(); it1 != m_dic.end(); it1++)
	{
		cout<<"["<<(*it1).first<<"]"<<endl;
		for(it2=(*it1).second.begin(); it2!=(*it1).second.end(); it2++)
		{
			cout<<"\t"<<(*it2).first<<"= "<<(*it2).second<<endl;
		}
	}
}


/****************************************************************************
* Description	
* @param 	
* @return 	
* *************************************************************************/
template <typename T> void IniFile<T>::save() const
{
  save(m_filename,0);
}

/****************************************************************************
* Description	
* @param 	
* @return 	
* *************************************************************************/
template <typename T> void IniFile<T>::save(const std::string& filename, int append) const
{
  std::ofstream out(filename.c_str(), (append==0)?(ios::out|ios::trunc):(ios::out|ios::app));
  save(out);
}

/****************************************************************************
* Description: 		��ȡini�ļ���section ������ 	
* *************************************************************************/
template <typename T> int IniFile<T>::getSectionCount() const
{
  return int(m_dic.size());
}

/****************************************************************************
* Description	 ��ȡ���е� [sections]�� ����֮�������. 
* @param 	
* @return 	
* @notice 	
****************************************************************************/
template <typename T> int IniFile<T>::getSections(vector<string> &out) const
{
		
	//typedef std::map<std::string, std::string> KeyValueMap;
	//typedef std::map<std::string, KeyValueMap> SectionMap;
	//
	//SectionMap m_dic;
	map<std::string, map<string, string> >::const_iterator it;

	//it= m_dic.begin();
	for(it = m_dic.begin(); it!= m_dic.end(); it++)
	{
		out.push_back((*it).first);		
	}
	return 1;
}



/****************************************************************************
* Description: ��û������ֶ� 	
* @param 	
* @return 	
* *************************************************************************/
template <typename T> bool IniFile<T>::hasSection(const std::string& section) const
{
  return m_dic.find(section) != m_dic.end();
}


/****************************************************************************
* Description: ��section ����û�����ֵ 	
* @param 	
* @return 	
* *************************************************************************/
template <typename T> bool IniFile<T>::hasKey(const std::string& section, const std::string& key) const
{
  return hasSection(section) && m_dic.find(section)->second.find(key) != m_dic.find(section)->second.end();
}


//typedef  typename IniFile<T>::SectionMap  MAP;
//template <typename T>   IniFile<T>::SectionMap   IniFile<T>::getSectionMap() const
//{
// return m_dic;
//}

//typedef  typename ( template <typename T> IniFile<T>::SectionMap ) MAP;
//template <typename T> IniFile<T>::SectionMap test;
template <typename T>   int  IniFile<T>::getSectionMap() const
{
  //return m_dic;
  return 1;
}


/****************************************************************************
* Description: ɾ��һ�� section	
* @param 	
* @return 	
* *************************************************************************/
template <typename T> void IniFile<T>::removeSection(const std::string& section)
{
  m_dic.erase(section);
}



/****************************************************************************
* Description: ��ʼ���ļ���  �������ļ����ڴ�  
* @param 	
* @return 	
* *************************************************************************/
template <typename T> IniFile<T> ::IniFile(const std::string& filename, bool createFile): m_filename(filename)
{
  load(m_filename, createFile);
}



/****************************************************************************
* Description: 
* @param :
* 		filename
* 		createFile: 0. ���´����µ��ļ���
* 					1. append �ķ�ʽ����ļ��� 
* 					Ĭ���Ǵ������ļ��� 
* @return 	
* *************************************************************************/
template <typename T> void IniFile<T>::load(const std::string& filename, bool append)
{
	m_filename = filename;
	if (append) 
	{
		std::fstream(m_filename.c_str(), std::ios::app);
	}
	std::ifstream in(m_filename.c_str());
	load_istream(in);
}

/****************************************************************************
* Description: ini�ļ������룬  
* @param 	
* @return 	
* @notice: ��Ҫͨ�� string  ��һЩ����. ���ļ����н����� 
* *************************************************************************/
template <typename T> void IniFile<T>::load_istream(std::istream& in)
{
	if (!in)
	{
		cout<<"IniFile"<<m_filename<<"  file not exists\n"<<endl;
		exit(-1);
	}
	//throw IniFileError<char>("Could not load ini");

	std::string section;
	while (!in.eof()) 
	{
		std::string line;
		std::getline(in, line);
		if (in.bad())
		{
		 	//throw IniFileError<char>();
			cout<<"file stat error \n"<<endl;
		}

		if (line.length() == 0)
		  continue;

		if (line.at(0) == ';' || line.at(0) == '#')
		  continue;
		if (line.at(0) == '[') 
		{
			std::string::size_type pos = line.find_first_of("]");
			section = trim<char>(line.substr(1, pos - 1));
			if (m_dic.find(section) == m_dic.end()) 
			{
				m_dic[section] = KeyValueMap();
			}
		} 
		else if (section.length() > 0) 
		{
			
			std::string::size_type pos = line.find_first_of("=");
			if (pos != std::string::npos) 
			{
				std::string key = trim<char>(line.substr(0, pos));
				if (key.length() > 0) 
				{
					 if(std::string::npos != line.find_first_of(";"))
        			{   
            			std::string::size_type pos_end = line.find_first_of(";");
           				std::string value = trim<char>(line.substr(pos+1, pos_end-pos-1));
						m_dic[section][key] = value;
        			}
					else
					{   
						std::string value = trim<char>(line.substr(pos + 1));
						m_dic[section][key] = value;
					}
				}
			}
		}
	}
}



/****************************************************************************
* Description: ���浽�ļ��� 
* @param out:  std::ostream ��Ҫ������ʼ���� 	
* @return 	
* *************************************************************************/
template <typename T> void IniFile<T>::save(std::ostream& out) const
{
	if (!out)
	{
		throw IniFileError<char>("Could not save ini");
	}

	SectionMap::const_iterator iter;
	for (iter = m_dic.begin(); iter != m_dic.end(); ++iter) 
	{
		std::string sectionName = iter->first;
		const KeyValueMap& section = iter->second;

		out << "[" << sectionName << "]\n";

		KeyValueMap::const_iterator sIter;
		for (sIter = section.begin(); sIter != section.end(); sIter++) 
		{
		  out <<"\t"<< sIter->first << "=" << sIter->second << '\n';
		}
		out << '\n';
	}

	if (!out)
	throw IniFileError<char>("Error saving ini");
}



template <typename T> IniFile<T>::~IniFile()
{
}



#endif
