
#include "tools.h"
#include "mfile.h"
#include "die.h"

/****************************************************************************
 * Description: 执行 shell 的命令。 
 * @param:	out 是 执行命令行之后 输出的字符串 
 * @return  	
 * 			返回值是 命令最后的返回值  
 * 			返回值的值 位于0-255 所以 需要对返回的值 对256 取mod.
 ***************************************************************************/
int  shell_exec(string const in, string &out)
{
#ifdef WINDOWSCODE
		return 1;
#else
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
#endif

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
template<typename T> void split( const string& source, T & string_out_list,const string& separator=string("\n") )
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
void  rand_mem_with_ascii_tools (char *input, int strLen)
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
 inline string ltrim(string const &str) 
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
 inline string rtrim(string const &str) 
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
 string trim(string const &str) 
{
	return rtrim(ltrim(str));
}

/****************************************************************************
* Description: sting  替换函数	
* @param 	
* 			pattern: 要取代的子字符串
* 			replacement: 目标字符串
* 			strIn: 源字符串	
* @return 	返回新的字符串;	
* *************************************************************************/
string str_replace( const string & pattern, const string &replacement, const string & strIn) 
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

 long long  filesize (string file)
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



//###############################################################################	
 string RandWord()
{
#ifdef WINDOWSCODE
	return "randword";
#else
	MFile  word;
	string ret;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	 
	srandom(tv.tv_sec+ tv.tv_usec);

	word.Open(MString("/usr/share/dict/linux.words"));
	int size=word.GetFileLength();
	word.Seek(random()%size, SEEK_SET);

	ret=word.ReadWord().c_str();
	word.Close();
	return ret;
#endif
}


 vector<string>  RandWord(int count)
{

	
	vector<string> vecStr;
	MFile word;
	struct timeval tv;
#ifdef WINDOWSCODE
#else
	gettimeofday(&tv, NULL);
	 
	srandom(tv.tv_sec+ tv.tv_usec);
	word.Open(MString("/usr/share/dict/linux.words"));
	int size=word.GetFileLength();
	for(int i=0; i<count;	i++)
	{
		word.Seek(random()%size, SEEK_SET);
		//cout<<word.ReadString()<<endl;
		//cout<<word.ReadWord()<<endl;
		vecStr.push_back(string(word.ReadWord().c_str()));
	}

	word.Close();
#endif
	return vecStr;
}

/****************************************************************************
* Description: 把string 对应的数据写入文件。 	
* @param :
* 		outfile: 输出的文件名。 
* 		in:		
* @return 	
* *************************************************************************/
int file_put_content(string outfile , string in, bool append=0)
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
	
	ofstream file(outfile.c_str(),  (append==0)?(ios::out|ios::trunc):(ios::out|ios::app));
	file<<in;
	file.close();
	return 1;
}

/****************************************************************************
* Description: words 每个word 的首字母大写	
* @param 	
* @return 	
* *************************************************************************/
string  ucfirst(string const &str)
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
* Description: 	
* @param :
* 		file: 输入的文件名  
* 		out: 传入的string 引用, 文件 append 的方式传入out. 	
* @return 	
* *************************************************************************/
int file_get_content(string file, string &out)
{
	fstream 	 in(file.c_str(), ios::in);
	string line;
	if(in.bad())
	{
		die("file open error");
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
char *file_seek64_and_read(FILE * file, int offset, int count, int * readLen)
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
		warn(" offset is larger than fileSize %d", length);
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
			warn(" read length not correct \n");
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
			warn(" read length not correct \n");
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

