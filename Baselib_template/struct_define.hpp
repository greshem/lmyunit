/********************************************************************************************
* Description -  自己碰到过的结构都 把他写到这里 
* Author -      qianzhongjie@gmail.com
* Date -        2011_03_30_15:50:56
* *******************************************************************************************/
#ifndef __STRUCT_DEFINE_HEADER__
#define __STRUCT_DEFINE_HEADER__

#include <fstream>
#include <string> 
#include <iostream>
#include <map>
#include <iostream> 
#include <algorithm>
#include <vector> 
#include <iterator>  
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
using namespace std;


typedef struct _IPXADDR {
    unsigned long  network;
    unsigned char  node[6];
    unsigned short sock;
} IPXADDR;


#define ADDR_SIZE               sizeof(IPXADDR)

//------------------------------------------------------------------------
//1. 第一个页面， 基本信息. 
//		接口: BaseDataEngine::GetBaseInfo( BaseInfo &out)
typedef struct _BaseInfo
{
	char server_name[32]; 	// 服务器名称
	char status;		  	// 模拟器工作状态.
	char inner_network[32]; // 内部网络号. 
	char inner_node[32];	// 内部node 号.	
	char ex_network[32];	// 外部node号.
	char mac_addr[16];		// 网卡地址.
	char frame_type[16];	// 帧类型. 
	friend ostream &  operator << (ostream &in , const struct _BaseInfo &baseinfo)
	{
		in <<"server_name -> "<<baseinfo.server_name <<endl;
		in <<"status -> "<<(int )baseinfo.status<<endl;
		in <<"inner_network-> " << baseinfo.inner_network<<endl;
		in <<"inner_node ->"<< baseinfo.inner_node<<endl;
		in <<"ex_network-> "<< baseinfo.ex_network<<endl;
		in <<"mac_addr-> "<< baseinfo.mac_addr<<endl;
		in <<"frame_type->"<<baseinfo.frame_type<<endl;
		return in ;
	}

}   __attribute__((__packed__)) BaseInfo ;

//------------------------------------------------------------------------
//2.  第二个页面, 共享文件夹目录
//		接口: void BaseDataEngine::GetShareDir(vector<string> &share_dir)
//		notice: 一个共享目录一个 char path[256];
		
//------------------------------------------------------------------------
//3. 第三个页面, 工作站管理
//		接口: void GetAllWorkStation(vector<Workstation> &out);
typedef struct _Workstation
{
	char mac_addr[16];		// 网卡地址.
	char inner_network[32]; // 内部网络号. 
	char status;			//工作状态
	int	 connect_time;		//连接时间. 
	char cur_used_file[128];//当前读取文件. 
} __attribute__((__packed__)) Workstation ;

//------------------------------------------------------------------------
//4. 第四个页面, 进程管理
//		接口. void BaseDataEngine::GetAllProcess(vector<nw_process> &out);
typedef struct _nw_process
{
	char mac_addr[16];		// 网卡地址.
	char inner_network[32]; // 内部网络号. 
	char process_name [32]; // 进程名称. 
	char status;			// 进程状态. 
} __attribute__((__packed__)) nw_process   ;
;

#endif //__STRUCT_DEFINE_HEADER__

