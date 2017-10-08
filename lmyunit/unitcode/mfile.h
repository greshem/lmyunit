//--------------------------------------------------------------------------------------------------------------------------------
//                  ;;;,
//        ,;;;;;: ,;;;:.,;..
//         :;;"`,;;;;;;"":;;					��Ԫ���ƣ��ļ���д����
//      ..;;:  .;;,.;;:',;;"
//    ,;;;;;;" :;`',;",;;"						��д���ڣ�2004��5��20
//   :" ,;:` , `:.;;;;;'
//    ,;;;,;:;;,;;;, ,;							��д��Ա��richtech
//   :;;;"` `:;;;;;,;,.;.
//   '""   .;;`.;";:;;;;` ;,					��ע��Ϣ��
//       .;"`  ::. '   .,;;;
//      ""     ';;;;;;;;;;`
//--------------------------------------------------------------------------------------------------------------------------------
#ifndef __LmyUnitMFileH__
#define __LmyUnitMFileH__
//--------------------------------------------------------------------------------------------------------------------------------
//����ͷ�ļ�
#include "mobject.h"
#include "mdatetime.h"
//................................................................................................................................
#ifdef WINDOWSCODE
//................................................................................................................................
//Windows����ϵͳ
#include "io.h"
//................................................................................................................................
#else
//................................................................................................................................
//Linux����ϵͳ
//#include <sys/types.h>
//#include <sys/stat.h>
#include <utime.h>
#include <fcntl.h>
#include <dirent.h>
//................................................................................................................................
#endif
//--------------------------------------------------------------------------------------------------------------------------------
#pragma pack(1)
//................................................................................................................................
typedef struct
{
	char					filename[32];			//�ļ�����
	unsigned long			fileAttr;				//�ļ�����
	unsigned long			filesize;				//�ļ���С
	MDateTime				CreateTime;				//����ʱ��
	MDateTime				UpdateTime;				//����ʱ��
	MDateTime				AccessTime;				//����ʱ��
} tagFileFindFileInfo;
//................................................................................................................................
#pragma pack()
//--------------------------------------------------------------------------------------------------------------------------------
enum
{
	MFILE_OPENMODE_READ = 0x01,															//���ļ���ȡ
	MFILE_OPENMODE_WRITE = 0x02,														//���ļ�д
	MFILE_OPENMODE_READWRITE = MFILE_OPENMODE_READ | MFILE_OPENMODE_WRITE,				//���ļ���д
	MFILE_OPENMODE_NOTHING = 0x00,														//��������
	MFILE_OPENMODE_SHAREREAD = 0x04,													//�������
	MFILE_OPENMODE_SHAREWRITE = 0x08,													//������д
	MFILE_OPENMODE_SHAREALL = MFILE_OPENMODE_SHAREREAD | MFILE_OPENMODE_SHAREWRITE,		//�������д
};
//................................................................................................................................
enum
{
	MFILE_ATTR_NORMAL = 0x00,															//��ͨ�ļ�
	MFILE_ATTR_READONLY = 0x01,															//ֻ���ļ�
	MFILE_ATTR_HIDDEN = 0x02,															//�����ļ�
	MFILE_ATTR_SYSTEM = 0x04,															//ϵͳ�ļ�
	MFILE_ATTR_VOLUME = 0x08,															//���
	MFILE_ATTR_DIRECTORY = 0x10,														//Ŀ¼
	MFILE_ATTR_ARCHIVE = 0x20,															//�浵�ļ�
};
//--------------------------------------------------------------------------------------------------------------------------------
class MFile : public MObject
{
protected:

#ifdef WINDOWSCODE
	HANDLE						m_FileHandle;
#else
	long						m_FileHandle;
	char						m_FileName[256];
#endif

public:
	MFile(void);
	virtual ~MFile();
public:
	int  Open(MString FileName,unsigned long Mode = MFILE_OPENMODE_READ | MFILE_OPENMODE_SHAREALL);
	int  Create(MString FileName);
	void Close(void);
public:
	int  Seek(long Offset,unsigned long FromType);
	int  SetFileLength(unsigned long FileLength);
	int  SetFileLength(void);
	unsigned long GetFileLength(void);
	long long GetCurOffset();

public:
	int  Read(char * OutBuf,unsigned long InSize);
	int  Write(char * InBuf,unsigned long InSize);
public:
	MString ReadString(void);
	int  ReadString(MString * Out);
	int  WriteString(MString In);
	MString  ReadWord();

public:
	int  LockFile(long Offset,unsigned long Size);
	int  UnLockFile(long Offset,unsigned long Size);
public:
	MDateTime GetCreateDateTime(void);
	MDateTime GetUpdateDateTime(void);
	MDateTime GetAccessDateTime(void);
public:
	int  SetCreateDateTime(MDateTime In);
	int  SetUpdateDateTime(MDateTime In);
	int  SetAccessDateTime(MDateTime In);
public:
	void Flush(void);
public:
	static unsigned long GetFileAttributes(MString FileName);
	static int  SetFileAttributes(MString FileName,unsigned long Attributes);
public:
	static int  RenameFileName(MString SourceFile,MString NewFile);
	static int  DeleteFile(MString FileName);
	static int  CreateDirectory(MString FileName);
	static int  DeleteDirectory(MString FileName);
	static int  CreateDirectoryTree(MString DirTreeName);
	static MString GetCurrentDirectory(void);
	static int  SetCurrentDirectory(MString In);
	static bool IsExist(MString FileName);
	static int  CopyFile(MString SourceFile,MString NewFile,bool FailIfExists);

	DECLARE_LMYUNIT(MFile)
};
//--------------------------------------------------------------------------------------------------------------------------------
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
	int  FindFirstFile(char * FileName,tagFileFindFileInfo * Out);
	int  FindNextFile(tagFileFindFileInfo * Out);
	void CloseFindFile(void);
};
//--------------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------
