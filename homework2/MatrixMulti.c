#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include "time.h"

#define MatrixOrder 2048
#define N 999

float matrixA[MatrixOrder][MatrixOrder];
float matrixB[MatrixOrder][MatrixOrder];
float matrxiMultiResult[MatrixOrder][MatrixOrder];
float matrxiMultiResultOMP[MatrixOrder][MatrixOrder];



void matrixInit()
{
	srand(time(0));
	int row, col;
	//#pragma omp parallel for num_threads(64)
	for (row = 0; row < MatrixOrder; row++)
	{
		for (col = 0; col < MatrixOrder; col++)
		{
			matrixA[row][col] = rand() % (N + 1) / (float)(N + 1);
			matrixB[row][col] = rand() % (N + 1) / (float)(N + 1);
		}
	}
}

float calcuPartOfMatrixMulti(int row, int col)
{
	float partOfMatrixMultiResult = 0.0;
	int i;
	for (i = 0; i < MatrixOrder; i++) 
	{
		partOfMatrixMultiResult += matrixA[row][i] * matrixB[i][col];
	}
	return partOfMatrixMultiResult;
}

void matrixMuti()
{
	int row, col;
	for (row = 0; row < MatrixOrder; row++)
	{
		for (col = 0; col < MatrixOrder; col++)
		{
			matrxiMultiResult[row][col] = calcuPartOfMatrixMulti(row, col);
		}
	}
}

float calcuPartOfMatrixMultiOMP(int row, int col)
{
	float partOfMatrixMultiResult = 0.0;
	int i;
	#pragma omp parallel for num_threads(64)
	for (i = 0; i < MatrixOrder; i++)
	{
		partOfMatrixMultiResult += matrixA[row][i] * matrixB[i][col];
	}
	return partOfMatrixMultiResult;
}

void matrixMutiOMP()
{
	int row, col;
	#pragma omp parallel for num_threads(64)
	for (row = 0; row < MatrixOrder; row++)
	{
		for (col = 0; col < MatrixOrder; col++)
		{
			matrxiMultiResultOMP[row][col] = calcuPartOfMatrixMulti(row, col);
		}
	}
}

int main() {
	printf("矩阵阶数: %d \n", MatrixOrder);
	matrixInit();
	clock_t t1 = clock();
	matrixMuti();
	clock_t t2 = clock();
	printf("串行运算CPU时间：%f \n", (double)(t2 - t1) / CLOCKS_PER_SEC);
	clock_t t3 = clock();
	matrixMutiOMP();
	clock_t t4 = clock();
	printf("并行运算CPU时间：%f \n", (double)(t4 - t3) / CLOCKS_PER_SEC);
	system("pause");
	return 0;
}