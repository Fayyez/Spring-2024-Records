#include <iostream>
#include <cstring>
#include <cctype>
#include <limits>
using namespace std;


void print(char *arr)
{
    for(int k = 0; arr[k] != '\0'; k++)
    {
        cout << arr[k];
    }
    cout << endl;
}

bool check_for_repitition(char* current_word, char* unique1d)      // TASK 1
{

    while (*unique1d != '\0') {
        const char* u = unique1d;
        const char* cw = current_word;

        // Compare characters in current_word and unique1d
        while (*u != ' ' && *u != '\0' && *u == *cw) {
            u++;
            cw++;
        }

        // If we reached the end of both strings, it's a repetition
        if (*u == ' ' && (*cw == '\0' || *cw == ' ')) {
            return true;
        }

        // Skip to the next word in unique1d
        while (*unique1d != ' ' && *unique1d != '\0') {
            unique1d++;
        }

        // Skip consecutive spaces in unique1d
        while (*unique1d == ' ') {
            unique1d++;
        }
    }

    return false;

}


char* create_unique_array(char* arr)                    //TASK 1
{
    char *unique1d = new char [500];
    char *current_word = nullptr;
    int x = 0;                              //for index of unique1d
    int prev1 = 0;
    int curr = 0;
    
    int wordcounter = 0;

    for(int i = 0; i <= strlen(arr) ; i++)
    {
        if ( (arr[i] != '\0' && !isalpha(arr[i]) && isalpha(arr[i+1])) || (arr[i] == '\0') )  
        {
            wordcounter++;
            
                        //extracting each word
            
            current_word = new char [100];
            curr = 0;
            while(prev1 != i)
            {
                if (isalpha(arr[prev1]))
                {
                    current_word[curr] = tolower(arr[prev1]);
                    curr++; 
                }
                prev1++;
            }
            current_word[curr] = '\0';         
            prev1++;

            if(wordcounter == 1)
            {
                for(int u = 0; u < curr; u++, x++)
                {
                    unique1d[x] = current_word[u];
                }
                unique1d[x] = ' ';
                x++;
            }
            else
            {
                if(check_for_repitition(current_word, unique1d) == false)
                {
                    for(int u = 0; u < curr; u++, x++)
                    {
                        unique1d[x] = current_word[u];
                    }
                    unique1d[x] = ' ';
                    x++;
                }
            }
        }

    }
    delete[] current_word;
    return unique1d;

}

char*** synonyms(char** arr, int rows)                  //TASK 2
{
    char*** synonym = new char**[500];
    for (int i = 0; i< rows; i++)
    {                                             
        cout<<"Do you want to enter synonyms of "<<arr[i]<<" (Y/N): ";
        char answer;
        cin>>answer;
        if (answer == 'y' || answer == 'Y')
        {
            cout<<endl<<"How many synonyms do you want to store against *"<<arr[i]<<"* ? ";
            int num;                                                             
            cin>>num;
            synonym[i] = new char*[num+1];
            cin.ignore();
            for (int j = 0; j < num; j++)
            {
                cout<<endl<<"Enter synonym "<<j+1<<": ";
                char temp[10];
                cin.getline(temp,10);
                int size = strlen(temp);   
                synonym[i][j] = new char[size+1];   
                for (int k = 0; k < size; k++)
                {
                    synonym[i][j][k] = temp[k];
                }
                synonym[i][j][size] = '\0';
            }
            synonym[i][num] = nullptr;
            cout<<endl<<endl<<"Synonyms entered successfully!";
        }
        else
        {
            synonym[i] = nullptr;
        }
        cout<<endl<<"\t\tProceeding to next word"<<endl;
    }
    for (int i = 0; i < rows; i++ )                                 
    {                      
        cout<<arr[i]<<": ";  
        if (synonym[i] != nullptr)
        {
            for (int j = 0; synonym[i][j] != nullptr; j++ )                 
            {
                for (int k = 0; synonym[i][j][k] != '\0'; k++)
                {
                    cout<<synonym[i][j][k];
                }
                cout<<" ";
            }
            cout<<endl;
        } 
        else
        {
            cout<<"No synonym"<<endl;
        }                                  
    }
    return synonym;
}

char** create_dictionary(char* arr, int &rows)              //TASK 1
{
    rows = 0;
    int cols = 0;
    for (int i = 0; arr[i] != '\0'; i++)
    {
        if (arr[i] == ' ')
            rows++;
    }
    char** dictionary = new char*[500];
    int temp_row = 0;
    for (int i = 0; i < strlen(arr) ; i++)
    {
        if (arr[i] != ' ')
        {
            cols++;
        }
        else
        {
            dictionary[temp_row] = new char[cols];
            dictionary[temp_row][cols] = '\0';
            int word_start = i - cols;
            for (int j = 0; j < cols; j++,word_start++)
            {
                dictionary[temp_row][j] = arr[word_start];
            }
            temp_row++;
            cols = 0;
        }
    }
    cout<<"Unique Words: "<<rows<<endl;
    for (int i = 0; i< rows; i++)
    {
        for (int j = 0; dictionary[i][j] != '\0'; j++)
        {
            cout<<dictionary[i][j];
        }
        cout<<endl;
    }
    return dictionary;
}

void input(char *arr)                       //TASK 1
{
    cout<<"Enter a paragraph(End the sentence with either '.' or '?'):-  ";
    cin.getline(arr, 3000);
}

void input2(char *arr)                      //Task 3
{
    cin.ignore();
    cout<<endl<<endl<<"Enter another paragraph:- ";
    cin.getline(arr,3000);
}

bool check_for_repetition(char* current_word, char** dictionary, int rows)  // TASK 3
{
    for (int i = 0; i < rows; i++) {
        int count = 0;
        for (int j = 0; current_word[j] != '\0' && dictionary[i][j] != '\0'; j++) {
            if (current_word[j] == dictionary[i][j]) {
                count++;
            } 
            else 
            {
                break;
            }
        }
        if (count == strlen(current_word) && dictionary[i][count] == '\0') {
            return true;    // Word already exists in the dictionary
        }
    }
    return false;   // Word is not in the dictionary
}

bool compare_words(char* word1, char* word2)        //TASK 4
{
    if (strlen(word1) == strlen(word2))
    {
        for (int i = 0; i < strlen(word1); i++)
        {
            if (word1[i] != word2[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

void replace_original_word(int starting_index, int& result_index, char* current_word, char* result, char* arr)      //TASK 4
{
    int i = starting_index;
    int size = strlen(current_word);
    int j = result_index;

    for (int k = 0; k < size; k++, i++, j++)
    {   
        result[j] = arr[i];
    }
    while (!isalpha(arr[i]) && arr[i] != '\0')
    {
        result[j] = arr[i];
        i++, j++;
    }
    result_index = j;
}

void replace_in_string(char* synonym, char* arr, char* current_word, int& result_index, char* result, int starting_index)       //TASK 4
{
    int size = strlen(synonym);
    int j = result_index;
    
    for (int i = 0; i < size; i++, j++)
    {                                         
        result[j] = synonym[i];
        
    }
    starting_index += strlen(current_word);      

    while (!isalpha(arr[starting_index]) && arr[starting_index] != '\0')        
    {
        result[j] = arr[starting_index];
        j++;
        starting_index++;
    }
    result_index = j;
}

void replace_with_synonym(char* current_word, char*arr, char*** synonym, char** dictionary, char* result, int starting_index, int& result_index)    //TASK 4 
{
    for (int i = 0; dictionary[i] != nullptr; i++)
    {
        if ( compare_words(current_word, dictionary[i]) && synonym[i] != nullptr )
        {
            cout<<"*"<<dictionary[i]<< "* found in dictionary. Do you wish to replace it(Y/N)? ";
            char answer;
            cin>>answer;
            if (answer == 'Y' || answer == 'y')
            {
                for (int j = 0; synonym[i][j] != nullptr; j++)
                {
                    cout<<j+1<<") ";
                    print(synonym[i][j]);
                }
                int syn_choice;
                cout<<"Enter your choice: ";
                cin>>syn_choice;
                cout<<endl;
                if (syn_choice >= 1 && synonym[i][syn_choice - 1] != nullptr) 
                {
                replace_in_string(synonym[i][syn_choice-1], arr, current_word, result_index, result, starting_index);
                } 
                else 
                {
                cout << "Invalid choice. \"" << current_word << "\" was not replaced." << endl;
                }
            }
            else
            {
                cout<<"\t\tProceeding to next word"<<endl;
                replace_original_word(starting_index, result_index, current_word, result, arr);
            }
        }
        else if(compare_words(current_word, dictionary[i]) && synonym[i] == nullptr)
        {
            replace_original_word(starting_index, result_index, current_word, result, arr);
        }
    }
}

char** update_dictionary(char** dictionary, char* arr, int &rows)       //TASK 3
{
    char *temp_array = new char[500];
    temp_array = 0;
    int current_word_index = 0;
    char current_word[100];

    for (int i = 0; arr[i] != '\0'; i++) {
        if (isalpha(arr[i])) {
            current_word[current_word_index++] = tolower(arr[i]);
            current_word[current_word_index] = '\0';    // Null-terminate the current word
        } 
        else 
        {
            if (current_word_index > 0 && !check_for_repetition(current_word, dictionary, rows)) 
            {
                    // Add the word to the dictionary if not already present
                dictionary[rows] = new char[current_word_index + 1];

                    // Copy characters manually
                for (int k = 0; k <= current_word_index; k++) 
                {
                    dictionary[rows][k] = current_word[k];
                }
                rows++;
            }
                // Reset current_word
            current_word_index = 0;
            current_word[0] = '\0';
        }
    }

                // Handle the last word in the input
    if (current_word_index > 0 && !check_for_repetition(current_word, dictionary, rows)) 
    {
            // Add the last word to the dictionary if not already present
        dictionary[rows] = new char[current_word_index + 1];

                    // Copy characters manually
        for (int k = 0; k <= current_word_index; k++) 
        {
            dictionary[rows][k] = current_word[k];
        }
        rows++;
    }

            // Print the updated dictionary
    for (int j = 0; j < rows; j++) {
        print(dictionary[j]);
    }

    return dictionary;
    delete[] temp_array;
}

void task4(char** dictionary, char* arr, int &rows, char***synonyms)      //TASK 4
{
    int result_index = 0;
    int current_word_index = 0;
    int starting_index = 0;
    char current_word[100];
    char* result = new char[3000];

    for (int i = 0; arr[i] != '\0'; i++) {
        if (isalpha(arr[i])) 
        {
            current_word[current_word_index++] = tolower(arr[i]);
            current_word[current_word_index] = '\0';    // Null-terminate the current word
        } 
        else 
        {
            starting_index = i - strlen(current_word);

            replace_with_synonym(current_word, arr, synonyms, dictionary, result, starting_index, result_index);
            
            // Reset current_word
            current_word_index = 0;
            current_word[0] = '\0';
        }
    }

            // Handle the last word in the input

    starting_index = strlen(arr) - strlen(current_word);

    replace_with_synonym(current_word, arr, synonyms, dictionary, result, starting_index, result_index);
    cout<<endl<<endl<<"Result: ";
    for(int k = 0; k < result_index; k++)
    {
        cout << result[k];
    }
    cout << endl;
    delete[] result;             //deallocating result
}
int main()
{
    int size = 3000;
    char * arr = new char[size];

    input(arr);         // Input for Task 1

    char* unique_arr = create_unique_array(arr);    
    
    int rows;
    delete[] arr;
    
    char** dictionary = create_dictionary(unique_arr, rows);    //Task 1
    
    delete[] unique_arr;
    
    char*** synonym = synonyms(dictionary, rows);       //  Task 2
    
    int size2 = 3000;
    char * arr2 = new char[size2];
    
    input2(arr2);               // Input for Task 3 & 4
    
    dictionary = update_dictionary(dictionary, arr2, rows);     // Task 3
    
    cout<<endl<<endl;
    
    task4(dictionary, arr2, rows, synonym);
    
    delete[] arr2;
    for (int i = 0; dictionary[i] != nullptr; i++)      //deallocating dictionary
    {
        delete[] dictionary[i];
    }
    delete[] dictionary;

    for (int i = 0; synonym[i] != nullptr; i++)         //deallocating synonym
    {
        for (int j = 0; synonym[i][j] != nullptr; j++)
        {
            delete[] synonym[i][j];
        }
        delete[] synonym[i];
    }
    delete[] synonym;

}