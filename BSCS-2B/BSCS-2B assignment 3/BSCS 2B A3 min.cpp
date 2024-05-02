

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

const int NUM_STUDENTS = 36;
const int NUM_QUIZZES = 4;
const int NUM_ASSIGNMENTS = 4;

class EvalReport {
public:
    string rollNo;
    string name;
    int quizzes[NUM_QUIZZES];
    int assignments[NUM_ASSIGNMENTS];
    int total;

    EvalReport() {
        rollNo = "";
        name = "";
        total = 0;
        for (int i = 0; i < NUM_QUIZZES; ++i)
            quizzes[i] = 0;
        for (int i = 0; i < NUM_ASSIGNMENTS; ++i)
            assignments[i] = 0;
    }

    void printDetailView() {
        cout << "printDetailView:" << endl;
        cout << "Roll No:                    " << rollNo << endl;
        cout << "Name:                       " << name << endl;
        cout << "Quizzes Marks:        " << endl;
        for (int i = 0; i < NUM_QUIZZES; ++i)
            cout << "                                   Q" << i + 1 << ":          " << quizzes[i] << "/10" << endl;
        cout << "Assignment Marks:" << endl;
        for (int i = 0; i < NUM_ASSIGNMENTS; ++i)
            cout << "                                   A" << i + 1 << ":            " << assignments[i] << "/55" << endl;
        cout << "Total:                                            " << total << "/300" << endl;
    }
};

EvalReport students[NUM_STUDENTS];

void ReadDataFromFile() {
    ifstream file("students.txt");
    if (!file) {
        cerr << "Unable to open file." << endl;
        return;
    }

    for (int i = 0; i < NUM_STUDENTS; ++i) {
        file >> students[i].rollNo >> students[i].name;
        for (int j = 0; j < NUM_QUIZZES; ++j)
            file >> students[i].quizzes[j];
        for (int j = 0; j < NUM_ASSIGNMENTS; ++j)
            file >> students[i].assignments[j];
    }

    file.close();
}

void UpdateStatistics() {
    
    for (int i = 0; i < NUM_STUDENTS; ++i) {
        students[i].total = 0;
        for (int j = 0; j < NUM_QUIZZES; ++j)
            students[i].total += students[i].quizzes[j];
        for (int j = 0; j < NUM_ASSIGNMENTS; ++j)
            students[i].total += students[i].assignments[j];
    }
}

void PrintAll() {
    cout << "RollNo               Name                  q1         q2         q3          q4         q1          a2         a3           a4       Total" << endl;
    for (int i = 0; i < NUM_STUDENTS; ++i) {
        cout << setw(10) << students[i].rollNo << "     " << setw(20) << students[i].name << "     ";
        for (int j = 0; j < NUM_QUIZZES; ++j)
            cout << setw(4) << students[i].quizzes[j] << "     ";
        for (int j = 0; j < NUM_ASSIGNMENTS; ++j)
            cout << setw(4) << students[i].assignments[j] << "     ";
        cout << setw(5) << students[i].total << endl;
    }
}

EvalReport** SearchStudentsByKeyWord(const char* keyword) {
    EvalReport** result = new EvalReport * [NUM_STUDENTS];
    int count = 0;

    for (int i = 0; i < NUM_STUDENTS; ++i) {
        if (strstr(students[i].rollNo.c_str(), keyword) || strstr(students[i].name.c_str(), keyword)) {
            result[count] = &students[i];
            count++;
        }
    }

    EvalReport** resizedResult = new EvalReport * [count];
    for (int i = 0; i < count; ++i)
        resizedResult[i] = result[i];

    delete[] result;
    return resizedResult;
}

void PrintAll(EvalReport** list) {
    cout << "RollNo               Name                  q1         q2         q3          q4         q1          a2         a3           a4       Total" << endl;
    for (int i = 0; i < NUM_STUDENTS; ++i) {
        cout << setw(10) << list[i]->rollNo << "     " << setw(20) << list[i]->name << "     ";
        for (int j = 0; j < NUM_QUIZZES; ++j)
            cout << setw(4) << list[i]->quizzes[j] << "     ";
        for (int j = 0; j < NUM_ASSIGNMENTS; ++j)
            cout << setw(4) << list[i]->assignments[j] << "     ";
        cout << setw(5) << list[i]->total << endl;
    }
}

void SortListByTotal() {
    for (int i = 0; i < NUM_STUDENTS - 1; ++i) {
        for (int j = i + 1; j < NUM_STUDENTS; ++j) {
            if (students[i].total < students[j].total) {
                EvalReport temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

void PrintDetailView(const char* rollNo) {
    for (int i = 0; i < NUM_STUDENTS; ++i) {
        if (students[i].rollNo == rollNo) {
            students[i].printDetailView();
            return;
        }
    }
    cout << "Student not found" << endl;
}

int main() {
    ReadDataFromFile();
    UpdateStatistics();
    cout << "PrintAll:" << endl;
    PrintAll();
    const char* keyword = "43";
    EvalReport** filteredList = SearchStudentsByKeyWord(keyword);
    cout << "filteredList" << endl;
    PrintAll(filteredList);
    delete[] filteredList;
    SortListByTotal();
    cout << "SortListByTotal" << endl;
    PrintAll();
    cout << "Student Details" << endl;
    PrintDetailView("15L-4023");


}


