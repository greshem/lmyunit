#ifndef __TOOLS_H__
#define __TOOLS_H__


#include <fstream>
#include <string> 
#include <iostream>
#include <map>
#include <iostream> 
#include <algorithm>
#include <vector> 
#include <iterator>  
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>

using namespace std;
/****************************************************************************
* Description: ȫ��dump ��Ӧ��T ��Ҫ�� << ������. 
* @param 	
* @return 	
* *************************************************************************/
template <class T>   int dump_all( T &in )
{
    typedef typename T::iterator IT; 
    IT it; 
    for(it=in.begin(); it!= in.end(); it++)
    {   
        cout<<*it<<endl;
    }   
    return 1;
}




//########################################################################
template <typename T> int  RandData(T &in)
{
	return 1;
}

/****************************************************************************
 * Description: ִ�� shell ����� 
 * @param:	out �� ִ��������֮�� ������ַ��� 
 * @return  	
 * 			����ֵ�� �������ķ���ֵ  
 * 			����ֵ��ֵ λ��0-255 ���� ��Ҫ�Է��ص�ֵ ��256 ȡmod.
 ***************************************************************************/
template <typename T> int  shell_exec(string const in, string &out)
{
    FILE *pipe=popen(in.c_str(), "r");
    char buffer[1024];
    //string out;

    if(! pipe)
    {
        cout<<"pipe open error"<<endl;
    }

    while((fgets(buffer, sizeof(buffer), pipe)))
    {
        out+=buffer;
    }
    //fclose(pipe);
    int ret=pclose(pipe);
	//return ret;
    return (ret%255); //����256

}


/****************************************************************************
* Description	: һ��Ѵ�shell_exec ִ�з��ص��ַ������зָ�. 
* @param 	
*		stringlist ���,  һ���� vector<string> ���� list<string> deque<string> �ȵ�. 
*						����������. 
*		soruce 		Ҫ���ָ�ľ���.	
*		separator 	�ָ����. һ����"\n";
* @return, 	
****************************************************************************/
//template<typename T>  void split(T & stringlist,const string& source,const string& separator=string("\n") )
template<typename T>  void split( const string& source, T & string_out_list,const string& separator=string("\n") )
{
	int start = 0;
	//fixme, unsigned int �������ѭ�� , why?  
	//unsigned int end = source.find_first_of(separator);
	size_t  end = source.find_first_of(separator);
	while(end != string::npos)
	{
		string_out_list.push_back(source.substr(start,end-start));
		start = end +1;
		end = source.find(separator,start);
	}
	//���һ���ǿ��� ��Ҫ����.
	//stringlist.push_back(source.substr(start,source.length()-start));
}

/****************************************************************************
 * Description   һ���ڴ��� ascii��������.
 * @param    
 * @return   
 * *************************************************************************/
template <typename T> void  rand_mem_with_ascii (char *input, int strLen)
{
	if(input == NULL|| strLen==0 )
	{
		return ;
	}

    for (int i=0; i< strLen; i++)
    {
        *(input+i)='a'+rand()%26;
    }
    input[strLen]='\0';
}


/****************************************************************************
* Description: trim ȥ�����ҿո�. 	
* @param 	
* @return 	
* *************************************************************************/
template < typename T> inline string ltrim(string const &str) 
{

	for (unsigned i = 0; i < str.size(); i++)
	{
		if (!isspace(str[i]))
		{
			return str.substr(i);
		}
	}
	return "";
}
/****************************************************************************
* Description	
* @param 	
* @return 	
* *************************************************************************/
template < typename T> inline string rtrim(string const &str) 
{
	for (int i = str.size() - 1; i >= 0; i--)
	{
		if (!isspace(str[i]))
		{
			return str.substr(0, i + 1);
		}
	}
	return "";
}
/****************************************************************************
* Description	
* @param 	
* @return 	
* *************************************************************************/
template < typename T> inline string trim(string const &str) 
{
	return rtrim<T>(ltrim<T>(str));
}

/****************************************************************************
* Description: sting  �滻����	
* @param 	
* 			pattern: Ҫȡ�������ַ���
* 			replacement: Ŀ���ַ���
* 			strIn: Դ�ַ���	
* @return 	�����µ��ַ���;	
* *************************************************************************/
template < typename T> string str_replace( const string & pattern, const string &replacement, const string & strIn) 
{
	string out=strIn;
	string::size_type pos=0;
	string::size_type srclen=pattern.size();
	string::size_type dstlen=replacement.size();
	while( (pos=out.find(pattern, pos)) != string::npos)
	{
		out.replace(pos, srclen, replacement);
		pos += dstlen;
	}
	return out;
}

#endif
