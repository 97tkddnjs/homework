test 용 입니다~~


```cpp

#include<iostream>
#include<algorithm>
#include<string>
#include<cstdint>
#include<vector>
#include<typeinfo>
#include<cstddef>
using namespace std;

struct Employee {	// 2 + (2) + 4 + 8 =16 //padding 2추가된거
					//컴파일러 선생님한테 물어봐라 최적화 때문에 그런 것
	short id;		// 2 bytes
	int age;		// 4 bytes
	double wage;	// 8 bytes
};
struct person {
	double height;
	float weight;
	int age;
	string name;


	void printPerson()
	{
		cout << height << weight << endl;
	}
};

int main(void)
{
	//cout<<typeid(person).name()<<endl;
	//cout << sizeof(person) << endl;
	//person me{ 2.0,100.0, 20 , "jack"};//uniform initializer가 도움
	////me.printPerson();
	//cout << (2 >> 2) << endl;

	int x = 12;
	double d = 124.5;

	int* ptr_x = &x;
	double* ptr_d = &d;
	person p;

	cout << sizeof(x) << endl;
	cout << sizeof(d) << endl;

	cout << sizeof(&x) << " " << sizeof(ptr_x) << endl;
	cout << sizeof(&d) << " " << sizeof(ptr_d) << endl;

	cout << sizeof(person) << " " << sizeof(&p) << endl;

	std::nullptr_t  nptr;		//파라미터 중에 nullptr받는 경우에만 사용 nullptr만 받을 수 있다.
}

```


well good~~