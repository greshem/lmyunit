//rand_01_One.cpp	分别产生10个[0, 1]区间均匀分布的伪随机数
#include <fstream>
#include <dirent.h>
#include <string> 
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <map>
#include <iostream> 
#include <algorithm>
#include <vector> 
#include <iterator>  
#include <numerical_math.hpp>

//#include <random.h>			//随机算法头文件
#include <iostream>			//输入输出流头文件			
#include <time.h>			//时间头文件
//########################################################################
//#include <QzjUnit.hpp>
//#include <MLmyUnit.hpp>
// #include <Baselib.hpp>
// #include <gtest/gtest.h>
#include <fstream>
#include <dirent.h>
#include <string> 
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <map>
#include <iostream> 
#include <algorithm>
#include <vector> 
#include <iterator>  
#include <numerical_math.hpp>
using namespace std;		//名字空间

int main(void)
{	
	double seed = (double)time(NULL);	//取种子

	
	cout.setf(ios::fixed|ios::left);	//输出数据为定点法，靠左对齐
	cout.precision(6);					//精度6位

	for(size_t st = 0; st < 10; st++)
	{	
		double rand = rand_01_One(seed);//生成[0，1]区间随机数

		cout << " random = " << rand << endl;
	}
}

