#ifndef __TOOLS_H__
#define __TOOLS_H__

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
#include "mstring.h"

       #include <sys/types.h>
       #include <sys/stat.h>
#ifdef WINDOWSCODE
#else
       #include <unistd.h>
#endif

//       #include <sys/types.h>
//       #include <sys/stat.h>
//       #include <unistd.h>


using namespace std;

int  shell_exec(string const in, string &out);
template <typename T> void split( const string& source, T & string_out_list,const string& separator );


void  rand_mem_with_ascii_tools (char *input, int strLen);
inline string ltrim(string const &str) ;
inline string rtrim(string const &str) ;
//inline string trim(string const &str) ;
string trim(string const &str) ;
string str_replace( const string & pattern, const string &replacement, const string & strIn) ;
long long  filesize (string file);
 
string RandWord();
vector<string>  RandWord(int count);

int file_put_content(string outfile , string in, bool append);
int file_get_content(string file, string &out);
string  ucfirst(string const &str);

char *file_seek64_and_read(FILE * file, int offset, int count, int * readLen);




#endif


