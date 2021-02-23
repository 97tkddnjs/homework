#include<iostream>
#include<cstdio>
#include<cstdlib>
#define SWAP(t, c_a, c_b) do{t tmp; tmp=c_a;c_a=c_b;c_b=tmp; }while(0)
using namespace std;

#define ARR_ROW_SIZE 4
#define ARR_COL_SIZE 4



void print_matrix(const int ** matrix, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}
}
int** MatrixMul(int **A , int **B)
{
	
	int tmp = 0;
	int i, j, k;
	int** res = new int*[ARR_ROW_SIZE];
	

	for (k = 0; k < ARR_ROW_SIZE; k++) {

		res[k] = new int[ARR_COL_SIZE];
		for (i = 0; i < ARR_ROW_SIZE; i++)
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
void Clear_mem(int** matrix, int size)
{
	for (int i = 0; i < 4; i++)
		delete[] matrix[i];

	delete[] matrix;
}
void TrnasPose(int** matrix, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			SWAP(int, matrix[i][j], matrix[j][i]);
		}
	}
}


int main()
{
	int b[ARR_ROW_SIZE][ARR_COL_SIZE] = {
		{0,0,1,0},
		{0,0,0,1},
		{1,0,0,0},
		{0,1,0,0}
	};

	int** A;
	A = new int* [ARR_COL_SIZE];

	for (int i = 0; i < ARR_ROW_SIZE; i++)
	{
		A[i] = new int[ARR_COL_SIZE];
		for (int j = 0; j < 4; j++)
		{
			A[i][j] = i + j;
		}
	}

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



	int** res;

	cout << "A_MATRIX" << endl;
	print_matrix(A, ARR_ROW_SIZE, ARR_COL_SIZE);
	

	res = MatrixMul(A,B);
	cout << "A*B_MATRIX" << endl;
	print_matrix(res, ARR_ROW_SIZE, ARR_COL_SIZE);
	cout << "T_a*b matrix" << endl;
	TrnasPose(res, ARR_COL_SIZE);
	print_matrix(res, ARR_ROW_SIZE, ARR_COL_SIZE);

	res = MatrixMul(res, A);

	cout << "res_MATRIX" << endl;
	print_matrix(res, ARR_ROW_SIZE, ARR_COL_SIZE);


	Clear_mem(A, ARR_COL_SIZE);
	Clear_mem(B, ARR_COL_SIZE);
	Clear_mem(res, ARR_COL_SIZE);
	

	return 0;
}