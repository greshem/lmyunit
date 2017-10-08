//rand_01_Series.cpp	产生[0,1]区间内均匀分布伪随机数序列
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

#include <iostream>		//输入输出流头文件			
#include <time.h>		//时间头文件
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

using namespace std;	//名字空间

int main(void)
{	
	double seed = (double)time(NULL);	//取种子
	valarray<double> dp(40);
	size_t stNum = 40;
	
	cout.setf(ios::fixed|ios::left);	//输出数据为定点法，靠左对齐
	cout.precision(6);					//精度6位

	rand_01_Series(seed, dp, stNum);	//生成[0,1]区间40个均匀随机数
	
	ValarrayPrint(dp);					//结果输出至显示器
	
	cout << endl;
}

