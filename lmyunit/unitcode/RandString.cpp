#include "RandString.h"
 #include <unistd.h>
//string RandString(int strLen);
//vector<string> RandVecString(int strLen, int size);

struct  addSuffix
{
        string m_suffix;
        addSuffix(string in):m_suffix(in){};
        int operator() ( string &in)
        {
            in+=m_suffix;
            return 1;
        }
};


string RandString (int strLen)
{
	char *tmp;

	tmp=new char[strLen+1];
	tmp[strLen]='\0';
	
    for (int i=0; i< strLen; i++)
    {   
        *(tmp+i)='a'+rand()%26;
    }  
    string retStr(tmp);		
	delete[] tmp;
	return retStr;
}


void  rand_mem_with_ascii (char *input, int strLen)
{
    if(input == NULL|| strLen==0 )
    {
        return ;
    }

    for (int i=0; i<=strLen-1; i++)
    {
        *(input+i)='a'+rand()%26;
    }
    input[strLen-1]='\0';
}

/****************************************************************************
* Description	
* @param 	
* @return 	
* *************************************************************************/
 string RandPath(int number)
{
	static int  pathLength=8;
	string path("./");
	for(int i=0;i<=number; i++)
	{
		path+=RandString(rand()%pathLength +1 );
		path+="/";	
	}
	return path;
}
/****************************************************************************
* Description	
* @param 	
* @return 	
* *************************************************************************/
 string RandFilePath (int number)
{
	static int  pathLength=8;
	string path("./");
	for(int i=0;i<=number; i++)
	{
		path+=RandString(rand()%pathLength +1 );
		path+="/";	
	}
	
	path+=RandString(rand()%pathLength +1 );
	return path;

}
/****************************************************************************
* Description	
* @param 	
* @return 	
* *************************************************************************/
vector<string> RandVecString (int strLen, int size)
{
	//int i=0;
	vector<string> vecStr;
	for(int i=0; i< size; i++)
	{
		
		vecStr.push_back(RandString(strLen));
	}
	return vecStr;
}
/****************************************************************************
* Description	
* @param 	
* @return 	
* *************************************************************************/

char  * stringFromFile (char *fileName)
{	
	#ifdef WINDOWSCODE
	return "no file";
#else
    char *str;
	struct stat st;
	if(stat(fileName, &st)< 0)
    {
       return NULL;
    }
	int fd;
	fd=open(fileName, O_RDONLY);
	if(fd <0 )
	{	
		return NULL;
	}
	str=(char*)malloc(st.st_size+1);
	read(fd,str,st.st_size);
	//str[st.st_size+1]='\0';
	str[st.st_size]='\0';
	close(fd);
	return str;
#endif
	
}

/*int main(int argc, char *argv[])
{
	vector<string> vecStr =  RandVecString(10, 100);
	cout<<"size = "<<vecStr.size()<<endl;
	//for_each(vecStr.begin(), vecStr.end(), myPrint );
	sort(vecStr.begin(), vecStr.end());
	//for_each(vecStr.begin(), vecStr.end(), myPrint );
	for_each(vecStr.begin(), vecStr.end(), addSuffix(".mp3"));
	for_each(vecStr.begin(), vecStr.end(), addSuffix(".mp3"));
   copy(vecStr.begin(), vecStr.end(), ostream_iterator<string>(cout, "\n"));
   getchar();
	return 1;
}*/
