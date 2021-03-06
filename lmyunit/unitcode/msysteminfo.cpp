//--------------------------------------------------------------------------------------------------------------------------------
#include "msysteminfo.h"
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MSystemInfo,MObject)

END_LMYUNIT
//................................................................................................................................
char			MSystemInfo::m_ApplicationPath[256] = "no initialize";
//................................................................................................................................
MSystemInfo::MSystemInfo(void)
{
#ifdef WINDOWSCODE
#else
#endif
}
//................................................................................................................................
MSystemInfo::~MSystemInfo()
{
#ifdef WINDOWSCODE
#else
#endif
}
//................................................................................................................................
int  MSystemInfo::GetCPUInfo(tagSystemInfoCpuInfo * Out,unsigned short InSize)
{
#ifdef WINDOWSCODE
	register int								i;
	char										tempbuf[256];
	MRegister									reg;
	register unsigned short						errorcode = 0;

	for ( i=0;i<=InSize - 1;i++ )
    {
        _snprintf(tempbuf,256,"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\%d",i);
        if ( reg.OpenKey(HKEY_LOCAL_MACHINE,tempbuf) > 0 )
        {
            errorcode ++;

            reg.ReadString("Identifier",Out[i].Indentify,50);
            reg.ReadString("ProcessorNameString",Out[i].ProcessName,50);
            reg.ReadInteger("~MHz",&Out[i].Frequency);
            reg.ReadString("VendorIdentifier",Out[i].Vendor,30);

            reg.CloseKey();
        }
    }

	return(errorcode);
#else
	char						tempbuf[8192];
	MFile						fileptr;
	char					*	searchptr;
	char					*	tempptr;
	register int				errorcode;
	register int				k;
	char						changebuf[50];

	//获取CPU信息
	if ( fileptr.Open("/proc/cpuinfo") < 0 )
	{
		return(0);
	}
	else
	{
		fileptr.Read(tempbuf,8192);

		searchptr = tempbuf;
		errorcode = 0;
		while((tempptr = strstr(searchptr,"model name")) != NULL )
		{
			//获取CPU名称
			while ( (* tempptr) != ':' && tempptr < (tempbuf + 8192) )
			{
				tempptr ++;
			}

			tempptr ++;
			k = 0;

			while ( (* tempptr) != 0x0A && (* tempptr) != 0x0D && k < 49 )
			{
				changebuf[k] = * tempptr;

				tempptr ++;
				k ++;
			}
			changebuf[k] = 0;
			
			strncpy(Out[errorcode].ProcessName,changebuf,50);
			
			searchptr = tempptr;
			if ( (tempptr = strstr(searchptr,"cpu MHz")) == NULL )
			{
				Out[errorcode].Frequency = 0;
			}
			else
			{
				while( (* tempptr) != ':' && tempptr < (tempbuf + 8192) )
				{
					tempptr ++;	
				}
				
				tempptr ++;
				k = 0;
				
				while((* tempptr) != 0x0A && (* tempptr) != 0x0D && k < 49 )
				{
					changebuf[k] = * tempptr;
					
					tempptr ++;
					k ++;
				}
				k = 0;
				
				Out[errorcode].Frequency = strtol(changebuf,NULL,10);
			}
			
			Out[errorcode].Indentify[0] = 0;
			Out[errorcode].Vendor[0] = 0;
			searchptr = tempptr;
			errorcode ++;
		}

		fileptr.Close();
		
		return(errorcode);
	}
#endif
}
//................................................................................................................................
int  MSystemInfo::GetBIOSInfo(tagSystemInfoBIOSInfo * Out)
{
#ifdef WINDOWSCODE
	MRegister									reg;
	int											errorcode;

	memset((char *)Out,0x00,sizeof(tagSystemInfoBIOSInfo));
	if ( (errorcode = reg.OpenKey(HKEY_LOCAL_MACHINE,"HARDWARE\\DESCRIPTION\\System")) > 0 )
    {
        reg.ReadString("Identifier",Out->Indentify,30);
		reg.ReadString("SystemBiosDate",Out->BiosDate,20);
        reg.ReadString("SystemBiosVersion",Out->BiosVersion,30);
		reg.ReadString("VideoBiosDate",Out->VideoDate,30);
		reg.ReadString("VideoBiosVersion",Out->VideoVersion,30);

        reg.CloseKey();

		return(1);
    }

	return(errorcode);
#else
	memset(Out,0x00,sizeof(tagSystemInfoBIOSInfo));
#endif
}
//................................................................................................................................
int  MSystemInfo::GetMemoryInfo(tagSystemInfoMemoryInfo * Out)
{
#ifdef WINDOWSCODE
	MEMORYSTATUS								memorystatus;

	memorystatus.dwLength = sizeof(memorystatus);
    ::GlobalMemoryStatus(&memorystatus);

	Out->PhyMemorySize = memorystatus.dwTotalPhys;
	Out->PhyAvailableSize = memorystatus.dwAvailPhys;
	Out->VirMemoryUserSize = memorystatus.dwTotalVirtual;

	return(1);
#else
	MFile				fileptr;
	char				tempbuf[8192];
	char			*	tempptr;
	char				changebuf[50];
	register int		k;
	
	Out->PhyAvailableSize = 0;
	Out->VirMemoryUserSize = 0;
	
	if ( fileptr.Open("/proc/meminfo") < 0 )
	{
		Out->PhyMemorySize = 0;	
	}
	else
	{
		fileptr.Read(tempbuf,8192);
		if ( (tempptr = strstr(tempbuf,"Mem")) == NULL )
		{
			Out->PhyMemorySize = 0;	
		}
		else
		{
			while ( (* tempptr) != ':' && tempptr < (tempbuf + 8192) )
			{
				tempptr ++;	
			}
			
			tempptr ++;
			
			while ( (* tempptr) == ' ' && tempptr < (tempbuf + 8192) )
			{
				tempptr ++;	
			}
			
			k = 0;
			while ( (* tempptr) != ' ' && k < 49 )
			{
				changebuf[k] = * tempptr;
				
				tempptr ++;
				k ++;
			}
			k = 0;
			
			Out->PhyMemorySize = strtol(changebuf,NULL,10);
		}
		fileptr.Close();	
	}
#endif
}
//................................................................................................................................
int  MSystemInfo::GetCPUPercent(void)
{
#ifdef WINDOWSCODE
	#pragma pack(1)
	struct																//Windows操作系统基本信息
	{
		unsigned long					dwUnknown1;							
		unsigned long					uKeMaximumIncrement;				
		unsigned long					uPageSize;
		unsigned long					uMmNumberOfPhysicalPages;
		unsigned long					uMmLowestPhysicalPage;
		unsigned long					uMmHighestPhysicalPage;
		unsigned long					uAllocationGranularity;
		void						*	pLowestUserAddress;
		void						*	pMmHighestUserAddress;
		unsigned long					uKeActiveProcessors;
		unsigned char					bKeNumberProcessors;
		unsigned char					bUnknown2;
		unsigned short					wUnknown3;
	} BaseInfo;   
	struct															//系统空闲时间信息
	{
		LARGE_INTEGER					liIdleTime;
		unsigned long					dwSpare[76];
	} IdleInfo;    
	struct															//系统时间信息
	{
		LARGE_INTEGER					liKeBootTime;
		LARGE_INTEGER					liKeSystemTime;
		LARGE_INTEGER					liExpTimeZoneBias;
		unsigned long					uCurrentTimeZoneId;
		unsigned long					dwReserved;
	} SysTimeInfo;       
	#pragma pack()

    __int64                             IdleTime;
    __int64                             SysTime;
	static __int64						OldIdleTime = 0;
	static __int64						OldSysTime = 0;
	double								tempdouble;
    long ( __stdcall *NtQuerySystemInformation )( DWORD, PVOID, DWORD, DWORD );

	//获取NT函数
    NtQuerySystemInformation = (long(__stdcall*)(DWORD,PVOID,DWORD,DWORD))::GetProcAddress( ::GetModuleHandle( "ntdll.dll" ),"NtQuerySystemInformation" );
    if ( NtQuerySystemInformation == NULL )
    {
        return(0);
    }

	//获取相应信息
    NtQuerySystemInformation(0,(void *)&BaseInfo,sizeof(BaseInfo),NULL);
    NtQuerySystemInformation(2,(void *)&IdleInfo,sizeof(IdleInfo),NULL);
    NtQuerySystemInformation(3,(void *)&SysTimeInfo,sizeof(SysTimeInfo),NULL);

	//计算CPU使用率
    IdleTime = IdleInfo.liIdleTime.QuadPart - OldIdleTime;
    SysTime = SysTimeInfo.liKeSystemTime.QuadPart - OldSysTime;
	if ( SysTime != 0 )
	{
		tempdouble = (double)IdleTime / (double)SysTime;
	}
	else
	{
		tempdouble = 0;
	}

    if ( BaseInfo.bKeNumberProcessors != 0 )
	{
        IdleTime = (__int64)(100.0 - tempdouble * 100.0 / (double)BaseInfo.bKeNumberProcessors + 0.5);
	}
	else
	{
		IdleTime = 0;
	}

    if ( OldIdleTime == 0 || OldSysTime == 0 )
    {
        OldIdleTime = IdleInfo.liIdleTime.QuadPart;
        OldSysTime = SysTimeInfo.liKeSystemTime.QuadPart;
        return(0);
    }
    else
    {
        OldIdleTime = IdleInfo.liIdleTime.QuadPart;
        OldSysTime = SysTimeInfo.liKeSystemTime.QuadPart;
        return((int)IdleTime);
    }
#else
    MFile					fileptr;
	char					tempbuf[8192];
	char				*	tempptr;
	char				*	nextptr;
	unsigned long			user = 0;
	unsigned long			amount = 0;
	register int			errorcode;
	
	if ( fileptr.Open("/proc/stat") < 0 )
	{
		return(0);	
	}
	else
	{
		fileptr.Read(tempbuf,8192);
		fileptr.Close();	
		
		if ( (tempptr = strstr(tempbuf,"cpu")) == NULL )
		{
			return(0);	
		}
		else
		{
			tempptr += 3;
			
			errorcode = strtol(tempptr,&nextptr,10);
			amount += errorcode;
			user += errorcode;
			tempptr = nextptr;
			
			errorcode = strtol(tempptr,&nextptr,10);
			amount += errorcode;
			user += errorcode;
			tempptr = nextptr;
			
			errorcode = strtol(tempptr,&nextptr,10);
			amount += errorcode;
			user += errorcode;
			tempptr = nextptr;
			
			errorcode = strtol(tempptr,&nextptr,10);
			amount += errorcode;
			tempptr = nextptr;
			
			if ( amount != 0 )
			{
				return(user * 100 / amount);
			}
			else
			{
				return(0);	
			}
		}
	}
#endif
}
//................................................................................................................................
int  MSystemInfo::GetMemoryPercent(void)
{
#ifdef WINDOWSCODE
	MEMORYSTATUS						memorystatus;

    memorystatus.dwLength = sizeof(memorystatus);
    ::GlobalMemoryStatus(&memorystatus);
	
	return(memorystatus.dwMemoryLoad);
#else
	//Linux操作系统
	MFile				fileptr;
	char				tempbuf[8192];
	char			*	tempptr;
	char			*	nextptr;
	double				user,total;
	
	if ( fileptr.Open("/proc/meminfo") < 0 )
	{
		return(0);	
	}
	else
	{
		fileptr.Read(tempbuf,8192);
		fileptr.Close();
		
		if ( (tempptr = strstr(tempbuf,"Mem:")) == NULL )
		{
			return(0);
		}
		else
		{
			tempptr += 4;
			total = strtod(tempptr,&nextptr) + 1;
			tempptr = nextptr;
			user = strtod(tempptr,&nextptr);
			
			return((int)(user * 100 / total));
		}
	}
#endif
}
//................................................................................................................................
MString MSystemInfo::GetApplicationFilePath(void)
{
#ifdef WINDOWSCODE
	char							tempbuf[256];
	register long					errorcode;
	register int					i;

	if ( (errorcode = ::GetModuleFileName(NULL,tempbuf,256)) == 0 )
	{
		return("");
	}

	for ( i=errorcode-1;i>=0;i-- )
	{
		if ( tempbuf[i] == '\\' )
		{
			tempbuf[i+1] = 0;
			return(tempbuf);
		}
	}

	return("");
#else
	char							temppath[256];
	MFile							fileptr;
	MString							tempstring;
	register int					i;
	
	if ( strcmp(m_ApplicationPath,"no initialize") == 0 )
	{
		_snprintf(temppath,256,"/proc/%d/cmdline",(int)getpid());
		if ( fileptr.Open(temppath) < 0 )
		{
			return("");	
		}
		
		strncpy(m_ApplicationPath,fileptr.ReadString().c_str(),256);
		
		fileptr.Close();
		
		for ( i=strlen(m_ApplicationPath)-1;i>=0;i-- )
		{
			if ( m_ApplicationPath[i] == '/' )
			{
				m_ApplicationPath[i+1] = 0;
				break;
			}
		}
	}
	
	return(m_ApplicationPath);
#endif
}
//................................................................................................................................
int  MSystemInfo::GetSystemHardWareInfo(tagHardWareInfo * Out)
{
#ifdef WINDOWSCODE

	unsigned long					osversion;
	tagSystemInfoBIOSInfo			biosinfo;
	tagSystemInfoCpuInfo			cpuinfo[20];
	register int					i;
	unsigned long					errorcode = 0;
	tagSystemInfoMemoryInfo			memoryinfo;

	osversion = ::GetVersion();

	if (osversion < 0x80000000)							// Windows NT/2000
	{
		Out->OSType = 0x02;
	}
	else if ( (DWORD)(LOBYTE(LOWORD(osversion))) < 4 )	// Win32s
	{
		Out->OSType = 0x01;
	}
	else												// Windows 95/98
	{
		Out->OSType = 0x00;
	}

	if ( GetBIOSInfo(&biosinfo) < 0 )
	{
		_snprintf(Out->Description,100,"无法获取系统描述信息");
	}
	else
	{
		_snprintf(Out->Description,100,"系统标示：%s，BIOS更新日期：%s，BIOS版本：%s，显示BIOS日期：%s，显示BIOS版本：%s",biosinfo.Indentify,biosinfo.BiosDate,biosinfo.BiosVersion,biosinfo.VideoDate,biosinfo.VideoVersion);
	}

	Out->CPUCount = GetCPUInfo(cpuinfo,20);
	for ( i=0;i<=(int)Out->CPUCount-1;i++ )
	{
		errorcode += cpuinfo[i].Frequency;
	}
	if ( Out->CPUCount != 0 )
	{
		Out->CPUFreq = errorcode / Out->CPUCount;
	}
	else
	{
		Out->CPUFreq = 0;
	}
	Out->CPUPercent = GetCPUPercent();

	if ( GetMemoryInfo(&memoryinfo) < 0 )
	{
		Out->PhyMemorySize = 0;
		Out->PhyMemoryPercent = 0;
	}
	else
	{
		Out->PhyMemorySize = memoryinfo.PhyMemorySize;
		Out->PhyMemoryPercent = GetMemoryPercent();
	}

	return(1);
#else
	unsigned long					osversion;
	tagSystemInfoBIOSInfo			biosinfo;
	tagSystemInfoCpuInfo			cpuinfo[20];
	register int					i;
	unsigned long					errorcode = 0;
	tagSystemInfoMemoryInfo			memoryinfo;

	Out->OSType = 0x03;

	if ( GetBIOSInfo(&biosinfo) < 0 )
	{
		_snprintf(Out->Description,100,"无法获取系统描述信息");
	}
	else
	{
		_snprintf(Out->Description,100,"系统标示：%s，BIOS更新日期：%s，BIOS版本：%s，显示BIOS日期：%s，显示BIOS版本：%s",biosinfo.Indentify,biosinfo.BiosDate,biosinfo.BiosVersion,biosinfo.VideoDate,biosinfo.VideoVersion);
	}

	Out->CPUCount = GetCPUInfo(cpuinfo,20);
	for ( i=0;i<=(int)Out->CPUCount-1;i++ )
	{
		errorcode += cpuinfo[i].Frequency;
	}
	if ( Out->CPUCount != 0 )
	{
		Out->CPUFreq = errorcode / Out->CPUCount;
	}
	else
	{
		Out->CPUFreq = 0;
	}
	Out->CPUPercent = GetCPUPercent();

	if ( GetMemoryInfo(&memoryinfo) < 0 )
	{
		Out->PhyMemorySize = 0;
		Out->PhyMemoryPercent = 0;
	}
	else
	{
		Out->PhyMemorySize = memoryinfo.PhyMemorySize;
		Out->PhyMemoryPercent = GetMemoryPercent();
	}

	return(1);
#endif
}
//--------------------------------------------------------------------------------------------------------------------------------
