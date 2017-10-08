//########################################################################
//#include <QzjUnit.hpp>
//#include <MLmyUnit.hpp>
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
template<> void dump(int &in)
{
    cout<<"int "<<in<<endl;
}

template<> void dump(IPXADDR * & wks)
{
            fprintf(stderr, "%08x %04x %02x:%02x:%02x:%02x:%02x:%02x %s login\n",
            (unsigned int)wks->network, wks->sock, wks->node[0],
            wks->node[1], wks->node[2], wks->node[3], wks->node[4], wks->node[5],
            //nwconn_context[nwconn_info_count].username);
			"who?" );
}

template <> void dump(vector<string> & in)
{
	typedef vector<string>::iterator IT;
	IT it;
	for(it=in.begin(); it!=in.end(); it++)
	{
		cout<< *it <<"|";
	}
	cout<<endl;
}
template <> void dump( BaseInfo  &in)
{
	cout<<in;	
}
