//###################################################
#include <gtest/gtest.h>
#include <fstream>
//#include <dirent.h>
#include <string> 
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unitlib.h>
#include <map>
#include <iostream> 
#include <algorithm>
#include <vector> 
#include <iterator>  


char *file_seek_and_read(FILE * file, int offset, int count, int * readLen);

struct sBootSector {
	u_char BS_JmpBoot[3];		// Jump instruction (to skip over header on boot)
	char BS_OEMName[8];		// OEM Name (padded with spaces)
	u_int16_t BS_BytesPerSec;	// Bytes per sector
	u_char BS_SecPerClus;		// Sectors per cluster
	u_int16_t BS_RsvdSecCnt;	// Reserved sector count (including boot sector)
	u_char BS_NumFATs;		// Number of file allocation tables
	u_int16_t BS_RootEntCnt;	// Number of root directory entries
	u_int16_t BS_TotSec16;		// Total sectors (bits 0-15)
	u_char BS_Media;		// Media descriptor
	u_int16_t BS_FATSz16;		// Sectors per file allocation table
	u_int16_t BS_SecPerTrk;	// Sectors per track
	u_int16_t BS_NumHeads;		// Number of heads
	u_int32_t BS_HiddSec;		// Hidden sectors
	u_int32_t BS_TotSec32;		// Total sectors (bits 16-47)
	u_int32_t BS_FATSz32;		// Sectors per FAT
	u_int16_t BS_ExtFlags;		// Flags
	u_int16_t BS_FSVer;		// Version
	u_int32_t BS_RootClus;		// Root Directory Cluster
	u_int16_t BS_FSInfo;		// Sector of FSInfo structure
	u_int16_t BS_BkBootSec;		// Sector number of the boot sector copy in reserved sectors
	char BS_Reserved[12];		// for future expansion
	char BS_DrvNum;			// see fat12/16
	char BS_Reserved1;		// see fat12/16
	char BS_BootSig;		// ...
	u_int32_t BS_VolID;
	char BS_VolLab[11];
	char BS_FilSysType[8];
	u_char unused[420];		// unused space in bootsector

	u_int16_t BS_EndOfBS;		// marks end of bootsector
} __attribute__((packed));

int sBootSector_dump(struct sBootSector in )	
{
	cout<< "u_char	BS_JmpBoot[3]		"<< (in.BS_JmpBoot)<<endl;
	cout<< "char	BS_OEMName[8]		"<< string(in.BS_OEMName)<<endl;
	cout<< "u_int16_t	BS_BytesPerSec		"<< in.BS_BytesPerSec<<endl;
	cout<< "u_char	BS_SecPerClus		"<< (unsigned int)in.BS_SecPerClus<<endl;
	cout<< "u_int16_t	BS_RsvdSecCnt		"<< in.BS_RsvdSecCnt<<endl;
	cout<< "u_char	BS_NumFATs		"<<  (unsigned int) in.BS_NumFATs<<endl;
	cout<< "u_int16_t	BS_RootEntCnt		"<< in.BS_RootEntCnt<<endl;
	cout<< "u_int16_t	BS_TotSec16		"<< in.BS_TotSec16<<endl;
	cout<< "u_char	BS_Media		"<<  (unsigned int) (in.BS_Media)<<endl;
	cout<< "u_int16_t	BS_FATSz16		"<< in.BS_FATSz16<<endl;
	cout<< "u_int16_t	BS_SecPerTrk		"<< in.BS_SecPerTrk<<endl;
	cout<< "u_int16_t	BS_NumHeads		"<< in.BS_NumHeads<<endl;
	cout<< "u_int32_t	BS_HiddSec		"<< in.BS_HiddSec<<endl;
	cout<< "u_int32_t	BS_TotSec32		"<< in.BS_TotSec32<<endl;
	cout<< "u_int32_t	BS_FATSz32		"<< in.BS_FATSz32<<endl;
	cout<< "u_int16_t	BS_ExtFlags		"<< in.BS_ExtFlags<<endl;
	cout<< "u_int16_t	BS_FSVer		"<< in.BS_FSVer<<endl;
	cout<< "u_int32_t	BS_RootClus		"<< in.BS_RootClus<<endl;
	cout<< "u_int16_t	BS_FSInfo		"<< in.BS_FSInfo<<endl;
	cout<< "u_int16_t	BS_BkBootSec		"<< in.BS_BkBootSec<<endl;
	cout<< "char	BS_Reserved[12]		"<< string(in.BS_Reserved)<<endl;
	cout<< "char	BS_DrvNum		"<< (unsigned int) (in.BS_DrvNum)<<endl;
	cout<< "char	BS_Reserved1		"<< (unsigned int) (in.BS_Reserved1)<<endl;
	cout<< "char	BS_BootSig		"<< (unsigned int) (in.BS_BootSig)<<endl;
	cout<< "u_int32_t	BS_VolID		"<< in.BS_VolID<<endl;
	cout<< "char	BS_VolLab[11]		"<< string(in.BS_VolLab)<<endl;
	cout<< "char	BS_FilSysType[8]		"<< string(in.BS_FilSysType)<<endl;
	cout<< "u_char	unused[420]		"<< (in.unused)<<endl;
	cout<< "u_int16_t	BS_EndOfBS		"<< in.BS_EndOfBS<<endl;
	return 1;
}

char *file_seek64_and_read(FILE * file, int offset, int count, int * readLen)
{
	char *buffer;
	int ret;
	buffer=(char *)malloc(count);
	memset(buffer, '\0', count);
	lseek64(fileno(file), 0, SEEK_END);
	long long  length=lseek64(fileno(file), 0, SEEK_CUR);

	//请求的offset 大于文件的长度。 
	if( offset > length)
	{
		warn(" offset is larger than fileSize %d", length);
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
		//*readLen=ret;	
		*readLen=ret;
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
		return buffer;
	}	
}


int main()
{

	struct sBootSector  in;
	assert(sizeof(in)==512);
	FILE *fp;
	fp=fopen("/dev/sdb1", "r");
	if(fp==NULL)
	{
		die("open /dev/sdb1 error");
	}
	int readLen;
	char* data=file_seek64_and_read(fp, 0, 512, &readLen);	
	memcpy((char*)&in, data , sizeof(in));
	sBootSector_dump( in )	;

		
}
