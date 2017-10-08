//Comm.cpp				使用公共头文件示例
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

//#include <iomapip>
//########################################################################
//#include <QzjUnit.hpp>
//#include <MLmyUnit.hpp>
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
#include <iostream>		//输入输出流头文件

#include <numerical_math.hpp>

using namespace std;	//名字空间

// 定义控制台应用程序的入口点
int main()
{
	int ia(10), ib(-23);
	double fx(1.5369200000000001), fy(-38.67);
	complex<double> cf(fx, fy);

	//显示初始数据
	cout << "初始数据：" << endl;
	cout << "  ia = " << ia << endl;
	cout << "  ib = " << ib << endl;
	printf("  fx = %25.20f \n", fx);
	printf("  fy = %25.20f \n", fy);
	cout << "  cf = " << cf << endl << endl;
	
	//取绝对值运算
	cout << "取绝对值运算：" << endl;
	cout << "  Abs(ia) = " << Abs(ia) << endl;
	cout << "  Abs(ib) = " << Abs(ib) << endl;
	cout << "  Abs(fx) = " << Abs(fx) << endl;
	cout << "  Abs(fy) = " << Abs(fy) << endl;
	cout << "  Abs(cf) = " << Abs(cf) << endl << endl;

	//取符号运算
	cout << "取符号运算：" << endl;
	cout << "  Sgn(ia) = " << Sgn(ia) << endl;
	cout << "  Sgn(ib) = " << Sgn(ib) << endl;
	cout << "  Sgn(fx) = " << Sgn(fx) << endl;
	cout << "  Sgn(fy) = " << Sgn(fy) << endl << endl;

	//浮点数比较
	cout << "浮点数比较：" << endl;
	if(FloatEqual(fx,1.53692)) 
		printf("  fx == 1.53692 \t fx = %25.20f \n\n", fx);
	else
		printf("  fx != 1.53692 \t fx = %25.20f \n\n", fx);

	if(FloatNotEqual(fy,-38.671)) 
		printf("  fy != -38.671 \t fy = %25.20f \n\n", fy);
	else
		printf("  fy == -38.671 \t fy = %25.20f \n\n", fy);

	//求最小值运算
	cout << "求最小值运算：" << endl;
	cout << "  Min(ia, ib) = " << Min(ia, ib) << endl << endl;

	//求最大值运算
	cout << "求最大值运算：" << endl;
	cout << "  Max(fx, fy) = " << Max(fx, fy) << endl << endl;

	double a[4] = {1.01, 1.02, 1.03, 2.04};

	valarray<double> va(a, 4);

	//打印数组(向量)值
	cout << "打印数组(向量)值：" << endl;
	ValarrayPrint(va);
	cout << endl;

	//打印某个指定数组(向量)元素值
	cout << "打印某个指定数组(向量)元素值：" << endl;
	for(ia=0; ia<4; ia++)
		ValarrayPrint(va, ia);
}

