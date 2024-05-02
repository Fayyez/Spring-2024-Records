#include<iostream>
#include<fstream>
using namespace std;

int** InputMatrix(ifstream& fin, int& rows, int& cols) {
	fin >> rows>>cols;
	cout<<"No of rows: " << rows << endl << "Number of cols:"  << cols << endl;
	int** Matrix = new int* [rows];
	for (int i = 0;i < rows;i++)
	{
		*(Matrix + i) = new int[cols];
		for (int j = 0;j < cols;j++)
		{
			fin >> *(*(Matrix + i) + j);
		}
	}
	return Matrix;
}
void OutputMatrix(int** Matrix, const int &rows, const int &cols) {
	for (int i = 0;i < rows;i++)
	{
		for (int j = 0;j < cols;j++)
		{
			cout<< *(*(Matrix + i) + j)<<"  ";
		}
		cout << endl;
	}
}
int** AddMatrix(int** matrix1, int** matrix2, const int &rows, const int &cols) {
	int** sum = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		*(sum + i) = new int[cols];
		for (int j = 0; j < cols; j++)
		{
			*(*(sum + i) + j) = *(*(matrix1 + i) + j) + *(*(matrix2 + i) + j);
		}
	}
	return sum;
}
int** TransposeMatrix(int** Matrix, const int &rows, const int &cols){
	int** Transpose = new int* [cols];
	for (int i = 0;i < cols;i++)
	{
		*(Transpose + i) = new int[rows];
    }
    for (int i = 0;i < rows;i++)
	{
		for (int j = 0;j < cols;j++)
		{
			*(*(Transpose+i)+j) = *(*(Matrix+j)+i);
		}
	}
	return Transpose;
}
bool IsSymmetric(int** Matrix, const int& rows, const int& cols) {
	if (rows != cols)
		return false;
	int** Transpose = TransposeMatrix(Matrix, rows, cols);
	for (int i = 0;i < rows;i++)
	{
		for (int j = 0;j < cols;j++)
		{
			if (*(*(Matrix + i) + j) != *(*(Transpose + i) + j))
				return false;
		}
	}
	return true;
}
void InterchangeRows(int*& row1, int*& row2) {
	int* temp = row1;
	row1 = row2;
	row2 = temp;
	temp = nullptr;
}
void InterchangeRows(int** Matrix, const int& rows, const int& cols) {
	int row1 = 0, row2 = 0;
	do
	{
		cout << "Enter 1st row no:";
		cin >> row1;
		cout << "Enter 2nd row no:";
		cin >> row2;
	} while (row1<0 || row1>rows || row2<0 || row2>rows);

	InterchangeRows(*(Matrix + row1), *(Matrix + row2));
}
int main() {
	ifstream fin("Input.txt");

	if (!fin.is_open()) {
		cout << "Failed to open the input file." << endl;
		return 1; 
	}
	int rows1 = 0, cols1 = 0;
	int** matrix1 = InputMatrix(fin, rows1, cols1);
    cout << "Matrix A ="<<endl;
	OutputMatrix(matrix1, rows1, cols1);

	int rows2 = 0, cols2 = 0;
	int** matrix2 = InputMatrix(fin, rows2, cols2);
    cout << "Matrix B ="<<endl;
	OutputMatrix(matrix2, rows2, cols2);
	
 int rows3 = 0, cols3 = 0;
	int** matrix3 = InputMatrix(fin, rows3, cols3);
    cout << "Matrix C ="<<endl;
	OutputMatrix(matrix3, rows3, cols3);
	
 fin.close();
	
	if (rows1 == rows2 && cols1 == cols2) {
		int** matrixSum=AddMatrix(matrix1, matrix2, rows1, cols2);
        cout << "A+B="<<endl;
		OutputMatrix(matrixSum, rows1, cols2);
	}
	else {
		cout << "addition is not possible"<<endl;
	}
	int **TransposeA=TransposeMatrix(matrix1, rows1, cols1);
    cout << "Transpose of A is:"<<endl;
    OutputMatrix( TransposeA, rows1, cols1);

    int **TransposeC=TransposeMatrix(matrix2, rows2, cols2);
    cout << "Transpose of C is:"<<endl;
    OutputMatrix( TransposeC, rows2, cols2);
 

	if (IsSymmetric(matrix1, rows1, cols1))
	{
		cout << "Matrix A is symmetric" << endl;
	}
	else
	{
		cout << "Matrix A is not symmetric" << endl;
	}

    if (IsSymmetric(matrix2, rows2, cols2))
	{
		cout << "Matrix B is symmetric" << endl;
	}
	else
	{
		cout << "Matrix B is not symmetric" << endl;
	}


	InterchangeRows(matrix1, rows1, cols1);
    cout << "Matrix after interchanging rows of Matrix A";
	OutputMatrix(matrix1, rows1,cols1);
}