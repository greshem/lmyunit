/********************************************************************************************
* Description -  �Լ��������Ľṹ�� ����д������ 
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
//1. ��һ��ҳ�棬 ������Ϣ. 
//		�ӿ�: BaseDataEngine::GetBaseInfo( BaseInfo &out)
typedef struct _BaseInfo
{
	char server_name[32]; 	// ����������
	char status;		  	// ģ��������״̬.
	char inner_network[32]; // �ڲ������. 
	char inner_node[32];	// �ڲ�node ��.	
	char ex_network[32];	// �ⲿnode��.
	char mac_addr[16];		// ������ַ.
	char frame_type[16];	// ֡����. 
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
//2.  �ڶ���ҳ��, �����ļ���Ŀ¼
//		�ӿ�: void BaseDataEngine::GetShareDir(vector<string> &share_dir)
//		notice: һ������Ŀ¼һ�� char path[256];
		
//------------------------------------------------------------------------
//3. ������ҳ��, ����վ����
//		�ӿ�: void GetAllWorkStation(vector<Workstation> &out);
typedef struct _Workstation
{
	char mac_addr[16];		// ������ַ.
	char inner_network[32]; // �ڲ������. 
	char status;			//����״̬
	int	 connect_time;		//����ʱ��. 
	char cur_used_file[128];//��ǰ��ȡ�ļ�. 
} __attribute__((__packed__)) Workstation ;

//------------------------------------------------------------------------
//4. ���ĸ�ҳ��, ���̹���
//		�ӿ�. void BaseDataEngine::GetAllProcess(vector<nw_process> &out);
typedef struct _nw_process
{
	char mac_addr[16];		// ������ַ.
	char inner_network[32]; // �ڲ������. 
	char process_name [32]; // ��������. 
	char status;			// ����״̬. 
} __attribute__((__packed__)) nw_process   ;
;

#endif //__STRUCT_DEFINE_HEADER__

