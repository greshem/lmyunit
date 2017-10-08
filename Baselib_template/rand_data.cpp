#include <Baselib.hpp>
#include <gtest/gtest.h>
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
/****************************************************************************
* Description	随机填充第一个页面的 基本信息. 
* @param 	
* @return 	
****************************************************************************/
template <> int RandData(BaseInfo &out)
{
	char tmp[256];
	rand_mem_with_ascii<char> (tmp, sizeof(tmp));
	strncpy(out.server_name, tmp, sizeof(out.server_name));

	out.status=rand();

	rand_mem_with_ascii<char> (tmp, sizeof(tmp));
	strncpy(out.inner_network, tmp, sizeof(out.inner_network));	

	rand_mem_with_ascii<char> (tmp, sizeof(tmp));
	strncpy(out.inner_node, tmp, sizeof(out.inner_node));

	rand_mem_with_ascii<char> (tmp, sizeof(tmp));
	strncpy(out.ex_network, tmp, sizeof(out.ex_network));

	rand_mem_with_ascii<char> (tmp, sizeof(tmp));
	strncpy(out.mac_addr, tmp, sizeof(out.mac_addr));

	rand_mem_with_ascii<char> (tmp, sizeof(tmp));
	strncpy(out.frame_type, tmp, sizeof(out.frame_type));
	return 1;
} 

/****************************************************************************
* Description	随机填充第三个页面的, 工作站的信息. 
* @param 	
* @return 	
****************************************************************************/
template <> int RandData( Workstation  & out )
{
	char tmp[256];	
	rand_mem_with_ascii<char> (tmp, sizeof(tmp));
	strncpy(out.mac_addr, tmp, sizeof(out.mac_addr));	

	rand_mem_with_ascii<char> (tmp, sizeof(tmp));
	strncpy(out.inner_network, tmp, sizeof(out.inner_network));

	out.status=rand();	
	
	rand_mem_with_ascii<char> (tmp, sizeof(tmp));
	strncpy(out.cur_used_file,tmp,  sizeof(out.cur_used_file))	;
	
	return 1;
}

/****************************************************************************
* Description	 随机填充第四个页面的 进程管理的信息. 
* @param 	
* @return 	
****************************************************************************/
template <> int RandData( nw_process  & out )
{
	char tmp[256];	
	rand_mem_with_ascii<char> (tmp, sizeof(tmp));
	strncpy(out.mac_addr, tmp, sizeof(out.mac_addr)); 
	
	rand_mem_with_ascii<char> (tmp, sizeof(tmp));
	strncpy(out.inner_network, tmp, sizeof( out.inner_network));

	rand_mem_with_ascii<char> (tmp, sizeof(tmp));
	strncpy(out.process_name, tmp, sizeof(out.process_name));	
	
	out.status=rand();
	
	return 1;
}

