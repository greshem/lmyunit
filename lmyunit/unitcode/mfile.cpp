//--------------------------------------------------------------------------------------------------------------------------------
#include <sys/stat.h> 
#include "mfile.h"
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MFile,MObject)

END_LMYUNIT
//................................................................................................................................
MFile::MFile(void)
{
#ifdef WINDOWSCODE
	m_FileHandle = INVALID_HANDLE_VALUE;
#else
	m_FileHandle = -1;
#endif
}
//................................................................................................................................
MFile::~MFile()
{
	Close();
}
//................................................................................................................................
int  MFile::Open(MString FileName,unsigned long Mode)
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
		return(ERROR_SYSTEM(GetLastError()));
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
	//printf("|| %s ",FileName.c_str());
	m_FileHandle = open(FileName.c_str(),openmode,sharemode);
	//printf(" %d ||",m_FileHandle);
	if ( m_FileHandle < 0 )
	{
		return(ERROR_SYSTEM(GetLastError()));
	}

	return(1);
#endif
}
//................................................................................................................................
int  MFile::Create(MString FileName)
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
		return(ERROR_SYSTEM(GetLastError()));
	}

	return(1);
#else
	strncpy(m_FileName,FileName.c_str(),256);
	
	Close();

	m_FileHandle = open(FileName.c_str(),O_CREAT | O_RDWR,S_IRWXU | S_IRWXG | S_IRWXO);
	if ( m_FileHandle < 0 )
	{
		return(ERROR_SYSTEM(GetLastError()));
	}

	return(1);
#endif
}
//................................................................................................................................
void MFile::Close(void)
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
//................................................................................................................................
int  MFile::Seek(long Offset,unsigned long FromType)
{
#ifdef WINDOWSCODE
	register int						errorcode;

	errorcode = ::SetFilePointer(m_FileHandle,Offset,0,FromType);
	if ( errorcode == 0xFFFFFFFF )
	{
		return(ERROR_SYSTEM(GetLastError()));
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
		return(ERROR_SYSTEM(GetLastError()));
	}
	else
	{
		return(errorcode);	
	}
#endif
}
//................................................................................................................................
int  MFile::SetFileLength(unsigned long FileLength)
{
#ifdef WINDOWSCODE
	register int						errorcode;

	errorcode = ::SetFilePointer(m_FileHandle,FileLength,0,0);
	if ( errorcode == 0xFFFFFFFF )
	{
		return(ERROR_SYSTEM(GetLastError()));
	}

	if ( ::SetEndOfFile(m_FileHandle) != 0 )
	{
		return(1);
	}
	else
	{
		return(ERROR_SYSTEM(GetLastError()));
	}
#else
	register int						errorcode;
	register int						oldptr;
	
	oldptr = lseek(m_FileHandle,0,1);
	if ( oldptr < 0 )
	{
		return(ERROR_SYSTEM(GetLastError()));
	}
	
	errorcode = ftruncate(m_FileHandle,FileLength);
	if ( errorcode < 0 )
	{
		return(ERROR_SYSTEM(GetLastError()));
	}
	
	if ( lseek(m_FileHandle,oldptr,0) < 0 )
	{
		return(ERROR_SYSTEM(GetLastError()));	
	}
	
	return(1);
#endif
}
//................................................................................................................................
int  MFile::SetFileLength(void)
{
#ifdef WINDOWSCODE
	if ( ::SetEndOfFile(m_FileHandle) != 0 )
	{
		return(1);
	}
	else
	{
		return(ERROR_SYSTEM(GetLastError()));
	}
#else
	register int				oldptr;
	
	oldptr = lseek(m_FileHandle,0,1);
	if ( oldptr < 0 )
	{
		return(ERROR_SYSTEM(GetLastError()));
	}
	
	if ( ftruncate(m_FileHandle,oldptr) < 0 )
	{
		return(ERROR_SYSTEM(GetLastError()));
	}
	
	return(1);
#endif
}
//................................................................................................................................
unsigned long MFile::GetFileLength(void)
{
	register int					errorcode;

	if ( (errorcode = Seek(0,2)) < 0 )
	{
		return(0);
	}
	else
	{
		return(errorcode);
	}
}
//................................................................................................................................
int  MFile::Read(char * OutBuf,unsigned long InSize)
{
#ifdef WINDOWSCODE
	register unsigned long					errorcode = 0;

	if ( ::ReadFile(m_FileHandle,OutBuf,InSize,&errorcode,NULL) == 0 )
	{
		return(ERROR_SYSTEM(GetLastError()));
	}
	else
	{
		return(errorcode);
	}
#else
	register int							errorcode;
	
	if ( (errorcode = read(m_FileHandle,OutBuf,InSize)) < 0 )
	{
		return(ERROR_SYSTEM(GetLastError()));	
	}
	else
	{
		return(errorcode);	
	}
#endif
}
//................................................................................................................................
int  MFile::Write(char * InBuf,unsigned long InSize)
{
#ifdef WINDOWSCODE
	register unsigned long					errorcode = 0;

	if ( ::WriteFile(m_FileHandle,InBuf,InSize,&errorcode,NULL) == 0 )
	{
		return(ERROR_SYSTEM(GetLastError()));
	}
	else
	{
		return(errorcode);
	}
#else
	register int							errorcode;
	
	if ( (errorcode = write(m_FileHandle,InBuf,InSize)) < 0 )
	{
		return(ERROR_SYSTEM(GetLastError()));
	}
	else
	{
		return(errorcode);
	}
#endif
}
//................................................................................................................................
MString MFile::ReadString(void)
{
	char						tempbuf[4096];
	register int				errorcode;
	register int				position;
	register int				i;

	position = Seek(0,1);
	errorcode = Read(tempbuf,4096);
	Seek(position,0);

	if ( errorcode < 0 )
	{
		return(errorcode);
	}


	for ( i=0;i<=errorcode-2;i++ )
	{
		if ( tempbuf[i] == 0x0D && tempbuf[i+1] == 0x0A )
		{
			tempbuf[i] = 0;
			return(tempbuf);
		}
	}

	tempbuf[errorcode] = 0;
	return(tempbuf);
}
//................................................................................................................................
int  MFile::ReadString(MString * Out)
{
	char						tempbuf[4096];
	register int				errorcode;
	register int				position;
	register int				i;
	
	position = Seek(0,1);
	errorcode = Read(tempbuf,4095);
	Seek(position,0);

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

			Seek(position + i + 2,0);

			return(1);
		}
	}
	
	tempbuf[errorcode] = 0;
	* Out = tempbuf;

	Seek(position + errorcode,0);

	return(1);
}
//................................................................................................................................
int  MFile::WriteString(MString In)
{
	In += "\r\n";

	return(Write(In.c_str(),In.Length()));
}
//................................................................................................................................
int  MFile::LockFile(long Offset,unsigned long Size)
{
#ifdef WINDOWSCODE
	if ( ::LockFile(m_FileHandle,Offset,0,Size,0) == 0 )
	{
		return(ERROR_SYSTEM(GetLastError()));
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
		return(ERROR_SYSTEM(GetLastError()));
	}
	else
	{
		return(1);	
	}
#endif
}
//................................................................................................................................
int  MFile::UnLockFile(long Offset,unsigned long Size)
{
#ifdef WINDOWSCODE
	if ( ::UnlockFile(m_FileHandle,Offset,0,Size,0) == 0 )
	{
		return(ERROR_SYSTEM(GetLastError()));
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
		return(ERROR_SYSTEM(GetLastError()));
	}
	else
	{
		return(1);	
	}
#endif
}
//................................................................................................................................
MDateTime MFile::GetCreateDateTime(void)
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

	return(		MDateTime(	systemtime.wYear,
							systemtime.wMonth,
							systemtime.wDay,
							systemtime.wHour,
							systemtime.wMinute,
							systemtime.wSecond	)	);
#else
	struct stat					errorcode;
	
	if ( fstat(m_FileHandle,&errorcode) < 0 )
	{
		return(MDateTime(0));
	}
	
	return(MDateTime(errorcode.st_ctime));
#endif
}
//................................................................................................................................
MDateTime MFile::GetUpdateDateTime(void)
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

	return(		MDateTime(	systemtime.wYear,
							systemtime.wMonth,
							systemtime.wDay,
							systemtime.wHour,
							systemtime.wMinute,
							systemtime.wSecond	)	);
#else
	struct stat					errorcode;
	
	if ( fstat(m_FileHandle,&errorcode) < 0 )
	{
		return(MDateTime(0));
	}
	
	return(MDateTime(errorcode.st_mtime));
#endif
}
//................................................................................................................................
MDateTime MFile::GetAccessDateTime(void)
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
	return(		MDateTime(	systemtime.wYear,
							systemtime.wMonth,
							systemtime.wDay,
							systemtime.wHour,
							systemtime.wMinute,
							systemtime.wSecond	)	);
#else
	struct stat					errorcode;
	
	if ( fstat(m_FileHandle,&errorcode) < 0 )
	{
		return(MDateTime(0));
	}
	
	return(MDateTime(errorcode.st_atime));
#endif
}
//................................................................................................................................
int  MFile::SetCreateDateTime(MDateTime In)
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
		return(ERROR_SYSTEM(GetLastError()));
	}
	else
	{
		return(1);
	}
#else
	return(-1);
#endif
}
//................................................................................................................................
int  MFile::SetUpdateDateTime(MDateTime In)
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
		return(ERROR_SYSTEM(GetLastError()));
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
		return(ERROR_SYSTEM(GetLastError()));
	}
	else
	{
		return(1);	
	}
#endif
}
//................................................................................................................................
int  MFile::SetAccessDateTime(MDateTime In)
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
		return(ERROR_SYSTEM(GetLastError()));
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
		return(ERROR_SYSTEM(GetLastError()));
	}
	else
	{
		return(1);	
	}
#endif
}
//................................................................................................................................
void MFile::Flush(void)
{
#ifdef WINDOWSCODE
	::FlushFileBuffers(m_FileHandle);
#else
	fsync(m_FileHandle);
#endif
}
//................................................................................................................................
unsigned long MFile::GetFileAttributes(MString FileName)
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
//................................................................................................................................
int  MFile::SetFileAttributes(MString FileName,unsigned long Attributes)
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
		return(ERROR_SYSTEM(GetLastError()));
	}
	else
	{
		return(1);
	}
#else
	return(-1);
#endif
}
//................................................................................................................................
int  MFile::RenameFileName(MString SourceFile,MString NewFile)
{
#ifdef WINDOWSCODE
	if ( ::MoveFile(SourceFile.c_str(),NewFile.c_str()) == 0 )
	{
		return(ERROR_SYSTEM(GetLastError()));
	}

	return(1);
#else
	if ( rename(SourceFile.c_str(),NewFile.c_str()) < 0 )
	{
		return(ERROR_SYSTEM(GetLastError()));
	}
	
	return(1);
#endif
}
//................................................................................................................................
int  MFile::DeleteFile(MString FileName)
{
#ifdef WINDOWSCODE
	if ( ::DeleteFile(FileName.c_str()) == 0 )
	{
		return(ERROR_SYSTEM(GetLastError()));
	}

	return(1);
#else
	if ( remove(FileName.c_str()) < 0 )
	{
		return(ERROR_SYSTEM(GetLastError()));
	}

	return(1);
#endif
}
//................................................................................................................................
int  MFile::CreateDirectory(MString FileName)
{
#ifdef WINDOWSCODE
	if ( ::CreateDirectory(FileName.c_str(),NULL) == 0 )
	{
		return(ERROR_SYSTEM(GetLastError()));
	}

	return(1);
#else
	if ( mkdir(FileName.c_str(),0x1FF) < 0 )
	{
		return(ERROR_SYSTEM(GetLastError()));
	}
	
	return(1);
#endif
}
//................................................................................................................................
int  MFile::DeleteDirectory(MString FileName)
{
#ifdef WINDOWSCODE
	if ( ::RemoveDirectory(FileName.c_str()) == 0 )
	{
		return(ERROR_SYSTEM(GetLastError()));
	}

	return(1);
#else
	if ( rmdir(FileName.c_str()) < 0 )
	{
		return(ERROR_SYSTEM(GetLastError()));
	}
	
	return(1);
#endif
}
//................................................................................................................................
int  MFile::CreateDirectoryTree(MString DirTreeName)
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
			
			MFile::CreateDirectory(tempbuf);
		}
	}
	
	MFile::CreateDirectory(dirtree);
	
	return(1);
}
//................................................................................................................................
MString MFile::GetCurrentDirectory(void)
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
//................................................................................................................................
int  MFile::SetCurrentDirectory(MString In)
{
#ifdef WINDOWSCODE
	if ( ::SetCurrentDirectory(In.c_str()) == 0 )
	{
		return(ERROR_SYSTEM(GetLastError()));
	}

	return(1);
#else
	if ( chdir(In.c_str()) < 0 )
	{
		return(	ERROR_SYSTEM(GetLastError()));
	}
	
	return(1);
#endif
}
//................................................................................................................................
bool MFile::IsExist(MString FileName)
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
//................................................................................................................................
int  MFile::CopyFile(MString SourceFile,MString NewFile,bool FailIfExists)
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
		return(ERROR_SYSTEM(GetLastError()));
	}

	return(1);
#else
	MFile						sourceptr;
	MFile						newfileptr;
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
	
	sourcefilesize = sourceptr.Seek(0,2);
	
	framecount = (sourcefilesize % 4096 == 0)?(sourcefilesize / 4096):(sourcefilesize / 4096 + 1);
	if ( framecount < 0 )
	{
		sourceptr.Close();
		newfileptr.Close();
		
		return(-1);
	}
	
	MFile::DeleteFile( NewFile );
	if ( (errorcode = newfileptr.Create(NewFile)) < 0 )
	{
		sourceptr.Close();
		return(errorcode);
	}
	
	sourceptr.Seek(0,0);
	newfileptr.Seek(0,0);
	
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
//--------------------------------------------------------------------------------------------------------------------------------
MFindFile::MFindFile(void)
{
	#ifdef WINDOWSCODE
		m_Handle = INVALID_HANDLE_VALUE;
	#else
		m_Handle = NULL;
	#endif
}
//................................................................................................................................
MFindFile::~MFindFile()
{
	CloseFindFile();
}
//................................................................................................................................
int MFindFile::FindingString(const char* lpszSour, const char* lpszFind, int nStart /* = 0 */)
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
//................................................................................................................................
bool MFindFile::MatchingString(const char* lpszSour, const char* lpszMatch, bool bMatchCase)
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
	{	//memcpy(szSource, lpszSour, j);
		while( *(szSource+i) = *(lpszSour+i++) );
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
//................................................................................................................................
int  MFindFile::FindFirstFile(char * FileName,tagFileFindFileInfo * Out)
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
	MFile					file;
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
				Out->AccessTime = MDateTime( 0l );
				Out->CreateTime = MDateTime( 0l );
				Out->UpdateTime = MDateTime( 0l );
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
//................................................................................................................................
int  MFindFile::FindNextFile(tagFileFindFileInfo * Out)
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
	MFile					file;
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
				Out->AccessTime = MDateTime( 0l );
				Out->CreateTime = MDateTime( 0l );
				Out->UpdateTime = MDateTime( 0l );
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
//................................................................................................................................
void MFindFile::CloseFindFile(void)
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
//--------------------------------------------------------------------------------------------------------------------------------
//

 long long MFile::GetCurOffset()
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



/****************************************************************************
* Description	 主要为了处理 /usr/share/dict/linux.words 获取的 word 的完整性
* @param 	
* @return 	 返回 , 一般的 常见的英文单词. 
* *************************************************************************/
//###############################################################################	
MString  MFile::ReadWord()
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

