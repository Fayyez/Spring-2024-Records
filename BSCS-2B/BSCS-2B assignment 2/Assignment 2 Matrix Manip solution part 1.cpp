#include <iostream>
#include <fstream>
using namespace std;

int** InputMatrix(ifstream& fin, int& rows, int& cols)
{
	fin >> rows;
	fin >> cols;
	
	int** tempMatrix = new int*[rows];
	int** endOfRows = tempMatrix + rows;

	for (; tempMatrix < endOfRows; tempMatrix++)
		*(tempMatrix) = new int[cols];

	tempMatrix = endOfRows - rows;

	for (; tempMatrix < endOfRows; tempMatrix++)
	{
		int* endOfCols = *tempMatrix + cols;
		for (int* colPtr = *tempMatrix; colPtr < endOfCols; colPtr++)
			fin >> *(colPtr);
	}

	return tempMatrix - rows;
}

void OutputMatrix(int** matrix, const int& ROWS, const int& COLS)
{
	int** endOfRows = matrix + ROWS;

	for (; matrix < endOfRows; matrix++)
	{
		int* endOfCols = *matrix + COLS;
		for (int* colPtr = *matrix; colPtr < endOfCols; colPtr++)
			cout << *(colPtr) << "\t";
		cout << "\n";
	}
	cout << "\n";

	matrix = endOfRows - ROWS;
}

int** AddMatrix(int** matrixA, int** matrixB, const int& ROWS, const int& COLS)
{
	int** matrixR = new int* [ROWS];
	int** endOfRows = matrixR + ROWS;

	for (; matrixR < endOfRows; matrixR++)
		*(matrixR) = new int[COLS];

	matrixR = endOfRows - ROWS;

	for (; matrixR < endOfRows; matrixR++, matrixA++, matrixB++)
	{
		int* endOfCols = *matrixR + COLS;
		for (int *colPtr = *matrixR, *aPtr = *matrixA, *bPtr = *matrixB; colPtr < endOfCols; colPtr++, aPtr++, bPtr++)
			*colPtr = *aPtr + *bPtr;
	}

	matrixA = matrixA - ROWS;
	matrixB = matrixB - ROWS;

	return matrixR - ROWS;
}

int** TransposeMatrix(int** matrix, const int& ROWS, const int& COLS)
{
	int** tempMatrix = new int* [ROWS];
	for (int i = 0; i < ROWS; i++)
		*(tempMatrix + i) = new int[COLS];

	for (int i = 0; i < COLS; i++)
		for (int j = 0; j < ROWS; j++)
			*(*(tempMatrix + j) + i) = *(*(matrix + i) + j);

	return tempMatrix;
}

bool IsSymmetric(int** matrix, const int& ROWS, const int& COLS)
{
	bool symmetric = true;
	int** transpose = TransposeMatrix(matrix, ROWS, COLS);

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
			if (*(*(transpose + i) + j) != *(*(matrix + i) + j))
			{
				symmetric = false;
				break;
			}
		if (symmetric == false)
			break;
	}

	return symmetric;
}

void InterchangeRows(int*& row1, int*& row2)
{
	int* temp = 0;
	temp = row1;
	row1 = row2;
	row2 = temp;
}

void InterchangeRows(int** matrix, const int& ROWS, const int& COLS)
{
	cout << "row 1 : 1\n";
	cout << "row 2 : 3\n";

	InterchangeRows(*(matrix + 0), *(matrix + 2));
}

int main()
{
    ifstream file("InputFile.txt");
	if (file.is_open())
	{
		int rowsA = 0, colsA = 0, rowsB = 0, colsB = 0, rowsC = 0, colsC = 0;

		cout << "Matrix A = \n";
		int** matrixA = InputMatrix(file, rowsA, colsA);
		OutputMatrix(matrixA, rowsA, colsA);

		cout << "\nMatrix B = \n";
		int** matrixB = InputMatrix(file, rowsB, colsB);
		OutputMatrix(matrixB, rowsB, colsB);

		cout << "\nMatrix C = \n";
		int** matrixC = InputMatrix(file, rowsC, colsC);
		OutputMatrix(matrixC, rowsC, colsC);

		cout << "\nA + B = \n";
		if (rowsA == rowsB && colsA == colsB) {
			OutputMatrix(AddMatrix(matrixA, matrixB, rowsA, colsA), rowsA, colsA);
		}
		else
			cout << "Addition not possible.\n";

		cout << "\nA + C = \n";
		if (rowsA == rowsC && colsA == colsC) {
			OutputMatrix(AddMatrix(matrixA, matrixC, rowsA, colsA), rowsA, colsA);
		}
		else
			cout << "Addition not possible.\n";

		cout << "\nTranspose of A = \n";
		OutputMatrix(TransposeMatrix(matrixA, colsA, rowsA), colsA, rowsA);

		cout << "\nTranspose of C = \n";
		OutputMatrix(TransposeMatrix(matrixC, colsC, rowsC), colsC, rowsC);

		if (IsSymmetric(matrixA, rowsA, colsA) == true)
			cout << "\nMatrix A is Symmetric.\n";
		else
			cout << "\nMatrix A is NOT Symmetric.\n";

		if (IsSymmetric(matrixB, rowsB, colsB) == true)
			cout << "\nMatrix B is Symmetric.\n";
		else
			cout << "\nMatrix B is NOT Symmetric.\n";

		cout << "\nInterchanging Rows of Matrix A:\n";
		InterchangeRows(matrixA, rowsA, colsA);
		cout << "\nAfter interchanging rows, Matrix A = \n";
		OutputMatrix(matrixA, rowsA, colsA);

	}
	else
		cout << "Unable to open file." << endl;
}

