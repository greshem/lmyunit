
#include "tools.h"
#include "mfile.h"
#include "die.h"

/****************************************************************************
 * Description: ִ�� shell ����� 
 * @param:	out �� ִ��������֮�� ������ַ��� 
 * @return  	
 * 			����ֵ�� �������ķ���ֵ  
 * 			����ֵ��ֵ λ��0-255 ���� ��Ҫ�Է��ص�ֵ ��256 ȡmod.
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
    return (ret%255); //����256
#endif

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
template<typename T> void split( const string& source, T & string_out_list,const string& separator=string("\n") )
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
* Description: trim ȥ�����ҿո�. 	
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
* Description: sting  �滻����	
* @param 	
* 			pattern: Ҫȡ�������ַ���
* 			replacement: Ŀ���ַ���
* 			strIn: Դ�ַ���	
* @return 	�����µ��ַ���;	
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
* Description: ��string ��Ӧ������д���ļ��� 	
* @param :
* 		outfile: ������ļ����� 
* 		in:		
* @return 	
* *************************************************************************/
int file_put_content(string outfile , string in, bool append=0)
{
	//�ض�
 	//ofstream output(FileName.c_str(),ios::out|ios::trunc);
 	//append, �ļ����ģʽ  ����shell �е� >> 
	//ofstream file(outfile.c_str(), ios::app);
	//create file , �ļ����±���ա� 
	
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
* Description: words ÿ��word ������ĸ��д	
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
* 		file: ������ļ���  
* 		out: �����string ����, �ļ� append �ķ�ʽ����out. 	
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
* Description: ƫ�Ƶ�һ����λ�ò���ȡһ�����������ݡ� 
* @param 	
* 		file: 	�ļ�
* 		offset:	�ļ�ƫ�� 
* 		count: 	��ȡ����������
* 		readLen: �����ȡ�����ݵĳ���
* @return : ��ȡ֮������ݣ� 	
* @notice: ע��Ҫ�ͷ�malloc ֮�������,  ���ص�ʱ�� �ļ���ƫ���������ú��ˡ� 
* 			֧�ֵ�64λ��  
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
		cout<<" �ڴ����ʧ��"<<endl;
		return NULL;
	}
	memset(buffer, '\0', count);
#ifdef WINDOWSCODE
	__int64  cur_len= _lseeki64( fileno(file), 0, SEEK_CUR);
	_lseeki64(fileno(file), 0, SEEK_END);
	//��ȡ�ļ����ȡ�
	long long  length=_lseeki64(fileno(file), 0, SEEK_CUR);
#else
	int cur_len= lseek64( fileno(file), 0, SEEK_CUR);
	lseek64(fileno(file), 0, SEEK_END);
	//��ȡ�ļ����ȡ�
	long long  length=lseek64(fileno(file), 0, SEEK_CUR);
#endif

	//�����offset �����ļ��ĳ��ȡ� 
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

	//���ļ�ĩβ��ʱ��, ��ȡ���ֽڻ�< count. 	
	if(length -offset < count)
	{
		fseek(file, offset, SEEK_SET);
		//д��  fread(tmp, sizeof(tmp), 1 , file)���� ��ȡ�˼����ṹ
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

