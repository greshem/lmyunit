#include <stdlib.h>
#include <unitlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string> 
#include <fstream>
#include <iterator>  
#include <vector> 
#include <algorithm>
#include <iostream> 
#include <map>
#include <gtest/gtest.h>
#ifdef WINDOWSCODE
#else
#include <stringprep.h>
#endif
#include <locale.h>
//2010_08_27 by greshem. 
//1.tar 文件， 文件后面有很多的填充的扇区， 最少是10k的文件， 好像， 可以用 几个小的文件测试一下。 
//2. 最后填充的 block 不一定只有一个, 记得有些资料上说是1个其实是错误的。  
//name[100] 
//#2010_09_01_18:54:19 add by greshem , 这里很重要。 
//setlocale (LC_ALL, ""), 否则会失败的。 

template <typename T> class book {
};
typedef struct tar_header
{
char name[100];
char mode[8];
char uid[8];
char gid[8];
char size[12];
char mtime[12];
char chksum[8];
char typeflag;
char linkname[100];
char magic[6];
char version[2];
char uname[32];
char gname[32];
char devmajor[8];
char devminor[8];
char prefix[155];
char padding[12];
} HEADER;

MLogFile logger;
using namespace std;
int dump_one_tar(string filename);

int main(int argc, char *argv[])
{
	logger.Instance(MString(argv[0])+".log", 1000);
	logger.WriteError("test", "test");

	if(argc < 2)
	{
		die("Usage: %s file.tar ", argv[0]);
	}
	for(int i=1; i< argc; i++)
	{
		string filename(argv[i]);
		dump_one_tar( filename);
		//cout<<filename<<endl;

	}

	
	return 0;
}
int dump_one_tar(string filename)
{
	HEADER tmp;
	assert(sizeof(tmp)==512);
	char buf[BUFSIZ];

	//ofstream output("name.list");
	MFile tar;
	if(tar.Open(filename.c_str()) != 1)
	{
		die("open file error\n");
	}

	setlocale (LC_ALL, "");
	long long Length=filesize(filename);
	assert(Length%512==0);
	while(	  tar.GetCurOffset() != Length )
	{
		//cout<<"###################"<<endl;
		// if((Length - tar.GetCurOffset()) ==512)
		// {
		// 	die("at the end of tar file \n");
		// 	break;
		// }
		//注意需要重新设置， 每个循环的变量用的时候初始化。 
		int ret=0;
		int pad=0;
		char *p;
		ret=tar.Read((char *) &tmp, sizeof(tmp)) ;
		//cout<<"读入"<<ret<<"字节"<<endl;
		if(ret ==0 )
		{
			break;
		}
		if(ret != 512)
		{

			cout<<"在 "<<tar.GetCurOffset()<<"处， 读入的数据不为 512"<<"为"<<ret<<endl; 
			die(" ############");
		}
		//cout<<"ftell "<<tar.GetCurOffset()<<endl;
		//assert(tar.GetCurOffset()%512==0);
		long long size=strtoull(tmp.size, NULL, 8);
		if(tmp.name[0]!='\0')
		{
			//cout<<"name "<<tmp.name<<endl;
			//cout<<"size "<<size<<endl;
			//cout<<"./fseek_and_print_v7 "<< filename<< "\t"<< tar.GetCurOffset()<<"\t"<< size<<"\t"<<" > "<<basename(tmp.name)<<endl;
			//cout<<"./fseek_and_print_v7 "<< filename<< "\t"<< tar.GetCurOffset()<<"\t"<< size<<"\t"<<" > "<<tmp.name<<endl;
			//if(size==0)
			{
				p=stringprep_utf8_to_locale(tmp.name);
				if(p)
				//MFile::CreateDirectoryTree();
				{
					//cout<<<<endl;
					printf("##### %s\n", p);
					free(p);
				}
				else
				{
					printf("Error,cann't changge to utf8\n");
				}
			}
		}
		tar.Seek(size, SEEK_CUR);
		if(size%512!=0)
		{
			pad=512-size%512;
		}
		//cout<<"Pad"<<pad<<endl;
		tar.Seek(pad, SEEK_CUR);	
	}
	tar.Close();
	return 1;
}
