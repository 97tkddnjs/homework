#include<iostream>
# include<cmath>
#include<vector>
#include<tuple>
#include<functional>
#include<cassert>

using namespace std;

typedef int* pint;

//이런 식으로 reference를 통해 반환 여러개 해줄 수 있음~~
//반환 값을 하나 밖에 못 해줘서...
void getSinCos(const double deg, double& sin_out, double& cos_out) 
{
	static const double PI = 3.141592; // / 180.0;여기에 있으면 연산 한 번만 하게 되는 장점 tip;
	double radians = deg * PI / 180.0;
	sin_out = std::sin(radians);
	cos_out = std::cos(radians);
}

//pint &ptr로 해도 되긴 함
void foo(int*& ptr) //(int*) &ptr 같은 것이라고 생각하면 된다
{

}

//(vectr<int> &arr) 도 ㄱㅊ
void printElement(int(&arr)[4])//정적 할 때 []안에 숫자 써주기~
{							   // 보통은 동적일 때 많이 함수 사용한다고 함

}

int main()
{

	const int x = 5;
	//int* ptr = &x;	//pint ptr로 치환해서 생각해도 ㄱㅊ음~
	int arr[]{ 1,2,3,4 };

	printElement(arr);
	assert(false);
	static_assert(); //컴파일 타임에 결정되는 것만 사용할 수 있다.

	foo(ptr);
	return 0;
}