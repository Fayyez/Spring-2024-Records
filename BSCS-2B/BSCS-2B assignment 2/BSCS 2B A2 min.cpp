/*#include <iostream>
using namespace std;

class employee {
	string name;
	int age;
public:
	employee(string,int);
	void setname(string);
	void setage(int);
	string getname();
	int getage();
};

employee::employee(string a="No Name", int b=0) {
	name = a;
	age = b;
}

void employee::setname(string a) {
	name = a;
}

void employee::setage(int a) {
	age = a;
}

string employee::getname() {
	return name;
}

int employee::getage() {
	return age;
}
*/

#include<iostream>
#include<fstream>
using namespace std;

int** input(int& rows, int& columns, ifstream& data) {
	data >> rows;
	data >> columns;
	int** temp;
	temp = new int* [rows];
	for (int i = 0; i < rows; i++) {
		*(temp+i) = new int[columns];
		for (int j = 0; j < columns; j++) {
			data >> *(*(temp + i) + j);
		}
	}
	return temp;
}


void output(int** temp, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		int z;
		cout << "|     ";
		for (int j = 0; j < columns; j++) {
			z = 0;
			if (*(*(temp + i) + j) > 9) {
				z++;
			}
			cout << *(*(temp + i) + j)<< "  ";
		}
		for (int i = 0; i < 5 - z; i++) {
			cout << " ";
		}
		cout << "|" << endl;
	}
	cout << endl << endl << endl;
}

int main() {

	int rows1 = 0; int columns1 = 0; int rows2 = 0; int columns2 = 0; int rows3 = 0; int columns3 = 0;

	ifstream data("InputFile.txt");

	int** matrix = input(rows1, columns1, data);
	cout << "The Matrix A is : " << endl;
	output(matrix, rows1, columns1);

	int** matrix2 = input(rows2, columns2, data);
	cout << "The Matrix B is : " << endl;
	output(matrix2, rows1, columns2);

	int** matrix3 = input(rows3, columns3, data);
	cout << "The Matrix C is : " << endl;
	output(matrix3, rows3, columns3);
}
