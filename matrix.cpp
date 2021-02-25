#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;

#define ARR_ROW_SIZE 4
#define ARR_COL_SIZE 4


int** Make_A_Matrix(int a, int b, int c, int d)
{	
	int** tmp;
	int	NumOfCase[16][4] = {
		{0,0,0,0},
		{1,0,0,0},	//	1이 1가지인 경우
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1},
		{1,1,0,0},	//	1이 2가지인 경우
		{0,1,1,0},
		{0,0,1,1},
		{0,1,0,1},
		{1,0,1,0},
		{1,0,0,1},
		{1,1,1,0},	//	1이 3가지인 경우 
		{1,1,0,1},
		{1,0,1,1},
		{0,1,1,1},
		{1,1,1,1}
	};
	tmp = new int* [ARR_COL_SIZE];
	for (int i = 0; i < 4; i++)
	{
		tmp[i] = new int[ARR_COL_SIZE];
	}

	for (int i = 0; i < 4; i++) {
		tmp[0][i] = NumOfCase[a][i];
		tmp[1][i] = NumOfCase[b][i];
		tmp[2][i] = NumOfCase[c][i];
		tmp[3][i] = NumOfCase[d][i];
	
	}
	return tmp;

}
void print_matrix(int ** matrix, int row, int col)
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
int** TransePose(int** matrix, int Size)
{
	int** tmp;
	tmp = new int* [4];
	for (int i = 0; i < Size; i++) {
		tmp[i] = new int[Size];
		
	}
	
	tmp[0][0] = matrix[0][0];
	tmp[1][1] = matrix[1][1];
	tmp[2][2] = matrix[2][2];
	tmp[3][3] = matrix[3][3];
	

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
	FILE* fp =NULL;
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
	int** T_A;

	int count = 0;
	double iter = 0;
	double all = 16 * 16 * 16 * 16;

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k < 16; k++)
			{
				for (int t = 0; t < 16; t++)
				{	
					//printf("idx ::%d %d %d %d \n",i,j,k,t);
					A = Make_A_Matrix(i, j, k, t);
					T_A = TransePose(A, ARR_COL_SIZE); //A transpose됨
		

					res=MatrixMul(T_A, B);
					ModularFunc(res, ARR_COL_SIZE);

					res = MatrixMul(res, A); //(A_T)*B*A
					ModularFunc(res, ARR_COL_SIZE);
					/*
					cout << "result" << endl;
					print_matrix(res, ARR_ROW_SIZE, ARR_COL_SIZE);
					cout << endl;
					*/
					
					if (CheckSameMatrix(res, B, ARR_COL_SIZE)) {
						
						count++;
						/*
						print_matrix(res, ARR_ROW_SIZE, ARR_COL_SIZE);
						cout << endl;
						*/
						cout << "This matrix "<<count<<" matrix"<<endl;
						
						print_matrix(A, ARR_ROW_SIZE, ARR_COL_SIZE);
						cout << endl;
						
					}
					iter++;
					//cout << (iter/all)*100<<"%"<< endl;
					
					Clear_mem(A, ARR_COL_SIZE);
					Clear_mem(res, ARR_COL_SIZE);
					Clear_mem(T_A, ARR_COL_SIZE);
				}
			}
		}
	}
	cout << count << endl;
	
	
	
	Clear_mem(B, ARR_COL_SIZE);
	//Clear_mem(res, ARR_COL_SIZE);
	
	
	return 0;
} //result는 720개가 나옴