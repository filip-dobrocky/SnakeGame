#include "pch.h"

char **createMatrix(int m, int n) {
	char** matrix = new char*[m];
	for (int i = 0; i < m; i++)
	{
		matrix[i] = new char[n];
	}
	return matrix;
}

void initMatrix(char **matrix, int m, int n) {
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			matrix[i][j] = ' ';
		}
	}
}

