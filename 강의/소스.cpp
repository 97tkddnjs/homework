#include<iostream>
# include<cmath>
#include<vector>
#include<tuple>
#include<functional>
#include<cassert>

using namespace std;

typedef int* pint;

//�̷� ������ reference�� ���� ��ȯ ������ ���� �� ����~~
//��ȯ ���� �ϳ� �ۿ� �� ���༭...
void getSinCos(const double deg, double& sin_out, double& cos_out) 
{
	static const double PI = 3.141592; // / 180.0;���⿡ ������ ���� �� ���� �ϰ� �Ǵ� ���� tip;
	double radians = deg * PI / 180.0;
	sin_out = std::sin(radians);
	cos_out = std::cos(radians);
}

//pint &ptr�� �ص� �Ǳ� ��
void foo(int*& ptr) //(int*) &ptr ���� ���̶�� �����ϸ� �ȴ�
{

}

//(vectr<int> &arr) �� ����
void printElement(int(&arr)[4])//���� �� �� []�ȿ� ���� ���ֱ�~
{							   // ������ ������ �� ���� �Լ� ����Ѵٰ� ��

}

int main()
{

	const int x = 5;
	//int* ptr = &x;	//pint ptr�� ġȯ�ؼ� �����ص� ������~
	int arr[]{ 1,2,3,4 };

	printElement(arr);
	assert(false);
	static_assert(); //������ Ÿ�ӿ� �����Ǵ� �͸� ����� �� �ִ�.

	foo(ptr);
	return 0;
}