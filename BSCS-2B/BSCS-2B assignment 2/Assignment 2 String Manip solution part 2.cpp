#include <iostream>
#include <fstream>
using namespace std;

void StringConcatenate(char* string1, char* string2)
{
	int end = 0, i = 0;
	for (; string1[end] != '\0'; end++);
	string1[end] = ' ';
	end++;
	for (; string2[i] != '\0'; i++, end++)
	{
		string1[end] = string2[i];
	}
	string1[end] = '\0';
}

char** StringTokens(char* string)
{
	int words = 1, length = 0;
	for (; string[length] != '\0'; length++)
		if (string[length] == ' ')
			words++;	

	char** tokens = new char*[words];
	for (int i = 0; i < words; i++)
		tokens[i] = new char[80];

	int i = 0, j = 0, counter = 0;
	for (i = 0; i <= length; i++)
	{
		if (string[i] == ' ' || string[i] == '\0')
		{
			tokens[counter][j] = '\0';
			j = 0;
			counter++;
		}
		else
		{
			tokens[counter][j] = string[i];
			j++;
		}
	}

	return tokens;
}

char** InverseStringTokens(char* string)
{
	char** reverse = StringTokens(string);
	char* temp;
	int words = 1;
	for (int i = 0; string[i] != '\0'; i++)
		if (string[i] == ' ')
			words++;

	for (int i = 0; i < words / 2; i++)
	{
		temp = reverse[i];
		reverse[i] = reverse[words - i - 1];
		reverse[words - i - 1] = temp;
	}
	return reverse;
}

char* ReverseSentence(char* string)
{
	char** tokens = InverseStringTokens(string);
	char* reverse =  tokens[0];
	int words = 1;
	for (int i = 0; string[i] != '\0'; i++)
		if (string[i] == ' ')
			words++;

	for (int i = 1; i < words; i++)
		StringConcatenate(reverse, tokens[i]);

	return reverse;
}

int CompareString(char* str1, char* str2)
{
	int size1 = 0, size2 = 0;
	for (; str1[size1] != '\0'; size1++);
	for (; str2[size2] != '\0'; size2++);
	for (int i = 0; ;i++)
	{
		if (str1[i] == '\0' || str2[i] == '\0')
			break;
		if (str1[i] > str2[i])
			return 1;
		else if (str1[i] < str2[i])
			return -1;
	}
	if (size1 > size2)
		return 1;
	else if (size2 > size1)
		return -1;
	else if (size1 == size2)
		return 0;
}

void DisplayStringList(char** list, int students)
{
	for (int i = 0; i < students; i++)
		cout << list[i] << endl;
}

int main()
{
	ifstream file("Data.txt");
	if (file.is_open())
	{
		char* temp = new char[80];
		char* temp2 = new char[80];
		file.getline(temp, 80);
		char* string1 = temp;
		file.getline(temp2, 80);
		char* string2 = temp2;
		temp = 0, temp2 = 0;

		cout << "--------------------------------------------------------------\n";
		cout << "Before string concatenate:\n";
		cout << "String1: " << string1 << endl;
		cout << "String2: " << string2 << endl;
		StringConcatenate(string1, string2);
		cout << "After string concatenate:\n";
		cout << "String1: " << string1 << endl;
		cout << "String2: " << string2 << endl << endl;;
		cout << "--------------------------------------------------------------\n";
		cout << "Tokens of String 1 are as follows: \n";
		char** tokens = StringTokens(string1);
		int words = 1;
		for (int i = 0; string1[i] != '\0'; i++)
			if (string1[i] == ' ')
				words++;
		for (int i = 0; i < words; i++)
			cout << tokens[i] << endl;
		cout << "--------------------------------------------------------------\n";
		cout << "Tokens of String 1 in reverse order are as follows: \n";
		char** reverseTokens = InverseStringTokens(string1);
		for (int i = 0; i < words; i++)
			cout << reverseTokens[i] << endl;
		cout << "--------------------------------------------------------------\n";
		cout << "String 1 sentence in reverse order is: \n";
		char* reverseSentence = ReverseSentence(string1);
		cout << reverseSentence << endl;
		cout << "--------------------------------------------------------------\n";
		cout << "Comparing strings: \n";
		int comparison = CompareString(string1, string2);
		if (comparison == -1)
			cout << "String 2 is greater than String 1.\n";
		else if (comparison == 1)
			cout << "String 1 is greater than String 2.\n";
		else 
			cout << "String 1 is equal to String 2.\n";
		cout << "--------------------------------------------------------------\n";
		int students;
		file >> students;
		file.ignore();
		char** list = new char*[students];
		for (int i = 0; i < students; i++)
		{
			list[i] = new char[80];
			file.getline(list[i], 80);
		}
		cout << "Unsorted List of Students: \n";
		DisplayStringList(list, students);
		cout << endl;
		cout << "--------------------------------------------------------------\n";
		cout << "Sorted List of Students: \n";


		//Bubble Sort of students:
		int i, j;
		temp = new char[80];
		bool swapped;
		for (i = 0; i < students - 1; i++) {
			swapped = false;
			for (j = 0; j < students - i - 1; j++)
				if (CompareString(list[j],list[j+1]) == 1) {
					temp = list[j];
					list[j] = list[j + 1];
					list[j + 1] = temp;
					swapped = true;
				}
			if (swapped == false)
				break;
		}
		DisplayStringList(list, students);

		for (int i = 0; i < students; i++)
			delete[] list[i];
		delete[] string1, string2, temp, temp2, tokens, list;
		file.close();
	}
	else
		cout << "Unable to open file.";
}