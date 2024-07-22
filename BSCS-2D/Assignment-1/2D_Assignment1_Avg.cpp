#include <iostream>
#include <cstdlib>
//#include <fstream>
//#include <iostream>
using namespace std;


int strlen(char* str) {
    int i = 0;
    while (*(str + i) != '\0') {
        i++;
    }
    return i;
}
int compareSize(const char* str1, const char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int len = (len1 > len2) ? len2 : len1;
    for (int i = 0; i < len; i++) {
        if (str1[i] < str2[i]) {
            return -1;
        }
        else if (str1[i] > str2[i]) {
            return 1;
        }
    }
    if (len1 > len2) {
        return 1;
    }
    else if (len1 < len2) {
        return -1;
    }
    else {
        return 0;
    }
}
void CopyChar(char* dest, const char* src, int size) {
    for (int i = 0; i < size; i++) {
        if (src[i] == '\0') {
            break;
        }
        dest[i] = src[i];
    }
    dest[size - 1] = '\0';
}

void get_word(char* word, int size) {
    cin.getline(word, size);
    for (int i = 0; i < size; i++) {
        if (word[i] == '\n') {
            word[i] = '\0';
            break;
        }
    }
}
int searchSame(const char* str1, const char* str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        int c1 = tolower(*str1);
        int c2 = tolower(*str2);
        if (c1 < c2) {
            return -1;
        }
        else if (c1 > c2) {
            return 1;
        }
        str1++;
        str2++;
    }
    if (*str1 == '\0' && *str2 != '\0') {
        return -1;
    }
    else if (*str1 != '\0' && *str2 == '\0') {
        return 1;
    }
    else {
        return 0;
    }
}

int Checkword(char** data_dictionary, const char* word, int num_words) {
    for (int i = 0; i < num_words; i++) {
        if (searchSame(data_dictionary[i], word) == 0) {
            return i;
        }
    }
    return -1;
}


int StoreSynonym(char*** synonyms, int i, int num_synonyms, const int S_size) {

    synonyms[i] = new char* [num_synonyms + 1];
    for (int j = 0; j < num_synonyms + 1; j++) {
        synonyms[i][j] = new char[S_size];
        CopyChar(synonyms[i][j], "0", S_size);
    }
    return num_synonyms;
}

// Function to free the memory for the synonyms of a word
void DeallocateSynonym(char*** synonyms, int i, int num_synonyms) {
    for (int j = 0; j < num_synonyms + 1; j++) {
        if (synonyms[i][j] != NULL) {
            delete[] synonyms[i][j];
        }
    }
    delete[] synonyms[i];
}


void get_line(char* line, int size) {
    cin.getline(line, size);
    for (int i = 0; i < size; i++) {
        if (line[i] == '\n') {
            line[i] = '\0';
            break;
        }
    }
}

const char* searchCharc(const char* str, int c) {
    while (*str != '\0') {
        if (*str == c) {
            return str;
        }
        str++;
    }
    return NULL;
}
char* CheckInput(char* str, const char* delim) {
    static char* input = NULL;
    if (str != NULL) {
        input = str;
    }
    if (input == NULL) {
        return NULL;
    }
    char* token = input;
    while (*input != '\0') {
        if (searchCharc(delim, *input) == NULL) {
            break;
        }
        input++;
    }
    if (*input == '\0') {
        return NULL;
    }
    char* start = input;
    while (*input != '\0') {
        if (searchCharc(delim, *input) != NULL) {
            *input = '\0';
            input++;
            break;
        }
        input++;
    }
    return start;
}
char* tokenize(char* input, char** data_dictionary, int& num_words, const int MAX_WORDS) {
    char* token = CheckInput(input, " .!?");
    while (token != NULL) {
        if (num_words == MAX_WORDS) {
            break;
        }
        int index = Checkword(data_dictionary, token, num_words);
        if (index == -1) {
            data_dictionary[num_words] = new char[strlen(token) + 1];
            CopyChar(data_dictionary[num_words], token, strlen(token) + 1);
            num_words++;
        }
        token = CheckInput(NULL, " .!?");
    }
    return token;
}
char*** printSynonyms(char*** synonyms, int size) {
    if (size == 0) {
        cout << "No synonyms found.\n";
        return 0;
    }
    cout << "Synonyms:\n";
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". " << ***synonyms << "\n";
    }
    return synonyms;
}
bool areStringsEqual(const char* str1, const char* str2, int length) {
    for (int i = 0; i < length; i++) {
        if (tolower(static_cast<unsigned char>(str1[i])) != tolower(static_cast<unsigned char>(str2[i]))) {
            return false;
        }
    }
    return true;
}

// Search function
void search(const char* input1, const char* input2, int numWords1, int numWords2) {
    int i = 0, j = 0;
    while (i < numWords1 && j < numWords2) {
        if (areStringsEqual(input1 + i, input2 + j, strlen(input1 + i))) {
            cout << "Match found: " << input1[i] << endl;
            i++;
            j++;
        }
        else if (strlen(input1 + i) < strlen(input2 + j)) {
            i++;
        }
        else {
            j++;
        }
    }
}

void Copy(char* dest, const char* src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}
void storeNonSimilarWords(const char* input1, const char* input2, int numWords1, int numWords2, char notSimilarWords[][100], int& numNotSimilarWords) {
    int i = 0, j = 0, k = 0;
    for (; i < numWords1 && j < numWords2; ) {
        if (areStringsEqual((input1 + i), (input2 + j), strlen((input1 + i)))) {
            i++;
            j++;
        }
        else if (i < numWords1 && j < numWords2) {
            if (!k) {
                notSimilarWords[k][0] = '\0'; // initialize the first word in the array
            }
            Copy(notSimilarWords[k], areStringsEqual((input1 + i), (input2 + j), strlen((input1 + i))) ? (input2 + j) : (input1 + i));
            k++;
            i++;
            j++;
        }
        else if (i < numWords1) {
            if (!k) {
                notSimilarWords[k][0] = '\0'; // initialize the first word in the array
            }
            Copy(notSimilarWords[k], (input1 + i));
            k++;
            i++;
        }
        else if (j < numWords2) {
            if (!k) {
                notSimilarWords[k][0] = '\0'; // initialize the first word in the array
            }
            Copy(notSimilarWords[k], (input2 + j));
            k++;
            j++;
        }
    }
    numNotSimilarWords = k;
    for (int i = 0; i < numNotSimilarWords; i++) {
        cout << notSimilarWords[i] << endl;
    }
}

//void getSynonyms(const string& word, char*** synonyms, int& S_size, int& num_synonyms) {
//    ifstream file("synonyms.txt");
//    if (!file.is_open()) {
//        cout << "Error opening synonyms file.\n";
//        return;
//    }
//    string line;
//    int synonymListSize = 0;
//    char** synonymList = nullptr;
//    while (getline(file, line)) {
//        size_t pos = line.find(':');
//        if (pos != string::npos) {
//            string currentWord = line.substr(0, pos);
//            if (currentWord == word) {
//                string synonymsStr = line.substr(pos + 1);
//                istringstream iss(synonymsStr);
//                string synonym;
//                while (getline(iss, synonym, ',')) {
//                    synonymListSize++;
//                    synonymList = (char**)realloc(synonymList, synonymListSize * sizeof(char*));
//                    synonymList[synonymListSize - 1] = new char[synonym.size() + 1];
//                    strcpy(synonymList[synonymListSize - 1], synonym.c_str());
//                    S_size += synonym.size() + 1;
//                }
//                break;
//            }
//        }
//    }
//    file.close();
//    num_synonyms = synonymListSize;
//    *synonyms = synonymList;
//}
void searchAndReplace(char* input, char* input2, int num_words, int numWords) {
    for (int i = 0; i < num_words; i++) {
        bool found = false;
        for (int j = 0; j < numWords; j++) {
            if (compareSize((input + i), (input + i)) == 0) {
                found = true;
                cout << "Word found: " << input[i] << "\n";
                char choice;
                cout << "Do you want to replace this word with its synonym? (Y/N): ";
                cin >> choice;
                if (choice == 'Y' || choice == 'y') {
                    char** synonyms = new char* [num_words];
                    int S_size = 0;
                    int num_synonyms;
                    char word = 0;
                   // getSynonyms(word,&synonyms, S_size, num_synonyms);
                    if (S_size > 0) {
                        cout << "Choose a synonym to replace the word with: \n";
                        for (int k = 0; k < S_size; k++) {
                            cout << k + 1 << ". " << synonyms[k] << "\n";
                        }
                        int synonymChoice;
                        cin >> synonymChoice;
                        if (synonymChoice >= 1 && synonymChoice <= S_size) {
                            CopyChar(input2 + strlen((input + i)), synonyms[synonymChoice - 1], strlen(synonyms[synonymChoice - 1]) + 1);
                            cout << "Updated paragraph 2: " << input2 << "\n";
                        }
                        else {
                            cout << "Invalid choice. Word not replaced.\n";
                        }
                    }
                    else {
                        cout << "No synonyms found for this word.\n";
                    }
                }
                break;
            }
        }
        if (!found) {
            cout << "Word not found: " << input[i] << "\n";
        }
    }
}
int main() {

    const int MAX_CHARS = 3000;
    const int MAX_WORDS = 100;
    const int S_size = 100;
    char input[MAX_CHARS];
    cout << "Enter a paragraph (max 3000 characters): ";
    get_line(input, MAX_CHARS);

    cout << "Enter a paragraph 2 (max 3000 characters): ";
    char input2[MAX_CHARS];
    get_line(input2, MAX_CHARS);


    // Tokenize the input and store unique words in the data dictionary
    char** dataDictionary = new char* [MAX_WORDS];
    int num_words = 0;
    char* token = tokenize(input, dataDictionary, num_words, MAX_WORDS);

    // Print the updated data dictionary
    //   cout << "Data Dictionary:\n";
    //     for (int i = 0; i < numWords; i++) {
    //         cout << i + 1 << ". " << dataDictionary[i] << "\n";
    //     }
    cout << "Unique words" << endl;
    for (int i = 0; i < num_words; i++) {
        cout << dataDictionary[i] << "\n";
    }
    cout << "\nNumber of unique words for para1: " << num_words << "\n";

    char** data_dictionary = new char* [MAX_WORDS];
    int numWords = 0;

    tokenize(input2, data_dictionary, numWords, MAX_WORDS);
    cout << "Unique words" << endl;
    for (int i = 0; i < numWords; i++) {
        cout << data_dictionary[i] << "\n";
    }
    cout << "\nNumber of unique words for para2: " << numWords << "\n";

    // Create a 3D character array to store the synonyms
    char*** synonyms = new char** [num_words];
    for (int i = 0; i < num_words; i++) {
        synonyms[i] = NULL;
    }

    // Iterate for each word in the data dictionary
    for (int i = 0; i < num_words; i++) {
        cout << "Do you want to store synonyms for the word \"" << dataDictionary[i] << "\"? (y/n) ";
        char temp[100];
        get_word(temp, 100);
        if (compareSize(temp, "y") == 0) {
            cout << "Enter the number of synonyms you want to store: ";
            get_word(temp, 100);
            int numsynonyms = atoi(temp);
            //int size = numsynonyms;
            cout << numsynonyms << endl;
            StoreSynonym(synonyms, i, numsynonyms, S_size);
            for (int j = 0; j < numsynonyms; j++) {
                cout << "Enter synonym " << j + 1 << ": ";
                get_word(temp, 100);
                int len = strlen(temp) + 1;
                synonyms[i][j] = new char[len];
                CopyChar(synonyms[i][j], temp, len);

            }
           
        }

    }
    //printSynonyms(synonyms, S_size);
   // char*** ss = printSynonyms(synonyms, S_size);

    //string word = "example";
  //  getSynonyms(word, &synonyms, S_size, num_synonyms);
   
    char(*notSimilarWords)[100]; // assuming this is your notSimilarWords array
    int numNotSimilarWords = 0; // assuming this is your numNotSimilarWords variable

    //storeNonSimilarWords(input, input2, num_words, numWords, notSimilarWords, numNotSimilarWords);
    // print out the notSimilarWords array
   /* for (int i = 0; i < numNotSimilarWords; i++) {
        cout << notSimilarWords[i] << endl;
    }*/
    search(input, input2, num_words, numWords);
    searchAndReplace(input, input2, num_words, numWords);
    // Free the memory for the synonyms of each word
    for (int i = 0; i < num_words; i++) {
        DeallocateSynonym(synonyms, i, 100);
        delete[] dataDictionary[i];
    }
    delete[] dataDictionary;
    delete[] synonyms;

    return 0;
}