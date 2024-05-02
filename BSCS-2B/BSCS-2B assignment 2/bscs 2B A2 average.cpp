


//Part 1: (Matrix Manipulation)

#include <iostream>
#include <fstream>
using namespace std;

// Function to input matrix from file
int** InputMatrix(ifstream& fin, int& rows, int& cols) {
	if (fin >> rows >> cols)
	{
		int** matrix = new int* [rows];
		for (int i = 0; i < rows; i++) {
			matrix[i] = new int[cols];

		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				fin >> *(*(matrix + i) + j);
			}
		}

		return matrix;
	}
	else
	{
		cerr << "Error reading integer from file" << endl;
		return nullptr;
	}

}

// Function to output matrix
void OutputMatrix(int** matrix, int& rows, const int& cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << *(*(matrix + i) + j) << " ";
		}
		cout << endl;
	}
}

// Function to add two matrices
int** AddMatrix(int** matrixA, int** matrixB, const int& rows, const int& cols) {
	int** matrixR = new int* [rows];
	for (int i = 0; i < rows; i++) {
		matrixR[i] = new int[cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			*(*(matrixR + i) + j) = *(*(matrixA + i) + j) + *(*(matrixB + i) + j);
		}
	}

	return matrixR;
}

// Function to transpose a matrix
int** TransposeMatrix(int** matrix, const int& rows, const int& cols) {
	int** matrixT = new int* [cols];
	for (int i = 0; i < cols; i++) {
		matrixT[i] = new int[rows];
	}
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			*(*(matrixT + i) + j) = *(*(matrix + j) + i);
		}
	}
	return matrixT;
}

// Function to check if a matrix is symmetric
bool IsSymmetric(int** matrix, const int& rows, const int& cols) {
	int** matrixT = TransposeMatrix(matrix, rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (matrix[i][j] != matrixT[i][j]) {
				return false;
			}
		}
	}
	return true;
}


int main() {
	// ofstream fo("Input.txt");
	 //ifstream fin("Input.txt");
	 //ifstream myfile;
	 //myfile.open("Matrix.cpp",ios::in);
	ifstream myfile;
	myfile.open("oop.txt", ios::in);//////txt

	if (myfile.is_open())
	{
		int** matrixA;
		int** matrixB;
		int** matrixC;
		int rowA, rowB, rowC, row1 = 1, row2 = 3;
		int colA, colB, colC;
		matrixA = InputMatrix(myfile, rowA, colA);
		matrixB = InputMatrix(myfile, rowB, colB);
		matrixC = InputMatrix(myfile, rowC, colC);

		cout << "matrixA" << endl;
		if (matrixA != nullptr) {
			cout << "No of rows " << rowA << endl;
			cout << "No of cols " << colA << endl;
			OutputMatrix(matrixA, rowA, colA);
		}

		cout << "matrixB" << endl;
		if (matrixB != nullptr) {
			cout << "No of rows " << rowB << endl;
			cout << "No of cols " << colB << endl;
			OutputMatrix(matrixB, rowB, colB);
		}

		cout << "matrixC" << endl;
		if (matrixC != nullptr) {
			cout << "No of rows " << rowC << endl;
			cout << "No of cols " << colC << endl;
			OutputMatrix(matrixC, rowC, colC);
		}

		if (rowA == rowB && colA == colB) {
			int** S = AddMatrix(matrixA, matrixB, rowA, colA);
			cout << "Sum of matrices: " << endl;
			OutputMatrix(S, rowA, colA);
		}

		if (rowA == colA) {
			int** S = TransposeMatrix(matrixA, rowA, colB);
			cout << " Transposed matrix is: " << endl;
			OutputMatrix(S, rowA, colA);
		}

		int I = IsSymmetric(matrixA, rowA, colA);
		if (I == 0)
		{
			cout << " Matrix is symmetric " << endl;
		}
		else
			cout << "Matrix is not symmetric" << endl;


		myfile.close();
	}

	else {
		cerr << "Error opening file" << endl;
	}

	return 0;
}


//Part 2: (String Manipulation)


#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int mystrlen(char* str)
{
	int i = 0;
	while (*str != '\0')
	{
		i++;
		str++;
	}
	return i;
}
void Canc(char s1[], char s2[])
{
	int len1 = mystrlen(s1);
	int len2 = mystrlen(s2);

	for (int i = 0; i < len2; i++)
	{
		s1[len1 + i] = s2[i];
	}

	s1[len1 + len2] = '\0';

	//cout << "Concatenated String: " << s1 << endl;

	//delete[] result; // Free the dynamically allocated memory
}//

void get_line(char* token, int MAX_SIZE)
{
	cin.getline(token, MAX_SIZE);
	if (cin.fail()) {
		cin.clear(); // Clear the error flag
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the input buffer
	}
	else {
		token[MAX_SIZE - 1] = '\0'; // Ensure null-termination
	}
}

int CompareString(const char* str1, const char* str2)
{ 
	int i = 0;
	while (str1[i] != '\0' && str2[i] != '\0') {
		if (str1[i] < str2[i]) {
			return -1; 
		}
		else if (str1[i] > str2[i]) { 
			return 1;
		}
		i++;
	}
	if (str1[i] == '\0' && str2[i] == '\0')
	{
		return 0;
	}
	else if (str1[i] == '\0') {
		return -1;
	} 
else { return 1; } }

void copy(char* des, char* str, int n)
{
	int i = 0;
	while (i < n && str[i] != '\0')
	{
		des[i] = str[i];
		i++;
	}
	des[i] = '\0';
}

int countRow(char* str)
{
	int i = 0;
	int row = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			row++;

		}
		i++;
	}

	return row+1;
}
bool chara(char* str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == 'a' || str[i] == 'z' || str[i] == 'A' || str[i] == 'Z')
		{
			return true;
		}
	}
	return false;
}
char** Token(char* str)
{
	int row = countRow(str);
	char** token = new char* [row];
	for (int i = 0; i < row; i++)
	{
		token[i] = new char[20];
	}
	int index = 0;
	int j = 0;
	char* str2 = str;
	int n = mystrlen(str);
	
		for (int i = 0; i<(n+1); i++)
		{
			if (str2[i]!=' ')
			{
				token[index][j] = str2[i];
				j++;
			}
			else
			{
				*(*(token+index)+j) = '\0';
				index++;
				j = 0;
				

			}
			*(*(token+index)+j) = '\0';
		}

	return token;
}
void ReverseWord(char* word, int start, int end) {
	while (start < end) {
		char temp = word[start];
		word[start] = word[end];
		word[end] = temp;
		start++;
		end--;
	}
}
char* ReverseWordsInString(char* str1) {
	char* str = str1;
	int length = mystrlen(str);
	int start = 0;

	// Reverse individual words while maintaining spaces
	for (int end = 0; end <= length; end++) {
		if (str[end] == ' ' || str[end] == '\0') {
			// Reverse the word from start to end (exclusive)
			ReverseWord(str, start, end - 1);
			start = end + 1;
		}
	}

	// Reverse the entire string
	ReverseWord(str, 0, length - 1);
	return str;
}
bool mycopy(char dest[], const char* src, size_t n) {
	if (dest == nullptr || src == nullptr || n == 0) {
		return false; // Handle invalid arguments
	}

	size_t len = std::strlen(src);
	size_t to_copy = std::min(len, n - 1); // Prevent buffer overflow

	for (size_t i = 0; i < to_copy; ++i) {
		dest[i] = src[i];
	}
	dest[to_copy] = '\0'; // Ensure null termination

	return true; // Indicate success
}
void CopyString(char* dest, const char* src)
{ 
	int i = 0;
     while (src[i] != '\0'){
		 dest[i] = src[i];
            i++; 
	 }
        dest[i] = '\0'; 
}

void SortNames(char char_arrays[][81], int numstudent) {
	for (int i = 0; i < numstudent - 1; i++) {
		for (int j = 0; j < numstudent - 1 - i; j++) {
			if (CompareString(char_arrays[j], char_arrays[j + 1]) > 0) {
				char temp[81];
				CopyString(temp, char_arrays[j]);
				CopyString(char_arrays[j], char_arrays[j + 1]);
				CopyString(char_arrays[j + 1], temp);
			}
		}
	}
}
int main()
{
	ifstream myfile;
	myfile.open("Data.txt", ios::in);
	if (myfile.is_open())
	{
		char s1[100], s2[100];
		int MAX_LEN = 100;
		int numstudent=80;
		myfile.getline(s1, MAX_LEN);
		
		myfile.getline(s2, MAX_LEN);
		//myfile >> numstudent;
		Canc(s1, s2);
		cout << "String 1: " << s1 << endl;
		cout << "String 2: " << s2 << endl;
		
		string names[80]; // Array to store names (up to 80 characters each)
		char char_arrays[80][81]; // Array of char arrays to hold individual names with null terminator

		// Read each name from the file and store it in the respective arrays
		for (int i = 0; i < numstudent; i++) {
			myfile >> names[i];
			// Copy the name to the corresponding character array, ensuring it fits
			mycopy(char_arrays[i], names[i].c_str(), 80);
			char_arrays[i][80] = '\0'; // Explicitly add null terminator in case name is shorter than 80 characters
		}
		
		
		char* token=s1;
		int end = mystrlen(token);
		
		char* in = token;
		int row = countRow(token);
		char** st = Token(token);
		cout << "After tokenization" << endl;
		for (int i = 0; i < row; i++)
		{
			cout << st[i] << endl;
		}

		cout << "Inverse array" << endl;

		// Output the result
		cout << "Reversed Words: " << in << std::endl;

		ReverseWordsInString(in);

		char** sst = Token(in);

		cout << "Resversed tokenized " << endl;;
		for (int i = 0; i < row; i++)
		{
			cout << sst[i] << endl;
		}
		cout << endl;
		cout << "Unsorted Names" << endl;
		for (int i = 0; i < numstudent; i++) {
			cout << names[i] << endl;
		}
		SortNames(char_arrays, numstudent);
		cout << "Sorted Names" << endl;
		// Print the sorted names (optional)
		for (int i = 0; i < numstudent; i++) {
			std::cout << char_arrays[i] << std::endl;
		}
		for (int i = 0; i < row; i++)
		{
			delete[] st[i];
			delete[] sst[i];
		}
		delete[] sst;
		delete[] st;
		delete[] char_arrays;
		myfile.close();
	}
	return 0;
}