/***************************************************
* Description -  对fat32 文件系统的单元测试。 
* Author -      qianzhongjie@gmail.com
* Date -        2010_08_10_10:06:52
* *************************************************/
//#2010_08_10_10:06:39 add by qzj
#include <assert.h>
//#include <dirent.h>
#include <malloc.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <gtest/gtest.h>

#define myerror(msg) fprintf(stderr, "%s: %s\n", __func__, msg);

#define SwapInt16(i) i
#define SwapInt32(i) i

#define DIR_ENTRY_SIZE 32
struct sFAT12_16 {
	u_char BS_DrvNum;		// Physical drive number
	u_char BS_Reserved;		// Current head
	u_char BS_BootSig;		// Signature
	u_int32_t BS_VolID;		// Volume ID
	char BS_VolLab[11];		// Volume Label
	char BS_FilSysType[8];		// FAT file system type (e.g. FAT, FAT12, FAT16, FAT32)
	u_char unused[448];		// unused space in bootsector
} __attribute__((packed));
//
struct sFAT32 {
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
} __attribute__((packed));

union sFATxx {
	struct sFAT12_16 FAT12_16;
	struct sFAT32 FAT32;
} __attribute__((packed));

// First sector = boot sector
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
	union sFATxx FATxx;
	u_int16_t BS_EndOfBS;		// marks end of bootsector
} __attribute__((packed));
//###############################################################################
int32_t getCountOfClusters(struct sBootSector *bs) ;
int32_t getFATType(struct sBootSector *bs) ;
//###############################################################################
u_int32_t getClusterOffset(struct sBootSector *bs, u_int32_t cluster) {
/*
	returns the offset of a specific cluster in the
	data region of the file system
*/

	assert(bs != NULL);
	assert(cluster > 1);

	u_int32_t FATSz, RootDirSectors, FirstDataSector;

	if (bs->BS_FATSz16 != 0) {
		FATSz = SwapInt16(bs->BS_FATSz16);
	} else {
		FATSz = SwapInt32(bs->FATxx.FAT32.BS_FATSz32);
	}

	RootDirSectors = ((SwapInt16(bs->BS_RootEntCnt) * DIR_ENTRY_SIZE) + (SwapInt16(bs->BS_BytesPerSec) - 1)) / SwapInt16(bs->BS_BytesPerSec);
	FirstDataSector = (SwapInt16(bs->BS_RsvdSecCnt) + (bs->BS_NumFATs * FATSz) + RootDirSectors);

	return (((cluster - 2) * bs->BS_SecPerClus) + FirstDataSector) * SwapInt16(bs->BS_BytesPerSec);

}
//###############################################################################/
/*
	retrieves FAT entry for a cluster number
*/
int32_t getFATEntry(FILE *fd, struct sBootSector *bs, u_int32_t cluster, u_int32_t *data) {

	assert(fd != NULL);
	assert(bs != NULL);
	assert(data != NULL);

	u_int32_t FATOffset, FATSz, BSOffset;
	int32_t FATType;

	*data=0;

	if (bs->BS_FATSz16 != 0) {
		FATSz = SwapInt16(bs->BS_FATSz16);
	} else {
		FATSz = SwapInt32(bs->FATxx.FAT32.BS_FATSz32);
	}

	FATType = getFATType(bs);

	if (FATType == 16) {
		FATOffset = cluster * 2;
		BSOffset = SwapInt16(bs->BS_RsvdSecCnt) * SwapInt16(bs->BS_BytesPerSec) + FATOffset;
		if (fseek(fd, BSOffset, SEEK_SET) == -1) {
			myerror("Seek error!");
			return -1;
		}
		if (fread(data, 2, 1, fd)<1) {
			myerror("Failed to read from file!");
			return -1;
		}
		*data=SwapInt32(*data);
	} else if (FATType == 32) {
		FATOffset = cluster * 4;
		BSOffset = SwapInt16(bs->BS_RsvdSecCnt) * SwapInt16(bs->BS_BytesPerSec) + FATOffset;
		if (fseek(fd, BSOffset, SEEK_SET) == -1) {
			myerror("Seek error!");
			return -1;
		}
		if (fread(data, 4, 1, fd) < 1) {
			myerror("Failed to read from file!");
			return -1;
		}
		*data=SwapInt32(*data);
		*data = *data & 0x0fffffff;
	} else if (FATType == 12) {
		myerror("FAT12 is not supported!");
		return -1;
	} else {
		myerror("Failed to get FAT type!");
		return -1;
	}

	return 0;

}
//###############################################################################
int32_t getFATType(struct sBootSector *bs) {
/*
	retrieves FAT type
*/

	assert(bs != NULL);

	int32_t CountOfClusters;

	CountOfClusters=getCountOfClusters(bs);
	if (CountOfClusters == -1) {
		return -1;
	} else if (CountOfClusters < 4096) { // FAT12!
		return 12;
	} else if (CountOfClusters < 65525) { // FAT16!
		return 16;
	} else { // FAT32!
		return 32;
	}
}
//###############################################################################
int32_t getCountOfClusters(struct sBootSector *bs) {
/*
	calculates count of clusters
*/

	assert(bs != NULL);

	u_int32_t RootDirSectors, FATSz, TotSec, DataSec;
	int32_t retvalue;

	RootDirSectors = ((SwapInt16(bs->BS_RootEntCnt) * 32) + (SwapInt16(bs->BS_BytesPerSec) - 1));
	RootDirSectors = RootDirSectors / SwapInt16(bs->BS_BytesPerSec);

	if (bs->BS_FATSz16 != 0) {
		FATSz = SwapInt16(bs->BS_FATSz16);
	} else {
		FATSz = SwapInt32(bs->FATxx.FAT32.BS_FATSz32);
	}
	if (SwapInt16(bs->BS_TotSec16) != 0) {
		TotSec = SwapInt16(bs->BS_TotSec16);
	} else {
		TotSec = SwapInt32(bs->BS_TotSec32);
	}
	DataSec = TotSec - (SwapInt16(bs->BS_RsvdSecCnt) + (bs->BS_NumFATs * FATSz) + RootDirSectors);

	retvalue = DataSec / bs->BS_SecPerClus;
	if (retvalue <= 0) {
		return -1;
	}
	return retvalue;
}
//###############################################################################
int32_t check_bootsector(struct sBootSector *bs) {
/*
	lazy check if this is really a FAT bootsector
*/

	assert(bs != NULL);

	if (!((bs->BS_JmpBoot[0] == 0xeb) &&
	     (bs->BS_JmpBoot[2] == 0x90))
	  && !(bs->BS_JmpBoot[0] == 0xe9)) {
		// boot sector does not begin with specific instruction
 		myerror("Boot sector does not begin with jump instruction!");
		return -1;
	} else if (SwapInt16(bs->BS_EndOfBS) != 0xaa55) {
		// end of bootsector marker is missing
		myerror("End of boot sector marker is missing!");
		return -1;
	} else if (SwapInt16(bs->BS_BytesPerSec) == 0) {
		myerror("Sectors have a size of zero! Corrupt boot sector!");
		return -1;
	} else if (SwapInt16(bs->BS_SecPerClus) == 0) {
		myerror("Clusters have a size of zero! Corrupt boot sector!");
		return -1;
	}

	return 0;
}


//###############################################################################
/*
	reads bootsector
*/

int32_t read_bootsector(FILE *fd, struct sBootSector *bs) {

	assert(fd != NULL);
	assert(bs != NULL);

	if (fread(bs, sizeof(struct sBootSector), 1, fd) < 1) {
		if (feof(fd)) {
			myerror("Boot sector is too short!");
		} else {
			myerror("Failed to read from file!");
		}
		return -1;
	}


	if (check_bootsector(bs)) {
		myerror("This is not a FAT bootsector!");
		return -1;
	}

	

	return 0;
}


//###############################################################################
/*
	print file system information
*/
int32_t printFSInfo(char *filename) 
{
	assert(filename != NULL);

	u_int32_t FATSz, value;
	int32_t FATType, cluster;
	FILE *fd;
	struct sBootSector bs;

	printf("\t- File system information -\n");

	if ((fd=fopen(filename, "r+")) == NULL) {
		perror(__func__);
		return -1;
	}

	// read boot sector
	if (read_bootsector(fd, &bs)) {
		myerror("Failed to read boot sector!");
		return -1;
	}

	if (bs.BS_FATSz16 != 0) {
		FATSz = SwapInt16(bs.BS_FATSz16);
	} else {
		FATSz = SwapInt32(bs.FATxx.FAT32.BS_FATSz32);
	}

	FATType = getFATType(&bs);
	if (FATType == -1) {
		myerror("Failed to get FAT type!");
		return -1;
	}

	cluster=getCountOfClusters(&bs);
	if (cluster == -1) {
		myerror("Failed to get count of cluster!");
		return -1;
	}

	printf("Device:\t\t\t\t%s\n", filename);
	fflush(stdout);
	printf("Type:\t\t\t\tFAT%u\n", getFATType(&bs));
	fflush(stdout);
	printf("Sector size:\t\t\t%u bytes\n", SwapInt16(bs.BS_BytesPerSec));
	fflush(stdout);
	printf("FAT size:\t\t\t%u sectors (%u bytes)\n", FATSz, FATSz * SwapInt16(bs.BS_BytesPerSec));
	printf("Cluster size:\t\t\t%u *  %u %u bytes\n",  bs.BS_SecPerClus,bs.BS_BytesPerSec,  bs.BS_SecPerClus * SwapInt16(bs.BS_BytesPerSec));
	printf("Cluster count:\t\t\t%u\n", cluster);
	printf("FS size:\t\t\t%.2f Mbytes\n", cluster * bs.BS_SecPerClus * SwapInt16(bs.BS_BytesPerSec) / (float) (1024*1024));
	if (FATType == 32) {
		if (getFATEntry(fd, &bs, SwapInt32(bs.FATxx.FAT32.BS_RootClus), &value) == -1) {
			myerror("Failed to get FAT enry!");
			return -1;
		}
		printf("FAT32 root directory first cluster: 0x%x, Data offset: 0x%x, FAT entry: 0x%x\n",
			SwapInt32(bs.FATxx.FAT32.BS_RootClus),
			getClusterOffset(&bs, SwapInt32(bs.FATxx.FAT32.BS_RootClus)), value);
	}

	fclose(fd);

	return 0;
}
TEST(endian , size)
{
	EXPECT_EQ( sizeof(sBootSector), 512 );
}

TEST(fat, info)
{
	EXPECT_EQ(printFSInfo("/dev/sdb1") ,0);
	
}
int main(int argc, char * argv[])
{
	//print
	testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
	
	//printFSInfo("/dev/sdb1") ;
}
