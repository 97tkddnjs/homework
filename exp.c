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
	static int a;	//���� ���� �ش� ���� �Ѿ�� ����ִ�. ���� ǥ ���� �� �� ����

	int num[9] = { 1,2,3,4,5,6,7,8,9 };
	int k = 0;

	

	//��� �����迭�� �Ҵ��ϱ�
	int** twop =NULL;
	int* p;
	twop = (int**)malloc(3 * sizeof(int*));
	
	for (int i = 0; i < 3; i++)
	{
		// ������� �߸��� ���� �ִٴ� ���� ���
		// malloc�Լ��� �ݵ�� �����ϴ� �Լ��� �ƴϱ� �����̴�.
		//�޸� �Ҵ� ������ ���� ������ NULL�� ��ȯ�ϰ� �ȴ�!
		
		p = (int*)malloc(3 * sizeof(int));
		twop[i] = p;
	}
	

	//�����Ҵ��� �ڹٳ� ���̽�� �ٸ��� ���� �޸� ������ ���־�� �Ѵ�.

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