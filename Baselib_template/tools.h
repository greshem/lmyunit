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
* Description: 全部dump 对应的T 需要有 << 操作符. 
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
 * Description: 执行 shell 的命令。 
 * @param:	out 是 执行命令行之后 输出的字符串 
 * @return  	
 * 			返回值是 命令最后的返回值  
 * 			返回值的值 位于0-255 所以 需要对返回的值 对256 取mod.
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
    return (ret%255); //不是256

}


/****************************************************************************
* Description	: 一般把从shell_exec 执行返回的字符串进行分割. 
* @param 	
*		stringlist 输出,  一般是 vector<string> 或者 list<string> deque<string> 等等. 
*						反正是容器. 
*		soruce 		要被分割的句子.	
*		separator 	分割符号. 一般是"\n";
* @return, 	
****************************************************************************/
//template<typename T>  void split(T & stringlist,const string& source,const string& separator=string("\n") )
template<typename T>  void split( const string& source, T & string_out_list,const string& separator=string("\n") )
{
	int start = 0;
	//fixme, unsigned int 会造成死循环 , why?  
	//unsigned int end = source.find_first_of(separator);
	size_t  end = source.find_first_of(separator);
	while(end != string::npos)
	{
		string_out_list.push_back(source.substr(start,end-start));
		start = end +1;
		end = source.find(separator,start);
	}
	//最后一行是空行 不要加入.
	//stringlist.push_back(source.substr(start,source.length()-start));
}

/****************************************************************************
 * Description   一块内存用 ascii来随机填充.
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
* Description: trim 去除左右空格. 	
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
* Description: sting  替换函数	
* @param 	
* 			pattern: 要取代的子字符串
* 			replacement: 目标字符串
* 			strIn: 源字符串	
* @return 	返回新的字符串;	
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
