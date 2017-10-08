//###############################################################################/
//                  ;;;,
//        ,;;;;;: ,;;;:.,;..
//         :;;"`,;;;;;;"":;;					单元名称：文件读写处理
//      ..;;:  .;;,.;;:',;;"
//    ,;;;;;;" :;`',;",;;"						编写日期：2010年8月12, 全部转换成stl
//   :" ,;:` , `:.;;;;;'
//    ,;;;,;:;;,;;;, ,;							编写人员：qianzj
//   :;;;"` `:;;;;;,;,.;.
//   '""   .;;`.;";:;;;;` ;,					备注信息：
//       .;"`  ::. '   .,;;;
//      ""     ';;;;;;;;;;`
//############################################################################### 
#ifndef __LmyUnitMFileH__
#define __LmyUnitMFileH__
//############################################################################### 
//公共头文件
//#include "MObject.h"
#include <string> 
#include <vector>
#include "MString.hpp"
#include "MDateTime.hpp"
//###############################################################################
#ifdef WINDOWSCODE
//Windows操作系统
#include "io.h"
#else
//Linux操作系统
#include <sys/types.h>
#include <sys/stat.h>
#include <utime.h>
#include <fcntl.h>
#include <dirent.h>
#endif
//###############################################################################	
//#pragma pack(1)
//###############################################################################	
template <typename T> class  tagFileFindFileInfo

{
	char					filename[32];			//文件名称
	unsigned long			fileAttr;				//文件属性
	unsigned long			filesize;				//文件大小
	MDateTime<T>				CreateTime;				//创建时间
	MDateTime<T>				UpdateTime;				//更新时间
	MDateTime<T>				AccessTime;				//访问时间
} ;
//###############################################################################	
//#pragma pack()
//###############################################################################	
enum
{
	MFILE_OPENMODE_READ = 0x01,															//打开文件读取
	MFILE_OPENMODE_WRITE = 0x02,														//打开文件写
	MFILE_OPENMODE_READWRITE = MFILE_OPENMODE_READ | MFILE_OPENMODE_WRITE,				//打开文件读写
	MFILE_OPENMODE_NOTHING = 0x00,														//不允许共享
	MFILE_OPENMODE_SHAREREAD = 0x04,													//允许共享读
	MFILE_OPENMODE_SHAREWRITE = 0x08,													//允许共享写
	MFILE_OPENMODE_SHAREALL = MFILE_OPENMODE_SHAREREAD | MFILE_OPENMODE_SHAREWRITE,		//允许共享读写
};

//###############################################################################	
enum
{
	MFILE_ATTR_NORMAL = 0x00,															//普通文件
	MFILE_ATTR_READONLY = 0x01,															//只读文件
	MFILE_ATTR_HIDDEN = 0x02,															//隐藏文件
	MFILE_ATTR_SYSTEM = 0x04,															//系统文件
	MFILE_ATTR_VOLUME = 0x08,															//卷标
	MFILE_ATTR_DIRECTORY = 0x10,														//目录
	MFILE_ATTR_ARCHIVE = 0x20,															//存档文件
};

//###############################################################################	
template <typename T> class MFile //: public MObject
{
protected:

#ifdef WINDOWSCODE
	HANDLE						m_FileHandle;
#else
	long						m_FileHandle;
	char						m_FileName[256];
	FILE						*m_FilePtr;
#endif

public:
	MFile<T>(void);
	virtual ~MFile<T>();
public:
	int  Open(MString<T> FileName,unsigned long Mode = MFILE_OPENMODE_READ | MFILE_OPENMODE_SHAREALL);
	int  Create(MString<T> FileName);
	void Close(void);
public:
	int  Seek(long Offset,unsigned long FromType);
	long  long  GetCurOffset();
	int  SetFileLength(unsigned long FileLength);
	int  SetFileLength(void);
	unsigned long GetFileLength(void);
public:
	int  Read(char * OutBuf,unsigned long InSize);
	int  Write(char * InBuf,unsigned long InSize);
public:
	MString<T> ReadString(void);
	MString<T>  ReadWord();
	int  ReadString(MString<T> * Out);
	int  WriteString(string in);
	int  WriteString(MString<T> In);
	//MString fgets();
public:
	int  LockFile(long Offset,unsigned long Size);
	int  UnLockFile(long Offset,unsigned long Size);
public:
	MDateTime<T> GetCreateDateTime(void);
	MDateTime<T> GetUpdateDateTime(void);
	MDateTime<T> GetAccessDateTime(void);
public:
	int  SetCreateDateTime(MDateTime <T>In);
	int  SetUpdateDateTime(MDateTime <T>In);
	int  SetAccessDateTime(MDateTime <T>In);
public:
	void Flush(void);
public:
	static unsigned long GetFileAttributes(MString<T> FileName);
	static int  SetFileAttributes(MString<T> FileName,unsigned long Attributes);
public:
	static int  RenameFileName(MString<T> SourceFile,MString<T> NewFile);
	static int  DeleteFile(MString<T> FileName);
	static int  CreateDirectory(MString<T> FileName);
	static int  DeleteDirectory(MString<T> FileName);
	static int  CreateDirectoryTree(MString<T> DirTreeName);
	static MString<T> GetCurrentDirectory(void);
	static int  SetCurrentDirectory(MString<T> In);
	static bool IsExist(MString<T> FileName);
	static int  CopyFile(MString<T> SourceFile,MString<T> NewFile,bool FailIfExists);

//	DECLARE_LMYUNIT(MFile)
};
//###############################################################################	
template <typename T>
class MFindFile
{
protected:

#ifdef WINDOWSCODE
	HANDLE						m_Handle;
#else
	DIR						*	m_Handle;
	char						m_pathname[256];
	char						m_match[32];
#endif

protected:
	int  FindingString(const char* lpszSour, const char* lpszFind, int nStart);
	bool MatchingString(const char* lpszSour, const char* lpszMatch, bool bMatchCase = true);
public:
	MFindFile(void);
	virtual ~MFindFile();
public:
	int  FindFirstFile(char * FileName,tagFileFindFileInfo<T> * Out);
	int  FindNextFile(tagFileFindFileInfo<T> * Out);
	void CloseFindFile(void);
};


//############################################################################### 
//###############################################################################	
template <typename T> MFile<T>::MFile(void)
{
#ifdef WINDOWSCODE
	m_FileHandle = INVALID_HANDLE_VALUE;
#else
	m_FileHandle = -1;
#endif
}

//###############################################################################	
template <typename T> MFile<T>::~MFile()
{
	Close();
}

//###############################################################################	
 template <typename T>int  MFile<T>::Open(MString<T> FileName,unsigned long Mode)
{
#ifdef WINDOWSCODE
	register unsigned long				openmode = 0;
	register unsigned long				sharemode = 0;

	Close();

	if ( (Mode & MFILE_OPENMODE_READ) != 0 )
	{
		openmode |= GENERIC_READ;
	}

	if ( (Mode & MFILE_OPENMODE_WRITE) != 0 )
	{
		openmode |= GENERIC_WRITE;
	}

	if ( (Mode & MFILE_OPENMODE_SHAREREAD) != 0 )
	{
		sharemode |= FILE_SHARE_READ;
	}

	if ( (Mode & MFILE_OPENMODE_SHAREWRITE) != 0 )
	{
		sharemode |= FILE_SHARE_WRITE;
	}

	m_FileHandle = ::CreateFile(	FileName.c_str(),
									openmode,
									sharemode,
									NULL,
									OPEN_EXISTING,
									FILE_ATTRIBUTE_NORMAL,
									NULL	);
	if ( m_FileHandle == INVALID_HANDLE_VALUE )
	{
//		return(ERROR_SYSTEM(GetLastError()));
				return -1;
	}

	return(1);
#else
	register unsigned long				openmode = 0;
	register unsigned long				sharemode = 0;
	
	strncpy(m_FileName,FileName.c_str(),256);

	Close();

	if ( (Mode & MFILE_OPENMODE_READ) != 0 && (Mode & MFILE_OPENMODE_WRITE) != 0 )
	{
		openmode |= O_RDWR;
	}
	else if ( (Mode & MFILE_OPENMODE_READ) != 0 )
	{
		openmode |= O_RDONLY;
	}
	else if ( (Mode & MFILE_OPENMODE_WRITE) != 0 )
	{
		openmode |= O_WRONLY;
	}
	
	if ( (Mode & MFILE_OPENMODE_SHAREREAD) != 0 )
	{
		sharemode |= S_IROTH;
	}

	if ( (Mode & MFILE_OPENMODE_SHAREWRITE) != 0 )
	{
		sharemode |= S_IWOTH;
	}

	m_FileHandle = open(FileName.c_str(),openmode,sharemode);
	if ( m_FileHandle < 0 )
	{
		//return(ERROR_SYSTEM(GetLastError()));
		return -1;
	}

	return(1);
#endif
}

//###############################################################################	
 template <typename T>int  MFile<T>::Create(MString<T> FileName)
{
#ifdef WINDOWSCODE
	Close();

	m_FileHandle = ::CreateFile(	FileName.c_str(),
									GENERIC_READ | GENERIC_WRITE,
									FILE_SHARE_READ | FILE_SHARE_WRITE,
									NULL,
									CREATE_NEW,
									FILE_ATTRIBUTE_NORMAL,
									NULL	);
	if ( m_FileHandle == INVALID_HANDLE_VALUE )
	{
//		return(ERROR_SYSTEM(GetLastError()));
				return -1;
	}

	return(1);
#else
	strncpy(m_FileName,FileName.c_str(),256);
	
	Close();

	m_FileHandle = open(FileName.c_str(),O_CREAT | O_RDWR,S_IRWXU | S_IRWXG | S_IRWXO);
	if ( m_FileHandle < 0 )
	{
		//return(ERROR_SYSTEM(GetLastError()));
		return -1;
	}

	return(1);
#endif
}

//###############################################################################	
 template <typename T>void MFile<T>::Close(void)
{
#ifdef WINDOWSCODE
	if ( m_FileHandle != INVALID_HANDLE_VALUE )
	{
		::CloseHandle(m_FileHandle);
		m_FileHandle = INVALID_HANDLE_VALUE;
	}
#else
	if ( m_FileHandle >= 0 )
	{
		close(m_FileHandle);
		m_FileHandle = -1;
	}
#endif
}

//###############################################################################	
 template <typename T>int  MFile<T>::Seek(long Offset,unsigned long FromType)
{
#ifdef WINDOWSCODE
	register int						errorcode;

	errorcode = ::SetFilePointer(m_FileHandle,Offset,0,FromType);
	if ( errorcode == 0xFFFFFFFF )
	{
//		return(ERROR_SYSTEM(GetLastError()));
				return -1;
	}
	else
	{
		return(errorcode);
	}
#else
	register int						errorcode;
	
	errorcode = lseek(m_FileHandle,Offset,FromType);
	if ( errorcode < 0 )
	{
		//return(ERROR_SYSTEM(GetLastError()));
		return -1;
	}
	else
	{
		return(errorcode);	
	}
#endif
}

template <typename T>  long long MFile<T>::GetCurOffset()
{
#ifdef WINDOWSCODE
//#warn "GetCurOffset not support in windows\n";
	return -1;
#else
	register int						errorcode;
	
	errorcode = lseek(m_FileHandle,0,SEEK_CUR);
	if ( errorcode < 0 )
	{
		//return(ERROR_SYSTEM(GetLastError()));
		return -1;
	}
	else
	{
		return(errorcode);	
	}
#endif
}

//###############################################################################	
 template <typename T>int  MFile<T>::SetFileLength(unsigned long FileLength)
{
#ifdef WINDOWSCODE
	register int						errorcode;

	errorcode = ::SetFilePointer(m_FileHandle,FileLength,0,0);
	if ( errorcode == 0xFFFFFFFF )
	{
//		return(ERROR_SYSTEM(GetLastError()));
				return -1;
	}

	if ( ::SetEndOfFile(m_FileHandle) != 0 )
	{
		return(1);
	}
	else
	{
//		return(ERROR_SYSTEM(GetLastError()));
				return -1;
	}
#else
	register int						errorcode;
	register int						oldptr;
	
	oldptr = lseek(m_FileHandle,0,SEEK_CUR);
	if ( oldptr < 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
				return -1;
	}
	
	errorcode = ftruncate(m_FileHandle,FileLength);
	if ( errorcode < 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
				return -1;
	}
	
	if ( lseek(m_FileHandle,oldptr,SEEK_SET) < 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));	
				return -1;
	}
	
	return(1);
#endif
}

//###############################################################################	
 template <typename T>int  MFile<T>::SetFileLength(void)
{
#ifdef WINDOWSCODE
	if ( ::SetEndOfFile(m_FileHandle) != 0 )
	{
		return(1);
	}
	else
	{
	//	return(ERROR_SYSTEM(GetLastError()));
				return -1;
	}
#else
	register int				oldptr;
	
	oldptr = lseek(m_FileHandle,0,SEEK_CUR);
	if ( oldptr < 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
				return -1;
	}
	
	if ( ftruncate(m_FileHandle,oldptr) < 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
				return -1;
	}
	
	return(1);
#endif
}
//###############################################################################	
 template <typename T>unsigned long MFile<T>::GetFileLength(void)
{
	register int					errorcode;

	if ( (errorcode = Seek(0,SEEK_END)) < 0 )
	{
		return(0);
	}
	else
	{
		return(errorcode);
	}
}

//###############################################################################	
 template <typename T>int  MFile<T>::Read(char * OutBuf,unsigned long InSize)
{
#ifdef WINDOWSCODE
	register unsigned long					errorcode = 0;

	if ( ::ReadFile(m_FileHandle,OutBuf,InSize,&errorcode,NULL) == 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
				return -1;
	}
	else
	{
		return(errorcode);
	}
#else
	register int							errorcode;
	
	if ( (errorcode = read(m_FileHandle,OutBuf,InSize)) < 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));	
				return -1;
	}
	else
	{
		return(errorcode);	
	}
#endif
}

//###############################################################################	
 template <typename T>int  MFile<T>::Write(char * InBuf,unsigned long InSize)
{
#ifdef WINDOWSCODE
	register unsigned long					errorcode = 0;

	if ( ::WriteFile(m_FileHandle,InBuf,InSize,&errorcode,NULL) == 0 )
	{
		//return(ERROR_SYSTEM(GetLastError()));
				return -1;
	}
	else
	{
		return(errorcode);
	}
#else
	register int							errorcode;
	
	if ( (errorcode = write(m_FileHandle,InBuf,InSize)) < 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
				return -1;
	}
	else
	{
		return(errorcode);
	}
#endif
}
//###############################################################################	
//MString MFile::fgets(void)
//{
//	long						m_FileHandle;
//	FILE *stream;
//	stream=fdopen(m_FileHandle, "w");
//}
//

//###############################################################################
/****************************************************************************
* Description	
* @param 	
* @return 	
* *************************************************************************/
template <typename T>MString<T> MFile<T>::ReadString(void)
{
	char						tempbuf[4096];
	register int				errorcode;
	register int				position;
	register int				i;

	position = Seek(0,SEEK_CUR);
	errorcode = Read(tempbuf,4096);
	Seek(position,SEEK_SET);

	if ( errorcode < 0 )
	{
		return(errorcode);
	}


	//处理WINDOWS 格式的时候， 注意  errocode -2  
	for ( i=0;i<=errorcode-1;i++ )
	{
		//0x0A才是换行符。 linux 
		if ( tempbuf[i] == 0x0A ) //&& tempbuf[i+1] == 0x0A )
		{
			tempbuf[i] = '\0';
			return(tempbuf);
		}
	}

	tempbuf[errorcode] = 0;
	return(tempbuf);
}

/****************************************************************************
* Description	 主要为了处理 /usr/share/dict/linux.words 获取的 word 的完整性
* @param 	
* @return 	 返回 , 一般的 常见的英文单词. 
* *************************************************************************/
//###############################################################################	
template <typename T>MString<T> MFile<T>::ReadWord()
{
	
	char						tempbuf[4096];
	register int				errorcode;
	register int				position;
	register int				i;
	
	static int   	wordLen=8;	
	int lastPos =0;
	position = Seek(0,SEEK_CUR);
	errorcode = Read(tempbuf,4096);
	Seek(position,SEEK_SET);

	if ( errorcode < 0 )
	{
		return(errorcode);
	}


	if(tempbuf[0]==0x0A)
	{
		*tempbuf='a';
	}	
	//处理WINDOWS 格式的时候， 注意  errocode -2  
	for ( i=0;i<=errorcode-1;i++ )
	{
		//0x0A才是换行符。 linux 
		if ( tempbuf[i] == 0x0A ) //&& tempbuf[i+1] == 0x0A )
		{
			tempbuf[i] = '\0';
			//这是个比较合理的英文word 
			//if(i-lastPos>= wordLen)
			if(i-lastPos>= wordLen)
			{
				memmove(tempbuf, tempbuf+lastPos+1, i-lastPos);
				return(tempbuf);
			}
			else
			{
				lastPos=i;	
			}
		}
	}

	tempbuf[errorcode] = 0;
	return(tempbuf);

}

//###############################################################################	
 template <typename T>int  MFile<T>::ReadString(MString <T>* Out)
{
	char						tempbuf[4096];
	register int				errorcode;
	register int				position;
	register int				i;
	
	position = Seek(0,SEEK_CUR);
	errorcode = Read(tempbuf,4095);
	Seek(position,SEEK_SET);

	if ( errorcode <= 0 )
	{
		return(errorcode);
	}
	
	
	for ( i=0;i<=errorcode-2;i++ )
	{
		if ( tempbuf[i] == 0x0D && tempbuf[i+1] == 0x0A )
		{
			tempbuf[i] = 0;
			* Out = tempbuf;

			Seek(position + i + 2,SEEK_SET);

			return(1);
		}
	}
	
	tempbuf[errorcode] = 0;
	* Out = tempbuf;

	Seek(position + errorcode,SEEK_SET);

	return(1);
}

//###############################################################################	
 template <typename T>int  MFile<T>::WriteString(MString<T> In)
{
	In += "\n";

	return(Write(In.c_str(),In.Length()));
}
 template <typename T>int MFile<T>::WriteString(string in)
{
	MString<T> tmp(in.c_str());
	tmp+="\n";
	return(Write(tmp.c_str(),tmp.Length()));
}

//###############################################################################	
 template <typename T> int  MFile<T>::LockFile(long Offset,unsigned long Size)
{
#ifdef WINDOWSCODE
	if ( ::LockFile(m_FileHandle,Offset,0,Size,0) == 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
				return -1;
	}
	else
	{
		return(1);
	}
#else
	struct flock 				lock;
	
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = Offset;
	lock.l_len = Size;
	
	if ( fcntl(m_FileHandle,F_SETLK,&lock) < 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
				return -1;
	}
	else
	{
		return(1);	
	}
#endif
}

//###############################################################################	
 template <typename T>int  MFile<T>::UnLockFile(long Offset,unsigned long Size)
{
#ifdef WINDOWSCODE
	if ( ::UnlockFile(m_FileHandle,Offset,0,Size,0) == 0 )
	{
		//return(ERROR_SYSTEM(GetLastError()));
				return -1;
	}
	else
	{
		return(1);
	}
#else
	struct flock 				lock;
	
	lock.l_type = F_UNLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = Offset;
	lock.l_len = Size;
	
	if ( fcntl(m_FileHandle,F_SETLK,&lock) < 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
				return -1;
	}
	else
	{
		return(1);	
	}
#endif
}
//###############################################################################	
 template <typename T> MDateTime<T> MFile<T>::GetCreateDateTime(void)
{
#ifdef WINDOWSCODE
	FILETIME					createtime,updatetime,accesstime,localtime;
	SYSTEMTIME					systemtime;

	if ( ::GetFileTime(m_FileHandle,&createtime,&accesstime,&updatetime) == 0 )
	{
		return(MDateTime(0));
	}

	::FileTimeToLocalFileTime(&createtime, &localtime );
	::FileTimeToSystemTime(&localtime,&systemtime);

	return(		MDateTime<T>(	systemtime.wYear,
							systemtime.wMonth,
							systemtime.wDay,
							systemtime.wHour,
							systemtime.wMinute,
							systemtime.wSecond	)	);
#else
	struct stat					errorcode;
	
	if ( fstat(m_FileHandle,&errorcode) < 0 )
	{
		return(MDateTime<T>(0));
	}
	
	return(MDateTime<T>(errorcode.st_ctime));
#endif
}
//###############################################################################	
 template <typename T> MDateTime<T> MFile<T>::GetUpdateDateTime(void)
{
#ifdef WINDOWSCODE
	FILETIME					createtime,updatetime,accesstime,localtime;
	SYSTEMTIME					systemtime;

	if ( ::GetFileTime(m_FileHandle,&createtime,&accesstime,&updatetime) == 0 )
	{
		return(MDateTime(0));
	}
	
	::FileTimeToLocalFileTime(&updatetime, &localtime );
	::FileTimeToSystemTime(&localtime,&systemtime);

	return(		MDateTime<T>(	systemtime.wYear,
							systemtime.wMonth,
							systemtime.wDay,
							systemtime.wHour,
							systemtime.wMinute,
							systemtime.wSecond	)	);
#else
	struct stat					errorcode;
	
	if ( fstat(m_FileHandle,&errorcode) < 0 )
	{
		return(MDateTime<T>(0));
	}
	
	return(MDateTime<T>(errorcode.st_mtime));
#endif
}
//###############################################################################	
 template <typename T> MDateTime<T> MFile<T>::GetAccessDateTime(void)
{
#ifdef WINDOWSCODE
	FILETIME					createtime,updatetime,accesstime,localtime;
	SYSTEMTIME					systemtime;

	if ( ::GetFileTime(m_FileHandle,&createtime,&accesstime,&updatetime) == 0 )
	{
		return(MDateTime(0));
	}

	::FileTimeToLocalFileTime(&accesstime, &localtime );
	::FileTimeToSystemTime(&localtime,&systemtime);
	return(		MDateTime<T>(	systemtime.wYear,
							systemtime.wMonth,
							systemtime.wDay,
							systemtime.wHour,
							systemtime.wMinute,
							systemtime.wSecond	)	);
#else
	struct stat					errorcode;
	
	if ( fstat(m_FileHandle,&errorcode) < 0 )
	{
		return(MDateTime<T>(0));
	}
	
	return(MDateTime<T>(errorcode.st_atime));
#endif
}

//###############################################################################	
 template <typename T> int  MFile<T>::SetCreateDateTime(MDateTime <T>In)
{
#ifdef WINDOWSCODE
	FILETIME					filetime,utcfiletime;
	SYSTEMTIME					systemtime;
	
	memset( &systemtime, 0, sizeof(SYSTEMTIME) );
	In.DecodeDate(&systemtime.wYear,&systemtime.wMonth,&systemtime.wDay);
	In.DecodeTime(&systemtime.wHour,&systemtime.wMinute,&systemtime.wSecond);

	::SystemTimeToFileTime(&systemtime,&filetime);
	::LocalFileTimeToFileTime( &filetime, &utcfiletime );
	if ( ::SetFileTime(m_FileHandle,&utcfiletime,NULL,NULL) == 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
		return -1;
	}
	else
	{
		return(1);
	}
#else
	return(-1);
#endif
}
//###############################################################################	
 template <typename T>int  MFile<T>::SetUpdateDateTime(MDateTime<T> In)
{
#ifdef WINDOWSCODE
	FILETIME					filetime,utcfiletime;
	SYSTEMTIME					systemtime;

	memset( &systemtime, 0, sizeof(SYSTEMTIME) );
	In.DecodeDate(&systemtime.wYear,&systemtime.wMonth,&systemtime.wDay);
	In.DecodeTime(&systemtime.wHour,&systemtime.wMinute,&systemtime.wSecond);
	
	::SystemTimeToFileTime(&systemtime,&filetime);
	::LocalFileTimeToFileTime( &filetime, &utcfiletime );
	if ( ::SetFileTime(m_FileHandle,NULL,NULL,&utcfiletime) == 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
		return -1;
	}
	else
	{
		return(1);
	}
#else
	struct utimbuf 				errorcode;
	
	errorcode.modtime = In.DateTimeToTimet(); 
	if ( utime(m_FileName,&errorcode) < 0 )
	{
		//return(ERROR_SYSTEM(GetLastError()));
		return -1;
	}
	else
	{
		return(1);	
	}
#endif
}
//###############################################################################	
template <typename T>int  MFile<T>::SetAccessDateTime(MDateTime<T> In)
{
#ifdef WINDOWSCODE
	FILETIME					filetime,utcfiletime;
	SYSTEMTIME					systemtime;

	memset( &systemtime, 0, sizeof(SYSTEMTIME) );
	In.DecodeDate(&systemtime.wYear,&systemtime.wMonth,&systemtime.wDay);
	In.DecodeTime(&systemtime.wHour,&systemtime.wMinute,&systemtime.wSecond);

	::SystemTimeToFileTime(&systemtime,&filetime);
	::LocalFileTimeToFileTime( &filetime, &utcfiletime );	
	if ( ::SetFileTime(m_FileHandle,NULL,&utcfiletime,NULL) == 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
		return -1;
	}
	else
	{
		return(1);
	}
#else
	struct utimbuf 				errorcode;
	
	errorcode.actime = In.DateTimeToTimet(); 
	if ( utime(m_FileName,&errorcode) < 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
		return -1;
	}
	else
	{
		return(1);	
	}
#endif
}

//############################################################################### 
template <typename T>void MFile<T>::Flush(void)
{
#ifdef WINDOWSCODE
	::FlushFileBuffers(m_FileHandle);
#else
	fsync(m_FileHandle);
#endif
}

//############################################################################### 
 template <typename T> unsigned long MFile<T>::GetFileAttributes(MString<T> FileName)
{
#ifdef WINDOWSCODE
	register unsigned long				errorcode;
	register unsigned long				returncode = 0;

	errorcode = ::GetFileAttributes(FileName.c_str());
	
	if ( (errorcode & FILE_ATTRIBUTE_READONLY) != 0 )
	{
		returncode |= MFILE_ATTR_READONLY;
	}

	if ( (errorcode & FILE_ATTRIBUTE_HIDDEN) != 0 )
	{
		returncode |= MFILE_ATTR_HIDDEN;
	}

	if ( (errorcode & FILE_ATTRIBUTE_SYSTEM) != 0 )
	{
		returncode |= MFILE_ATTR_SYSTEM;
	}

	if ( (errorcode & FILE_ATTRIBUTE_DIRECTORY) != 0 )
	{
		returncode |= MFILE_ATTR_DIRECTORY;
	}

	if ( (errorcode & FILE_ATTRIBUTE_ARCHIVE) != 0 )
	{
		returncode |= MFILE_ATTR_ARCHIVE;
	}

	return(returncode);
#else
	return(0);
#endif
}

//############################################################################### 
 template <typename T>int  MFile<T>::SetFileAttributes(MString<T> FileName,unsigned long Attributes)
{
#ifdef WINDOWSCODE
	register unsigned long					errorcode = 0;

	if ( (Attributes & MFILE_ATTR_READONLY) != 0 )
	{
		errorcode |= FILE_ATTRIBUTE_READONLY;
	}

	if ( (Attributes & MFILE_ATTR_HIDDEN) != 0 )
	{
		errorcode |= FILE_ATTRIBUTE_HIDDEN;
	}

	if ( (Attributes & MFILE_ATTR_SYSTEM) != 0 )
	{
		errorcode |= FILE_ATTRIBUTE_SYSTEM;
	}

	if ( (Attributes & MFILE_ATTR_DIRECTORY) != 0 )
	{
		errorcode |= FILE_ATTRIBUTE_DIRECTORY;
	}

	if ( (Attributes & MFILE_ATTR_ARCHIVE) != 0 )
	{
		errorcode |= FILE_ATTRIBUTE_ARCHIVE;
	}

	if ( ::SetFileAttributes(FileName.c_str(),errorcode) == 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
		return -1;
	}
	else
	{
		return(1);
	}
#else
	return(-1);
#endif
}

//############################################################################### 
 template <typename T> int  MFile<T>::RenameFileName(MString<T> SourceFile,MString<T> NewFile)
{
#ifdef WINDOWSCODE
	if ( ::MoveFile(SourceFile.c_str(),NewFile.c_str()) == 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
		return -1;
	}

	return(1);
#else
	if ( rename(SourceFile.c_str(),NewFile.c_str()) < 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
		return -1;
	}
	
	return(1);
#endif
}
//############################################################################### 
 template <typename T> int  MFile<T>::DeleteFile(MString<T> FileName)
{
#ifdef WINDOWSCODE
	if ( ::DeleteFile(FileName.c_str()) == 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
		return -1;
	}

	return(1);
#else
	if ( remove(FileName.c_str()) < 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
		return -1;
	}

	return(1);
#endif
}
//############################################################################### 
template <typename T> int  MFile<T>::CreateDirectory(MString<T> FileName)
{
#ifdef WINDOWSCODE
	if ( ::CreateDirectory(FileName.c_str(),NULL) == 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
		return -1;
	}

	return(1);
#else
	if ( mkdir(FileName.c_str(),0x1FF) < 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
		return -1;
	}
	
	return(1);
#endif
}
//############################################################################### 
 template <typename T> int  MFile<T>::DeleteDirectory(MString<T> FileName)
{
#ifdef WINDOWSCODE
	if ( ::RemoveDirectory(FileName.c_str()) == 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
		return -1;
	}

	return(1);
#else
	if ( rmdir(FileName.c_str()) < 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
		return -1;
	}
	
	return(1);
#endif
}
// ############################################################################### 
template <typename T> int  MFile<T>::CreateDirectoryTree(MString<T> DirTreeName)
{
	char				dirtree[256];
	char				tempbuf[256];
	register int		i;
	register int		errorcode;

	strncpy(dirtree,DirTreeName.c_str(),256);
	errorcode = strlen(dirtree);
	for ( i=0;i<=errorcode-1;i++ )
	{
		if ( i > 0 && (dirtree[i] == '\\' || dirtree[i] == '/') && dirtree[i-1] != '.' && dirtree[i-1] != ':' )
		{
			memcpy(tempbuf,dirtree,i);
			tempbuf[i] = 0;
			
			MFile<T>::CreateDirectory(tempbuf);
		}
	}
	
	MFile::CreateDirectory(dirtree);
	
	return(1);
}
//############################################################################### 
 template <typename T> MString<T> MFile<T>::GetCurrentDirectory(void)
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
//############################################################################### 
 template <typename T> int  MFile<T>::SetCurrentDirectory(MString<T> In)
{
#ifdef WINDOWSCODE
	if ( ::SetCurrentDirectory(In.c_str()) == 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
		return -1;
	}

	return(1);
#else
	if ( chdir(In.c_str()) < 0 )
	{
	//	return(	ERROR_SYSTEM(GetLastError()));
		return -1;
	}
	
	return(1);
#endif
}
//###############################################################################/
 template <typename T> bool MFile<T>::IsExist(MString<T> FileName)
{
#ifdef WINDOWSCODE
	if ( _access(FileName.c_str(),0) == -1 )
	{
		return(false);
	}
	
	return(true);
#else
	if ( access(FileName.c_str(),0) == -1 )
	{
		return(false);
	}
	
	return(true);
#endif
}
//############################################################################### 
 template <typename T> int  MFile<T>::CopyFile(MString <T> SourceFile,MString<T> NewFile,bool FailIfExists)
{
#ifdef WINDOWSCODE
	BOOL					flag;

	if ( FailIfExists == true )
	{
		flag = TRUE;
	}
	else
	{
		flag = FALSE;
	}

	if ( ::CopyFile(SourceFile.c_str(),NewFile.c_str(),flag) == 0 )
	{
	//	return(ERROR_SYSTEM(GetLastError()));
		return -1;
	}

	return(1);
#else
	MFile<T>						sourceptr;
	MFile<T>						newfileptr;
	char						tempbuf[4096];
	int							sourcefilesize;
	int							errorcode;
	int							framecount;
	int							getcount;
	register int				i;
	
	if( MFile::IsExist( NewFile ) && FailIfExists )
		return (-2);
	
	if ( (errorcode = sourceptr.Open(SourceFile)) < 0 )
	{
		return(errorcode);
	}
	
	sourcefilesize = sourceptr.Seek(0,SEEK_END);
	
	framecount = (sourcefilesize % 4096 == 0)?(sourcefilesize / 4096):(sourcefilesize / 4096 + 1);
	if ( framecount < 0 )
	{
		sourceptr.Close();
		newfileptr.Close();
		
		return(-1);
	}
	
	MFile<T>::DeleteFile( NewFile );
	if ( (errorcode = newfileptr.Create(NewFile)) < 0 )
	{
		sourceptr.Close();
		return(errorcode);
	}
	
	sourceptr.Seek(0,SEEK_SET);
	newfileptr.Seek(0,SEEK_SET);
	
	for ( i=0;i<framecount;i++ )
	{
		getcount = (i == framecount - 1)?(sourcefilesize - i * 4096):4096;
		
		sourceptr.Read(tempbuf,getcount);
		newfileptr.Write(tempbuf,getcount);
	}
	
	sourceptr.Close();
	newfileptr.Close();
	
	return(1);
#endif
}
//############################################################################### 
template <typename T >  MFindFile<T>::MFindFile(void)
{
	#ifdef WINDOWSCODE
		m_Handle = INVALID_HANDLE_VALUE;
	#else
		m_Handle = NULL;
	#endif
}
//############################################################################### 
template <typename T> MFindFile<T>::~MFindFile()
{
	CloseFindFile();
}
//###############################################################################/
 template <typename T>int MFindFile<T>::FindingString(const char* lpszSour, const char* lpszFind, int nStart /* = 0 */)
{
//	ASSERT(lpszSour && lpszFind && nStart >= 0);
	if(lpszSour == NULL || lpszFind == NULL || nStart < 0)
		return -1;

	int m = strlen(lpszSour);
	int n = strlen(lpszFind);

	if( nStart+n > m )
		return -1;

	if(n == 0)
		return nStart;

	//KMP算法
	int* next = new int[n];
	//得到查找字符串的next数组
	{	n--;

		int j, k;
		j = 0;
		k = -1;
		next[0] = -1;

		while(j < n)
		{	if(k == -1 || lpszFind[k] == '?' || lpszFind[j] == lpszFind[k])
			{	j++;
				k++;
				next[j] = k;
			}
			else
				k = next[k];
		}

		n++;
	}

	int i = nStart, j = 0;
	while(i < m && j < n)
	{
		if(j == -1 || lpszFind[j] == '?' || lpszSour[i] == lpszFind[j])
		{	i++;
			j++;
		}
		else
			j = next[j];
	}

	delete []next;

	if(j >= n)
		return i-n;
	else
		return -1;
}
//############################################################################### 
 template <typename T> bool MFindFile<T>::MatchingString(const char* lpszSour, const char* lpszMatch, bool bMatchCase)
{
//	ASSERT(AfxIsValidString(lpszSour) && AfxIsValidString(lpszMatch));
	if(lpszSour == NULL || lpszMatch == NULL)
		return false;

	if(lpszMatch[0] == 0)//Is a empty string
	{
		if(lpszSour[0] == 0)
			return true;
		else
			return false;
	}

	int i = 0, j = 0;

	//生成比较用临时源字符串'szSource'
	char* szSource =
		new char[ (j = strlen(lpszSour)+1) ];

	if( bMatchCase )
	{	memcpy(szSource, lpszSour, j);
		//qzj here 20100707  operation on i may be undefined? 
		//while( (*(szSource+i) = *(lpszSour+(i++)) ) );
	}
	else
	{	//Lowercase 'lpszSour' to 'szSource'
		i = 0;
		while(lpszSour[i])
		{	if(lpszSour[i] >= 'A' && lpszSour[i] <= 'Z')
				szSource[i] = lpszSour[i] - 'A' + 'a';
			else
				szSource[i] = lpszSour[i];

			i++;
		}
		szSource[i] = 0;
	}

	//生成比较用临时匹配字符串'szMatcher'
	char* szMatcher = new char[strlen(lpszMatch)+1];

	//把lpszMatch里面连续的“*”并成一个“*”后复制到szMatcher中
	i = j = 0;
	while(lpszMatch[i])
	{
		szMatcher[j++] = (!bMatchCase) ?
								( (lpszMatch[i] >= 'A' && lpszMatch[i] <= 'Z') ?//Lowercase lpszMatch[i] to szMatcher[j]
										lpszMatch[i] - 'A' + 'a' :
										lpszMatch[i]
								) :
								lpszMatch[i];		 //Copy lpszMatch[i] to szMatcher[j]
		//Merge '*'
		if(lpszMatch[i] == '*')
			while(lpszMatch[++i] == '*');
		else
			i++;
	}
	szMatcher[j] = 0;

	//开始进行匹配检查

	int nMatchOffset, nSourOffset;

	bool bIsMatched = true;
	nMatchOffset = nSourOffset = 0;
	while(szMatcher[nMatchOffset])
	{
		if(szMatcher[nMatchOffset] == '*')
		{
			if(szMatcher[nMatchOffset+1] == 0)
			{	//szMatcher[nMatchOffset]是最后一个字符

				bIsMatched = true;
				break;
			}
			else
			{	//szMatcher[nMatchOffset+1]只能是'?'或普通字符

				int nSubOffset = nMatchOffset+1;

				while(szMatcher[nSubOffset])
				{	if(szMatcher[nSubOffset] == '*')
						break;
					nSubOffset++;
				}

				if( strlen(szSource+nSourOffset) <
						size_t(nSubOffset-nMatchOffset-1) )
				{	//源字符串剩下的长度小于匹配串剩下要求长度
					bIsMatched = false; //判定不匹配
					break;			//退出
				}

				if(!szMatcher[nSubOffset])//nSubOffset is point to ender of 'szMatcher'
				{	//检查剩下部分字符是否一一匹配

					nSubOffset--;
					int nTempSourOffset = strlen(szSource)-1;
					//从后向前进行匹配
					while(szMatcher[nSubOffset] != '*')
					{
						if(szMatcher[nSubOffset] == '?')
							;
						else
						{	if(szMatcher[nSubOffset] != szSource[nTempSourOffset])
							{	bIsMatched = false;
								break;
							}
						}
						nSubOffset--;
						nTempSourOffset--;
					}
					break;
				}
				else//szMatcher[nSubOffset] == '*'
				{	nSubOffset -= nMatchOffset;

					char* szTempFinder = new char[nSubOffset];
					nSubOffset--;
					memcpy(szTempFinder, szMatcher+nMatchOffset+1, nSubOffset);
					szTempFinder[nSubOffset] = 0;

					int nPos = FindingString(szSource+nSourOffset, szTempFinder, 0);
					delete []szTempFinder;

					if(nPos != -1)//在'szSource+nSourOffset'中找到szTempFinder
					{	nMatchOffset += nSubOffset;
						nSourOffset += (nPos+nSubOffset-1);
					}
					else
					{	bIsMatched = false;
						break;
					}
				}
			}
		}		//end of "if(szMatcher[nMatchOffset] == '*')"
		else if(szMatcher[nMatchOffset] == '?')
		{
			if(!szSource[nSourOffset])
			{	bIsMatched = false;
				break;
			}
			if(!szMatcher[nMatchOffset+1] && szSource[nSourOffset+1])
			{	//如果szMatcher[nMatchOffset]是最后一个字符，
				//且szSource[nSourOffset]不是最后一个字符
				bIsMatched = false;
				break;
			}
			nMatchOffset++;
			nSourOffset++;
		}
		else//szMatcher[nMatchOffset]为常规字符
		{
			if(szSource[nSourOffset] != szMatcher[nMatchOffset])
			{	bIsMatched = false;
				break;
			}
			if(!szMatcher[nMatchOffset+1] && szSource[nSourOffset+1])
			{	bIsMatched = false;
				break;
			}
			nMatchOffset++;
			nSourOffset++;
		}
	}

	delete []szSource;
	delete []szMatcher;
	return bIsMatched;
}
//###############################################################################
 template <typename T> int  MFindFile<T>::FindFirstFile(char * FileName,tagFileFindFileInfo<T> * Out)
{
#ifdef WINDOWSCODE

	WIN32_FIND_DATA				out;
	SYSTEMTIME					systime;
	
	CloseFindFile();
	m_Handle = ::FindFirstFile(FileName,&out);
	if ( m_Handle == INVALID_HANDLE_VALUE )
	{
		return(-1);
	}

	strncpy(Out->filename,out.cFileName,32);
	Out->fileAttr = out.dwFileAttributes;
	Out->filesize = out.nFileSizeLow;

	::FileTimeToSystemTime(&(out.ftCreationTime),&systime);
	Out->CreateTime = MDateTime(systime.wYear,systime.wMonth,systime.wDay,systime.wHour,systime.wMinute,systime.wSecond);				//创建时间
	
	::FileTimeToSystemTime(&(out.ftLastWriteTime),&systime);
	Out->UpdateTime = MDateTime(systime.wYear,systime.wMonth,systime.wDay,systime.wHour,systime.wMinute,systime.wSecond);				//创建时间

	::FileTimeToSystemTime(&(out.ftLastAccessTime),&systime);
	Out->AccessTime = MDateTime(systime.wYear,systime.wMonth,systime.wDay,systime.wHour,systime.wMinute,systime.wSecond);				//创建时间
	
	return(1);
#else
	struct dirent		*	ep;
	register int			i;
	MFile<T>					file;
	char					tempbuf[256];
	
	strncpy(m_pathname,FileName,256);
	strncpy(m_match,"",32);
	
	for ( i=strlen(m_pathname);i>=0;i-- )
	{
		if ( m_pathname[i] == '\\' || m_pathname[i] == '/' )
		{
			strcpy(m_match,&(m_pathname[i+1]) );
			m_pathname[i] = 0;
			break;
		}
	}
	
	CloseFindFile();
	m_Handle = opendir(m_pathname);
	if ( m_Handle == NULL )
	{
		return(-1);	
	}
	
	while( ( ep = readdir( m_Handle )) != NULL )
	{
		if( MatchingString( ep->d_name, m_match, false ) )
		{
			strncpy(Out->filename,ep->d_name,32);
			Out->fileAttr = ep->d_type;				//文件属性
			Out->filesize = ep->d_reclen;			//文件大小
			
			snprintf(tempbuf,256,"%s/%s",m_pathname,Out->filename);
			if( file.Open( tempbuf ) < 0 )
			{
				Out->AccessTime = MDateTime<T>( 0l );
				Out->CreateTime = MDateTime<T>( 0l );
				Out->UpdateTime = MDateTime<T>( 0l );
			}
			else
			{
				Out->AccessTime = file.GetAccessDateTime();
				Out->CreateTime = file.GetCreateDateTime();
				Out->UpdateTime = file.GetUpdateDateTime();
				
				file.Close(); 
			}
			return (1);
		}
	}
	
	CloseFindFile();
	return (-2);
#endif
}
//###############################################################################/
 template <typename T> int  MFindFile<T>::FindNextFile(tagFileFindFileInfo<T> * Out)
{
#ifdef WINDOWSCODE
	
	WIN32_FIND_DATA				out;
	SYSTEMTIME					systime;
	
	if ( ::FindNextFile(m_Handle,&out) == 0 )
	{
		return(-1);
	}
	
	strncpy(Out->filename,out.cFileName,32);
	Out->fileAttr = out.dwFileAttributes;
	Out->filesize = out.nFileSizeLow;
	
	::FileTimeToSystemTime(&(out.ftCreationTime),&systime);
	Out->CreateTime = MDateTime(systime.wYear,systime.wMonth,systime.wDay,systime.wHour,systime.wMinute,systime.wSecond);				//创建时间
	
	::FileTimeToSystemTime(&(out.ftLastWriteTime),&systime);
	Out->UpdateTime = MDateTime(systime.wYear,systime.wMonth,systime.wDay,systime.wHour,systime.wMinute,systime.wSecond);				//创建时间
	
	::FileTimeToSystemTime(&(out.ftLastAccessTime),&systime);
	Out->AccessTime = MDateTime(systime.wYear,systime.wMonth,systime.wDay,systime.wHour,systime.wMinute,systime.wSecond);				//创建时间
	
	return(1);

#else
	struct dirent		*	ep;
	MFile<T>				file;
	char					tempbuf[256];
	
	while( ( ep = readdir( m_Handle )) != NULL )
	{
		if( MatchingString( ep->d_name, m_match,false ) )
		{ 
			strncpy(Out->filename,ep->d_name,32);
			Out->fileAttr = ep->d_type;				//文件属性
			Out->filesize = ep->d_reclen;			//文件大小
			
			snprintf(tempbuf,256,"%s/%s",m_pathname,Out->filename);
			if( file.Open( tempbuf ) < 0 )
			{
				Out->AccessTime = MDateTime<T>( 0l );
				Out->CreateTime = MDateTime<T>( 0l );
				Out->UpdateTime = MDateTime<T>( 0l );
			}
			else
			{
				Out->AccessTime = file.GetAccessDateTime();
				Out->CreateTime = file.GetCreateDateTime();
				Out->UpdateTime = file.GetUpdateDateTime();
				file.Close();
			}
			return (1);
		}
	}
	return (-2);
#endif
}

//###############################################################################	
 template <typename T>void MFindFile<T>::CloseFindFile(void)
{
#ifdef WINDOWSCODE

	if ( m_Handle != INVALID_HANDLE_VALUE )
	{
		::FindClose(m_Handle);
		m_Handle = INVALID_HANDLE_VALUE;
	}
	
#else
	if ( m_Handle != NULL )
	{
		closedir(m_Handle);
		m_Handle = NULL;
	}
#endif
}

//###############################################################################	
template <typename T> string RandWord()
{
	MFile<T> word;
	string ret;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	 
	srandom(tv.tv_sec+ tv.tv_usec);

	word.Open(MString<char>("/usr/share/dict/linux.words"));
	int size=word.GetFileLength();
	word.Seek(random()%size, SEEK_SET);

	ret=word.ReadWord().c_str();
	word.Close();
	return ret;
}


template <typename T> vector<string>  RandWord(int count)
{

	
	vector<string> vecStr;
	MFile<T> word;
	struct timeval tv;
#ifdef WINDOWSCODE
#else
	gettimeofday(&tv, NULL);
	 
	srandom(tv.tv_sec+ tv.tv_usec);
	word.Open(MString<char>("/usr/share/dict/linux.words"));
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

#endif
