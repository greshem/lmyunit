//Comm.cpp				ʹ�ù���ͷ�ļ�ʾ��
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
#include <iostream>		//���������ͷ�ļ�

#include <numerical_math.hpp>

using namespace std;	//���ֿռ�

// �������̨Ӧ�ó������ڵ�
int main()
{
	int ia(10), ib(-23);
	double fx(1.5369200000000001), fy(-38.67);
	complex<double> cf(fx, fy);

	//��ʾ��ʼ����
	cout << "��ʼ���ݣ�" << endl;
	cout << "  ia = " << ia << endl;
	cout << "  ib = " << ib << endl;
	printf("  fx = %25.20f \n", fx);
	printf("  fy = %25.20f \n", fy);
	cout << "  cf = " << cf << endl << endl;
	
	//ȡ����ֵ����
	cout << "ȡ����ֵ���㣺" << endl;
	cout << "  Abs(ia) = " << Abs(ia) << endl;
	cout << "  Abs(ib) = " << Abs(ib) << endl;
	cout << "  Abs(fx) = " << Abs(fx) << endl;
	cout << "  Abs(fy) = " << Abs(fy) << endl;
	cout << "  Abs(cf) = " << Abs(cf) << endl << endl;

	//ȡ��������
	cout << "ȡ�������㣺" << endl;
	cout << "  Sgn(ia) = " << Sgn(ia) << endl;
	cout << "  Sgn(ib) = " << Sgn(ib) << endl;
	cout << "  Sgn(fx) = " << Sgn(fx) << endl;
	cout << "  Sgn(fy) = " << Sgn(fy) << endl << endl;

	//�������Ƚ�
	cout << "�������Ƚϣ�" << endl;
	if(FloatEqual(fx,1.53692)) 
		printf("  fx == 1.53692 \t fx = %25.20f \n\n", fx);
	else
		printf("  fx != 1.53692 \t fx = %25.20f \n\n", fx);

	if(FloatNotEqual(fy,-38.671)) 
		printf("  fy != -38.671 \t fy = %25.20f \n\n", fy);
	else
		printf("  fy == -38.671 \t fy = %25.20f \n\n", fy);

	//����Сֵ����
	cout << "����Сֵ���㣺" << endl;
	cout << "  Min(ia, ib) = " << Min(ia, ib) << endl << endl;

	//�����ֵ����
	cout << "�����ֵ���㣺" << endl;
	cout << "  Max(fx, fy) = " << Max(fx, fy) << endl << endl;

	double a[4] = {1.01, 1.02, 1.03, 2.04};

	valarray<double> va(a, 4);

	//��ӡ����(����)ֵ
	cout << "��ӡ����(����)ֵ��" << endl;
	ValarrayPrint(va);
	cout << endl;

	//��ӡĳ��ָ������(����)Ԫ��ֵ
	cout << "��ӡĳ��ָ������(����)Ԫ��ֵ��" << endl;
	for(ia=0; ia<4; ia++)
		ValarrayPrint(va, ia);
}

