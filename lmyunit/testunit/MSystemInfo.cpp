//#include "msysteminfo.h"
#include <unitlib.h> 
#include <iostream>
using namespace std;
main()
{ 
	tagSystemInfoCpuInfo cpuinfo;
	tagSystemInfoBIOSInfo biosinfo;
	tagSystemInfoMemoryInfo memoryinfo;
	tagHardWareInfo hardwareinfo;
	MSystemInfo info;
	MString  path;
	char infobb[40];
	if (info.GetCPUInfo(&cpuinfo, 1024) < 0 ) 
	{
		printf("error get cpuinfo\n");
	}
	if (info.GetBIOSInfo(&biosinfo) < 0) 
	{
		printf("error get biosinfo \n");
	}
	if (info.GetMemoryInfo(&memoryinfo) < 0) 
	{
		printf("error get memoryinfo \n");
	}
	if (info.GetCPUPercent() < 0) 
	{  
		printf("error get cpupercent info\n");
	}
	if (info.GetMemoryPercent() < 0) 
	{
		printf("errror get MemoryPercent info\n");
	}
	if (info.GetSystemHardWareInfo(&hardwareinfo) < 0)
	{
		printf("error get SystemHardWareInfo\n");
	}
	path+=info.GetApplicationFilePath();
    printf("path %s\n",path.c_str());
	printf("all the info\n");
	printf("[cpuinfo] %s %s %d %s\n\n",cpuinfo.Indentify,cpuinfo.ProcessName,cpuinfo.Frequency,cpuinfo.Vendor);
	printf("[biosinfo] Indentify %s  BiosDate %s BiosVersion %s VideoDate  %s VideoVersion \n\n",biosinfo.Indentify,biosinfo.BiosDate,biosinfo.VideoDate,biosinfo.VideoVersion);
	printf("[memoryinfo]  PhyMemorySize %d PhyAvailableSize %d VirMemoryUserSize %d\n\n",memoryinfo.PhyMemorySize,memoryinfo.PhyAvailableSize,memoryinfo.VirMemoryUserSize);
	printf("[hardwareinfo] OSType %d Description %s CPUCount %d CPUFreq %d CPUPercent %d PhyMemorySize %d PhyMemoryPercent %d \n\n",hardwareinfo.OSType,hardwareinfo.Description,hardwareinfo.CPUCount,hardwareinfo.CPUFreq,hardwareinfo.CPUPercent,hardwareinfo.PhyMemorySize,hardwareinfo.PhyMemoryPercent);
}

