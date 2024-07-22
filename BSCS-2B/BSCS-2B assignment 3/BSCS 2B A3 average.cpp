#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class EvalReport {
private:
    string rollNo;
    string name;
    int quizzes[4];
    int assignments[4];
    int total;

public:
    // Constructor
    EvalReport() {
        total = 0;
        rollNo = "";
        name = "";
        for (int i = 0; i < 4; i++) {
            quizzes[i] = 0;
        }
        for (int i = 0; i < 4; i++) {
            assignments[i] = 0;
        }
    }

    // Member functions
    void SetRollNo(const string& roll) {
        rollNo = roll;
    }

    void SetName(const string& n) {
        name = n;
    }
    int GetQuizMarks(int idx) {
        return quizzes[idx];
    }
    void SetQuizMarks(int index, int mark) {
        quizzes[index] = mark;
    }
    int GetAssignmentMarks(int idx) {
        return assignments[idx];
    }
    void SetAssignmentMarks(int index, int mark) {
        assignments[index] = mark;
    }

    void CalculateTotal() {
        total = 0;
        for (int i = 0; i < 4; ++i) {
            total += quizzes[i] + assignments[i];
        }
    }

    string GetRollNo() const {
        return rollNo;
    }

    string GetName() const {
        return name;
    }

    int GetTotal() const {
        return total;
    }

    void PrintDetailView() const {
        cout << "Student Information:" << endl;
        cout << "Roll No:\t" << rollNo << endl;
        cout << "Name:\t\t" << name << endl;
        cout << "Quizzes Marks:" << endl;
        for (int i = 0; i < 4; ++i) {
            cout << "\tQ" << i + 1 << ":\t" << quizzes[i] << endl;
        }
        cout << "Assignment Marks:" << endl;
        for (int i = 0; i < 4; ++i) {
            cout << "\tA" << i + 1 << ":\t" << assignments[i] << endl;
        }
        cout << "Total:\t\t" << total << endl; // Assuming total marks are out of 300
    }
};

class EvaluationSystem {
private:
    EvalReport* studentData;
    int totalStudents;
    int quizzesTotal[4];
    int assignmentsTotal[4];

public:
    // Constructor
    EvaluationSystem() {
        studentData = nullptr;
        totalStudents = 0;
        for (int i = 0; i < 4; i++) {
            quizzesTotal[i] = 0;
        }
        for (int i = 0; i < 4; i++) {
            assignmentsTotal[i] = 0;
        }
    }

    // Destructor
    ~EvaluationSystem() {
        delete[] studentData;
    }

    // Member functions
    void ReadDataFromFile(const char* filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file!" << endl;
            return;
        }

        file >> totalStudents;
        studentData = new EvalReport[totalStudents];

        int totalQuizzes, totalAssignments;
        file >> totalQuizzes >> totalAssignments;

        for (int i = 0; i < totalQuizzes; i++) {
            file >> quizzesTotal[i];
        }

        for (int i = 0; i < totalAssignments; i++) {
            file >> assignmentsTotal[i];
        }
        int count = 0;
        for (int i = 0; i < totalStudents; i++) {
            string name, rollNo;
            file >> name >> rollNo;
            studentData[i].SetName(name);
            studentData[i].SetRollNo(rollNo);
            for (int j = 0; j < totalQuizzes; j++) {
                int mark;
                file >> mark;
                studentData[i].SetQuizMarks(j, mark);
            }
            for (int j = 0; j < totalAssignments; j++) {
                int mark;
                file >> mark;
                studentData[i].SetAssignmentMarks(j, mark);
            }
            studentData[i].CalculateTotal();
        }

        file.close();
    }

    void PrintAll() const {
        cout << "Roll No.\tName\t\t\tQ1\tQ2\tQ3\tQ4\tA1\tA2\tA3\tA4\tTotal" << endl;
        for (int i = 0; i < totalStudents; ++i) {
            cout << studentData[i].GetRollNo() << "\t" << studentData[i].GetName() << "\t\t";
            for (int j = 0; j < 4; ++j) {
                cout << studentData[i].GetQuizMarks(j) << "\t";
            }
            for (int j = 0; j < 4; ++j) {
                cout << studentData[i].GetAssignmentMarks(j) << "\t";
            }
            cout << studentData[i].GetTotal() << endl;
        }
    }

    void SearchStudentsByKeyWord(const char* keyword) const {
        cout << "Roll No.\tName\t\tQ1\tQ2\tQ3\tQ4\tA1\tA2\tA3\tA4\tTotal" << endl;
        for (int i = 0; i < totalStudents; i++) {
            if (studentData[i].GetName().find(keyword) != string::npos ||
                studentData[i].GetRollNo().find(keyword) != string::npos) {
                cout << studentData[i].GetRollNo() << "\t" << studentData[i].GetName() << "\t\t";
                for (int j = 0; j < 4; j++) {
                    cout << studentData[i].GetQuizMarks(j) << "\t";
                }
                for (int j = 0; j < 4; j++) {
                    cout << studentData[i].GetAssignmentMarks(j) << "\t";
                }
                cout << studentData[i].GetTotal() << endl;
            }
        }
    }

    void SortListByTotal() {
        for (int i = 0; i < totalStudents - 1; i++) {
            for (int j = 0; j < totalStudents - i - 1; j++) {
                if (studentData[j].GetTotal() < studentData[j + 1].GetTotal()) {
                    EvalReport temp = studentData[j];
                    studentData[j] = studentData[j + 1];
                    studentData[j + 1] = temp;
                }
            }
        }
    }

    void PrintDetailView(const char* rollNo) const {
        for (int i = 0; i < totalStudents; i++) {
            if (studentData[i].GetRollNo() == rollNo) {
                studentData[i].PrintDetailView();
                return;
            }
        }
        cout << "Student not found" << endl;
    }
};

int main() {
    EvaluationSystem evalSystem;
    evalSystem.ReadDataFromFile("gradesheet.txt");

    cout << "All students:" << endl;
    evalSystem.PrintAll();

    cout << "Search results:" << endl;
    evalSystem.SearchStudentsByKeyWord("43");

    evalSystem.SortListByTotal();
    cout << "Sorted List:" << endl;
    evalSystem.PrintAll();

    cout <<endl<< "\t\t\tStudent Detail View:" << endl;
    evalSystem.PrintDetailView("23L-0951");

    return 0;
}
