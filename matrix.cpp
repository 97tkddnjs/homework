#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;

#define ARR_ROW_SIZE 4
#define ARR_COL_SIZE 4

/* 사용한는 함수 설명
 * 
 *	Make_A_Matrix() 2^16 가지의 경우의 수를 만드는 함수 A를 만드는 함수
 *	MatrixMul()	행렬 곱을 시행 후 반환해주는 함수	
 *	TransePose()	전치 행렬을 만들어서 반환해주는 함수
 *	ModularFunc()	만약 값이 1,0이 아닐 경우 1 혹은 0으로 만들어 주는 함수
 *	CheckSameMatrix()	같은 지 체크하는 함수
 *
 *	print_matrix 결과값 확인을 위한 행렬 print함수
 *	
 *	Clear_mem() 동적할당을 통해 생성된 매트릴스들을 스택 메모리 구역에서 없애주는 함수
 *
 *
*/


/*
4*4행렬에서는 행렬 요소값이 0,1로만 이루어졌다는 가정하에는 한 행에서 나올 수 있는 행의 경우의 수가
16가지이다. 그래서 NumOfCase Array에 한 행에서 나올 수 있는 경우의 수인 16가지를 먼저 저장한다.
(또한 각각의 경우의 수를 0~15번까지 총 16개로 인덱스한다고 하자)
한 편 요소값이 0,1  2가지인 4*4행렬의 경우의 수는 총 16*16*16*16가지이다.
매개 변수 인자 a,b,c,d는 한 행에서 나올 수 있는 경우의 수인 16가지 중에서
몇 번째 경우의 수 인지를 의미한다. 
*/
int** Make_A_Matrix(int a, int b, int c, int d)
{	
	int** tmp;	//만들어지는 값을 반환해줄 변수 tmp
	int	NumOfCase[16][4] = {
		{0,0,0,0},
		{1,0,0,0},	//	1이 1가지일 때의 경우의 수
		{0,1,0,0},	
		{0,0,1,0},
		{0,0,0,1},
		{1,1,0,0},	//	1이 2가지일 때의 경우의 수
		{0,1,1,0},
		{0,0,1,1},
		{0,1,0,1},
		{1,0,1,0},
		{1,0,0,1},
		{1,1,1,0},	//	1이 3가지일 때의 경우의 수 
		{1,1,0,1},
		{1,0,1,1},
		{0,1,1,1},
		{1,1,1,1}
	};

	//tmp에 동적할당으로 2차원 배열을 만들어준다!
	tmp = new int* [ARR_COL_SIZE];	//int형 포인터를 동적할당
	for (int i = 0; i < 4; i++)
	{
		tmp[i] = new int[ARR_COL_SIZE];	//int형 배열을 동적할당
	}

	for (int i = 0; i < 4; i++) {	//매개변수로 들어온 경우의 수에 따라 각각의 값에 맞는 요소값을 저장해줌
		tmp[0][i] = NumOfCase[a][i];
		tmp[1][i] = NumOfCase[b][i];
		tmp[2][i] = NumOfCase[c][i];
		tmp[3][i] = NumOfCase[d][i];
	
	}
	return tmp;

}
//단순히 행렬 값을 보여주는 함수
void print_matrix(int ** matrix, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}
}

//행렬곱을 수행후 값을 반환해주는 함수
int** MatrixMul(int **A , int **B)
{
	
	int tmp = 0;
	int i, j, k;
	int** res = new int*[ARR_ROW_SIZE]; //반환해줄 변수 res
	

	for (k = 0; k < ARR_ROW_SIZE; k++) { //연산 후 행 idx인 k

		res[k] = new int[ARR_COL_SIZE];
		for (i = 0; i < ARR_ROW_SIZE; i++)	//연산 후 열 idx인 i
		{
			for (j = 0; j < ARR_COL_SIZE; j++)
			{
				tmp += A[k][j] * B[j][i];
			}
			res[k][i] = tmp;
			tmp = 0;
		}
	}
	return res;
}
//동적할당으로 차있던 스택 memory를 지워주는 함수
void Clear_mem(int** matrix, int size)
{
	for (int i = 0; i < 4; i++)
		delete[] matrix[i];

	delete[] matrix;
}
//전치 행렬을 하는 함수
int** TransePose(int** matrix, int Size)
{
	int** tmp;
	tmp = new int* [4];
	for (int i = 0; i < Size; i++) {
		tmp[i] = new int[Size];
		
	}
	//대각 성분의 값을 먼저 채우고
	tmp[0][0] = matrix[0][0];
	tmp[1][1] = matrix[1][1];
	tmp[2][2] = matrix[2][2];
	tmp[3][3] = matrix[3][3];
	
	//나머지 요소를 전치 시키자.
	for (int i = 0; i < Size -1; i++)
	{
		for (int j =i + 1; j < Size; j++)
		{
			//cout << i << " " << j<<endl;
			int tmp_v= matrix[i][j];
			tmp[i][j] = matrix[j][i];
			tmp[j][i]=tmp_v;
		}
	}
	return tmp;
	
}

//같은지 체크하는 함수
bool CheckSameMatrix(int** a, int** b, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (a[i][j] != b[i][j])
				return false;
		}
	}
	return true;
}
//매개변수로 받은 matrix값 자체를 0,1로 변환해준다.
void ModularFunc(int** matrix,int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			matrix[i][j] = matrix[i][j] % 2;
		}
	}
}
int main()
{	
	//B행렬
	int b[ARR_ROW_SIZE][ARR_COL_SIZE] = {
		{0,0,1,0},
		{0,0,0,1},
		{1,0,0,0},
		{0,1,0,0}
	};


	//A행렬의 값을 담을 틀을 생성
	int** A;
	A = new int* [ARR_COL_SIZE];

	for (int i = 0; i < ARR_ROW_SIZE; i++)
	{
		A[i] = new int[ARR_COL_SIZE];
	}

	//B행렬의 값을 담을 이중포인터 행렬
	int** B;
	B = new int* [ARR_COL_SIZE];
	for (int i = 0; i < ARR_ROW_SIZE; i++)
	{
		B[i] = new int[ARR_COL_SIZE];
		for (int j = 0; j < 4; j++)
		{
			B[i][j] = b[i][j];
		}
	}


	
	int** res;//결과값을 담을 res
	int** T_A;	//Transpose_A값을 받을 포인터 변수

	int count = 0; //총 개수를 담을 count

	//몇 %완료 되었는 지 확인하려고 만들었던 변수
	double iter = 0;
	double all = 16 * 16 * 16 * 16;
	
	
	//총 16*16*16*16가지 경우의 수 시뮬레이션 시작
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k < 16; k++)
			{
				for (int t = 0; t < 16; t++)
				{	
					//먼저 경우의 수에 따라 A값을 받는다
					A = Make_A_Matrix(i, j, k, t);
					//전치시킨 A값을 받는다.
					T_A = TransePose(A, ARR_COL_SIZE); //A transpose��
		
					//전치된 A와 B를 행렬 곱한다.
					res=MatrixMul(T_A, B);
					//만약 값이 0,1이 아니면 0,1로 만들어 줌
					ModularFunc(res, ARR_COL_SIZE);

					res = MatrixMul(res, A); //(A_T)*B*A
					//만약 값이 0,1이 아니면 0,1로 만들어 줌
					ModularFunc(res, ARR_COL_SIZE);
					/*디버깅을 위한 것
					cout << "result" << endl;
					print_matrix(res, ARR_ROW_SIZE, ARR_COL_SIZE);
					cout << endl;
					*/
					
					// 만약 조건에 맞으면  count++후 Print
					if (CheckSameMatrix(res, B, ARR_COL_SIZE)) {
						
						count++;
						/*디버깅을 위한 것
						print_matrix(res, ARR_ROW_SIZE, ARR_COL_SIZE);
						cout << endl;
						*/
						cout << "This matrix "<<count<<" matrix"<<endl;
						
						print_matrix(A, ARR_ROW_SIZE, ARR_COL_SIZE);
						cout << endl;
						
					}
					iter++;
					//cout << (iter/all)*100<<"%"<< endl;
					
					//할당 되었던 값 해제해줌
					Clear_mem(A, ARR_COL_SIZE);
					Clear_mem(res, ARR_COL_SIZE);
					Clear_mem(T_A, ARR_COL_SIZE);
				}
			}
		}
	}
	cout << count << endl;
	
	
	//모든 연산이 끝난 후 B도 동적할당 해제해줌
	Clear_mem(B, ARR_COL_SIZE);

	
	
	return 0;
} //result값은 720이였다.