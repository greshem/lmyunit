// Comm.h				公共头文件
// Ver 1.0.0.0
// 最后修改: 2002.5.31

#ifndef _COMM_H		//避免多次编译
#define _COMM_H

 /******
     由于NDEBUG是为程序调试(debug)期间使用的，当调试期完毕，程序出
 发行版(release)后，NDEBUG将失去作用。为了能够使assert()函数在发行
 版中也可以使用，则定义了下面的条件编译NDEBUG，意思为：
     如果已经定义NDEBUG，则定义宏Assert(x)：当x为假时，执行throw，
 交由系统已定义的方式处理；否则将Assert(x)定义为函数assert(x)，该
 函数对 参数x进行测试：x为假时，函数终止程序并打印错误信息。
 *****/
 #ifdef NDEBUG			
  #define Assert(x)	if (!x)	throw;	
 #else			//否则用系统定义的函数assert()处理
  #include <cassert>
  #define Assert(x)	assert(x);
 #endif			//NDEBUG

 #include <complex>		//模板类complex的标准头文件
 #include <valarray>	//模板类valarray的标准头文件
 using namespace std;	//名字空间

 const float  FLOATERROR = 1.0e-6F;
 const double DOUBLEERROR = 1.0e-15;
 const long double LONGDOUBLEERROR = 1.0e-30;

 const double GoldNo = 0.618033399;		//黄金分割常数(1.0-0.381966)
 
 //取x绝对值
 template <class T>		
 long double Abs(const T& x);				

 //取x符号，+-或0
 template <class T>		
 T Sgn(const T& x);
 
 //比较两float浮点数相等
 bool FloatEqual(float lhs, float rhs);		
 //比较两float浮点数不相等
 bool FloatNotEqual(float lhs, float rhs);		
 //比较两double浮点数相等
 bool FloatEqual(double lhs, double rhs);		
 //比较两double浮点数不相等
 bool FloatNotEqual(double lhs, double rhs);	
 //比较两long double浮点数相等
 bool FloatEqual(long double lhs, long double rhs);	
 //比较两long double浮点数不相等
 bool FloatNotEqual(long double lhs, long double rhs);	

 //求x与y的最小值，返回小者
 template <class T>
 T Min(const T& x, const T& y);

 //求x与y的最大值，返回大者
 template <class T>
 T Max(const T& x, const T& y);

 //打印数组(向量)所有元素值
 template <class T>
 void ValarrayPrint(const valarray<T>& vOut);
 
 //打印某个指定数组(向量)元素值
 template <class T>
 void ValarrayPrint(const valarray<T>& vOut, size_t sPosition);
 
// #include "Comm.inl"	//实现

// Comm.inl		公共函数（方法）定义
// Ver 1.0.0.0
// 版权所有(C) greshem, 2002
// 最后修改: 2002.5.31

#ifndef _COMM_INL
#define _COMM_INL

template <class T>
inline long double		//判断绝对值
Abs(const T& x)
{
	complex<long double> cld(x);
	long double ldAbs = abs(cld);
	return(ldAbs);
}

template <class T>
inline T			//取x符号，+-0
Sgn(const T& x)
{
	return x < T(0) ? T(-1) : (x > T(0) ? T(1) : T(0));
}


inline bool			//判断float浮点数相等
FloatEqual(float lhs, float rhs)
{
	if (Abs(lhs - rhs) < FLOATERROR)
		return true;
	else
		return false;
}

inline bool			//判断float浮点数不相等
FloatNotEqual(float lhs, float rhs)
{
	if (Abs(lhs - rhs) >= FLOATERROR)
		return true;
	else
		return false;
}

inline bool			//判断double浮点数相等
FloatEqual(double lhs, double rhs)
{
	if (Abs(lhs - rhs) < DOUBLEERROR)
		return true;
	else
		return false;
}

inline bool			//判断double浮点数不相等
FloatNotEqual(double lhs, double rhs)
{
	if (Abs(lhs - rhs) >= DOUBLEERROR)
		return true;
	else
		return false;
}

inline bool				//比较两long double浮点数相等
FloatEqual(long double lhs, long double rhs)
{
	if (Abs(lhs - rhs) < LONGDOUBLEERROR)
		return true;
	else
		return false;
}

inline bool				//比较两long double浮点数不相等
FloatNotEqual(long double lhs, long double rhs)
{
	if (Abs(lhs - rhs) >= LONGDOUBLEERROR)
		return true;
	else
		return false;
}
 
template <class T>
inline T
Min(const T& x, const T& y)			//比较x与y，返回小者
{
	if(x < y)
		return x;
	else
		return y;
}

template <class T>
T Max(const T& x, const T& y)		//求x与y的最大值，返回大者
{
	if(x > y)
		return x;
	else
		return y;
}

//打印数组(向量)所有元素值
template <class T>
void ValarrayPrint(const valarray<T>& vOut)
{
	size_t vsize = vOut.size();		//取数组元素的个数
	for(size_t st=0; st<vsize; st++)
	{
		std::cout.width(15);				//元素对齐，让每个元素占15列
		std::cout << vOut[st] << ' ';
	}
	cout << endl;
}

//打印某个指定数组(向量)元素值
template <class T>
void ValarrayPrint(const valarray<T>& vOut, size_t sPosition)
{
	std::cout.width(15);					//元素对齐，让每个元素占15列
	std::cout << vOut[sPosition] << endl;
}

#endif			// _COMM_INL

#endif	// _COMM_H

