
#ifndef __QzjUnit_TOOLS__
#define  __QzjUnit_TOOLS__

//#2010_08_13_18:10:48 add by qzj
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string> 
//#include <dirent.h>
#include <fstream>
#include <iterator>  
#include <vector> 
#include <algorithm>
#include <iostream> 
#include <map>
#include <stdarg.h>
#include "die.hpp"
using namespace std;
/****************************************************************************
* Description: 偏移到一定的位置并读取一定数量的数据。 
* @param 	
* 		file: 	文件
* 		offset:	文件偏移 
* 		count: 	读取的数据数量
* 		readLen: 具体读取的数据的长度
* @return : 读取之后的数据， 	
* @notice: 注意要释放malloc 之后的数据,  返回的时候， 文件的偏移重新设置好了。 
* 			支持的64位。  
* *************************************************************************/
template <typename T> char *file_seek64_and_read(FILE * file, int offset, int count, int * readLen)
{
	if(file==NULL)
	{
		return NULL;
	}
	char *buffer=NULL;
	int ret;
	buffer=(char *)malloc(count);
	if(buffer ==NULL)
	{
		cout<<" 内存分配失败"<<endl;
		return NULL;
	}
	memset(buffer, '\0', count);
#ifdef WINDOWSCODE
	__int64  cur_len= _lseeki64( fileno(file), 0, SEEK_CUR);
	_lseeki64(fileno(file), 0, SEEK_END);
	//获取文件长度。
	long long  length=_lseeki64(fileno(file), 0, SEEK_CUR);
#else
	int cur_len= lseek64( fileno(file), 0, SEEK_CUR);
	lseek64(fileno(file), 0, SEEK_END);
	//获取文件长度。
	long long  length=lseek64(fileno(file), 0, SEEK_CUR);
#endif

	//请求的offset 大于文件的长度。 
	if( offset > length)
	{
		warn<char>(" offset is larger than fileSize %d", length);
#ifdef WINDOWSCODE
		_lseeki64(fileno(file), cur_len, SEEK_SET);
#else
		lseek64(fileno(file), cur_len, SEEK_SET);		
#endif
		return NULL;
	}

	//在文件末尾的时候, 读取的字节会< count. 	
	if(length -offset < count)
	{
		fseek(file, offset, SEEK_SET);
		//写成  fread(tmp, sizeof(tmp), 1 , file)返回 读取了几个结构
		ret=fread(buffer, 1, count,   file);
		if(ret != count)
		{
			warn<char>(" read length not correct \n");
		}
		*readLen=ret;
#ifdef WINDOWSCODE
		_lseeki64(fileno(file), cur_len, SEEK_SET);
#else
		lseek64(fileno(file), cur_len, SEEK_SET);
#endif
		return buffer;
	}
	else
	{
		fseek(file, offset, SEEK_SET);
		ret=fread(buffer, 1,count, file);
		if(ret != count)
		{
			warn<char>(" read length not correct \n");
		}
		//putChar(tmp, count);
		*readLen=ret;
#ifdef WINDOWSCODE
		_lseeki64(fileno(file), cur_len, SEEK_SET);
#else
		lseek64(fileno(file), cur_len, SEEK_SET);
#endif
		return buffer;
	}	
}
/****************************************************************************
* Description: 	
* @param :
* 		file: 输入的文件名  
* 		out: 传入的string 引用, 文件 append 的方式传入out. 	
* @return 	
* *************************************************************************/
template <typename T>int file_get_content(string file, string &out)
{
	fstream 	 in(file.c_str(), ios::in);
	string line;
	if(in.bad())
	{
		die<char>("file open error");
	}
	while ( std::getline(in, line, '\n') )
	{
		out+=line;
		out+="\n";
	}
	in.close();
	return 1;	
}
/****************************************************************************
* Description: 把string 对应的数据写入文件。 	
* @param :
* 		outfile: 输出的文件名。 
* 		in:		
* @return 	
* *************************************************************************/
template < typename T > int file_put_content(string outfile , string in, bool append=0)
{
	//截断
 	//ofstream output(FileName.c_str(),ios::out|ios::trunc);
 	//append, 文件添加模式  就是shell 中的 >> 
	//ofstream file(outfile.c_str(), ios::app);
	//create file , 文件重新被清空。 
	
	// if(append==1)
	// {
	// 	ofstream file(outfile.c_str(), ios::app);
	// }
	// else
	// {
	// 	ofstream file(outfile.c_str());
	// }
	ofstream file(outfile.c_str(), ios::app);
	file<<in;
	file.close();
	return 1;
}

/****************************************************************************
* Description	
* @param 	
* @return 	
* *************************************************************************/
template < typename T> long long  filesize (string file)
{
	struct stat st;
	long long ret=stat(file.c_str(), &st);
	if(ret ==-1)
	{
		cout<<file<<" stat error"<<endl;
		return -1;
	}
#ifdef WINDOWSCODE
	 return st.st_size ;         
#else
	switch (st.st_mode & S_IFMT)
	{
		//block device
		case S_IFBLK: return st.st_size ;         
			break;
		//char device
		case S_IFCHR:  return st.st_size  ;    
			break;
		//dirrectory
		case S_IFDIR:  return st.st_size  ;            
			break;
		//FIFO/pipe
		case S_IFIFO:  return st.st_size  ;            
			break;
		//symlink
		case S_IFLNK:  return st.st_size  ;            
			break;
		// regular file 
		case S_IFREG:  return st.st_size  ;            
			break;
		//socket
		case S_IFSOCK: return st.st_size  ;            
			break;
		default:       return -1;
			break;
	}
#endif
}

/****************************************************************************
* Description: words 每个word 的首字母大写	
* @param 	
* @return 	
* *************************************************************************/
 template <typename T > string  ucfirst(string const &str)
{
	string out;
	bool newword=true;
	for(string::const_iterator i =str.begin(); i!= str.end(); i++)
	{
		if(newword && isalpha(*i))
		{
			out+=toupper(*i);
			newword=false;
		}
		else
		{
			if(isspace(*i) || ispunct(*i))
			{
				newword=true;
			}
			out+=*i;
		}
	}
	return out;
}
/****************************************************************************
* Description: 执行 shell 的命令。 
* @param 	
* @return 	
* *************************************************************************/
template <typename T> string shell_exec(string const in)
{
#ifdef WINDOWSCODE
	//return string("");
	  SECURITY_ATTRIBUTES sa; 
    HANDLE hRead,hWrite;
    
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;
    if (!CreatePipe(&hRead,&hWrite,&sa,0))
    {   
        return FALSE;
    }   
    char command[1024];    //长达1K的命令行，
    //strcpy(command,"Cmd.exe /C ");
    //strcat(command,EXECDOSCMD);
      strcpy(command, in.c_str());
    STARTUPINFO si; 
    PROCESS_INFORMATION pi; 
    si.cb = sizeof(STARTUPINFO);
    GetStartupInfo(&si);
    si.hStdError = hWrite;            //把创建进程的标准错误输出重定向到管道输入
    si.hStdOutput = hWrite;           //把创建进程的标准输出重定向到管道输入
    si.wShowWindow = SW_HIDE;
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    //关键步骤，CreateProcess函数参数意义请查阅MSDN
    if (!CreateProcess(NULL, command,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi))
    {   
        CloseHandle(hWrite);
        CloseHandle(hRead);
        return FALSE;
    }   
    CloseHandle(hWrite);
    
    char buffer[4096] = {0};          //用4K的空间来存储输出的内容，只要不是显示文件内容，一般情况下是够用了。
    DWORD bytesRead;
    while (true)
    {   
        if (ReadFile(hRead,buffer,4095,&bytesRead,NULL) == NULL)
            break;
        //buffer中就是执行的结果，可以保存到文本，也可以直接输出
        //  MessageBox(NULL, buffer, "test", MB_OK);   //这里是弹出对话框显示
        //if(logToFile)
        //{   
        //    global_Log.WriteInfo("COMMAND", "%s", buffer);
        //}   
    }   
    CloseHandle(hRead);
	return string(buffer);
#else
	FILE *pipe=popen(in.c_str(), "r");
	char buffer[1024];
	string out;
	
	if(! pipe) 
	{
		cout<<"pipe open error"<<endl;
	}
	
	while((fgets(buffer, sizeof(buffer), pipe)))
	{
		out+=buffer;
	}
	fclose(pipe);
	return out;
#endif
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
* Description	
* @param 	
* @return 	
* *************************************************************************/
template <typename T> string getpwd(void)
{
#ifdef WINDOWSCODE
	char						tempbuf[256];

	if ( ::GetCurrentDirectory(256,tempbuf) == 0 )
	{
		return("");
	}
	
	if ( strlen(tempbuf) > 0 && tempbuf[strlen(tempbuf)-1] != '\\' )
	{
		strcat(tempbuf,"\\");	
	}

	return(tempbuf);
#else
	char						tempbuf[256];
	
	if ( getcwd(tempbuf,256) < 0 )
	{
		return("");	
	}
	
	if ( strlen(tempbuf) > 0 && tempbuf[strlen(tempbuf)-1] != '/' )
	{
		strcat(tempbuf,"/");	
	}
	
	return(tempbuf);
#endif
}

/****************************************************************************
* Description	
* @param 	
* @return 	
* *************************************************************************/
template <class T>  
int dump_all( T &in )
{
    typedef typename T::iterator IT; 
    IT it; 
    for(it=in.begin(); it!= in.end(); it++)
    {   
        cout<<*it<<endl;
    }   
    return 1;
}

/****************************************************************************
* Description	
* @param 	
* @return 	
* *************************************************************************/
template <class T>  
int dump_all_to_file( T &in , string FileName, int append=1)
{
    typedef typename T::iterator IT; 
	ofstream output(FileName.c_str(), (append==0)?(ios::out|ios::trunc):(ios::out|ios::app));

	//########################################################################
	// 下面的定义的方式有点累赘了， 	
	// if(append!=0)
	// {
	// 		ofstream output(FileName.c_str(), ios::out|ios::trunc);
	// }
	// else
	// {
	// 		ofstream output(FileName.c_str(), ios::out|ios::app);
	// }

    IT it; 
    for(it=in.begin(); it!= in.end(); it++)
    {   
        output<<*it<<endl;
    }   
    return 1;
}

//########################################################################
#endif   
