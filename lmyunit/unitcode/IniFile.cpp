#include "IniFile.hpp"
//###############################################################################






/****************************************************************************
* Description	�����е�keyvalue ��dump ����. 
* @param 	
* @return 	
****************************************************************************/
 void IniFile::Dump()
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
 void IniFile::save() const
{
  save(m_filename,0);
}

/****************************************************************************
* Description	
* @param 	
* @return 	
* *************************************************************************/
 void IniFile::save(const std::string& filename, int append) const
{
  std::ofstream out(filename.c_str(), (append==0)?(ios::out|ios::trunc):(ios::out|ios::app));
  save(out);
}

/****************************************************************************
* Description: 		��ȡini�ļ���section ������ 	
* *************************************************************************/
 int IniFile::getSectionCount() const
{
  return int(m_dic.size());
}

/****************************************************************************
* Description	 ��ȡ���е� [sections]�� ����֮�������. 
* @param 	
* @return 	
* @notice 	
****************************************************************************/
 int IniFile::getSections(vector<string> &out) const
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
 bool IniFile::hasSection(const std::string& section) const
{
  return m_dic.find(section) != m_dic.end();
}


/****************************************************************************
* Description: ��section ����û�����ֵ 	
* @param 	
* @return 	
* *************************************************************************/
 bool IniFile::hasKey(const std::string& section, const std::string& key) const
{
  return hasSection(section) && m_dic.find(section)->second.find(key) != m_dic.find(section)->second.end();
}


//typedef  typename IniFile::SectionMap  MAP;
//   IniFile::SectionMap   IniFile::getSectionMap() const
//{
// return m_dic;
//}

//typedef  typename (  IniFile::SectionMap ) MAP;
// IniFile::SectionMap test;
   int  IniFile::getSectionMap() const
{
  //return m_dic;
  return 1;
}


/****************************************************************************
* Description: ɾ��һ�� section	
* @param 	
* @return 	
* *************************************************************************/
 void IniFile::removeSection(const std::string& section)
{
  m_dic.erase(section);
}



/****************************************************************************
* Description: ��ʼ���ļ���  �������ļ����ڴ�  
* @param 	
* @return 	
* *************************************************************************/
 IniFile ::IniFile(const std::string& filename, bool createFile): m_filename(filename)
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
 void IniFile::load(const std::string& filename, bool append)
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
 void IniFile::load_istream(std::istream& in)
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
			section = trim(line.substr(1, pos - 1));
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
				std::string key = trim(line.substr(0, pos));
				if (key.length() > 0) 
				{
					 if(std::string::npos != line.find_first_of(";"))
        			{   
            			std::string::size_type pos_end = line.find_first_of(";");
           				std::string value = trim(line.substr(pos+1, pos_end-pos-1));
						m_dic[section][key] = value;
        			}
					else
					{   
						std::string value = trim(line.substr(pos + 1));
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
 void IniFile::save(std::ostream& out) const
{
	if (!out)
	{
		throw IniFileError("Could not save ini");
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
	throw IniFileError("Error saving ini");
}



 IniFile::~IniFile()
{
}

