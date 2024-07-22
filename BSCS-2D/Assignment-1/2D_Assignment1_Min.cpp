#include<iostream>
#include<string>
using namespace std;
int main()
{
	char *arr=new char a[3000];
	cout << "\nEnter paragraph:\n";
	cin.getline(arr, 3000);
	cout <<"\n\n\nOriginal Paragraph:\n"<< arr << endl;

    char brr[20];     
    int i = 0, j = 0;
    cout << "\n\n\n SEPERATED WORDS:\n\n";
    while (arr[i] != NULL)  
    {
        brr[j] = arr[i];
        if (brr[j] == ' ')
        {
            brr[j + 1] = '\0';
            cout << S << endl;   
            j = -1;

        }
        if (brr[j] == '.')
        {
            brr[j] = ' ';
            cout << S << endl;
            j = -1;

        }
        if (brr[j] == '?')
        {
            brr[j] = ' ';
            cout << S << endl;
            j = -1;

        }
        i++;
        j++;
    }
    
}