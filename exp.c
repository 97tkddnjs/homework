#include <stdio.h>
#include <stdlib.h>

int(*ReturnArray(int(*two_array)[3]))[3]
{
	
}


void println(char* a)
{
	printf(a);
	printf("\n");
}



int main()
{
	int arr[10] = { 0 };
	int arr2[5][4];
	static int a;	//정적 변수 해당 범위 넘어서도 살아있다. 이유 표 보면 알 수 있음

	int num[9] = { 1,2,3,4,5,6,7,8,9 };
	int k = 0;

	

	//행렬 동적배열로 할당하기
	int** twop =NULL;
	int* p;
	twop = (int**)malloc(3 * sizeof(int*));
	
	for (int i = 0; i < 3; i++)
	{
		// 녹색줄은 잘못될 수도 있다는 것을 경고
		// malloc함수가 반드시 성공하는 함수가 아니기 때문이다.
		//메모리 할당 조건이 맞지 않으면 NULL을 반환하게 된다!
		
		p = (int*)malloc(3 * sizeof(int));
		twop[i] = p;
	}
	

	//동적할당은 자바나 파이썬과 다르게 직접 메모리 해제를 해주어야 한다.

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			twop[i][j] = num[k];
			k++;
		}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
		{
			printf("%d ", twop[i][j]);
		}printf("\n");
	}

	for (int i = 0; i < 3; i++)
	{
		free(twop[i]);
	}
	free(twop);

	println("hello world");
	printf("avb");
	return 0;
}