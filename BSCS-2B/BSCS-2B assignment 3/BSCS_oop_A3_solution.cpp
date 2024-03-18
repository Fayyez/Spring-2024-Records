#include <iostream>
#include <fstream>
using namespace std;

class Helper
{
public:
    static int StringLenght(const char* str)
    {
        int i;
        for (i = 0; str[i] != '\0'; i++);
        return i;
    }
    static void StringCopy(char*& dest, char*& src) {
        //Deep Copies src into dest.
        int size = StringLenght(src), i;
        for (i = 0; i < size; i++)
            dest[i] = src[i];
        dest[i] = '\0';
    }

    static char* GetStringFromBuffer(char* str)
    {
        char* string = new char[StringLenght(str) + 1];
        StringCopy(string, str);
        return string;
    }
    static bool matchStrings(const char* first, char* second)
    {
        int size1 = Helper::StringLenght(first);
        int size2 = Helper::StringLenght(second);
        bool result = true;
            for (int i = 0; i < size1; i++)
            {
                if (first[i] != second[i])
                {
                    result = false;
                    break;
                }
            }
        return result;
    }
};

class EvalReport
{
private:
    static int totalQuiz, totalAssignments, totalStudents;
    static int *quizMarks, *assignmentMarks;
    char rollNo[9];
    char* fName;
    char* lName;
    int* quizN;
    int* assignmentN;
    int total;

public:
    //Default Constructor
    EvalReport()
    {
        rollNo[0] = '\0';
        fName = new char;
        lName = new char;
        quizN = new int;
        assignmentN = new int;
        total = 0;
    }
    //Copy Constructor
    EvalReport(const EvalReport& rhs)
    {
        for (int i = 0; i < 9; i++)
            rollNo[i] = rhs.rollNo[i];
        fName = Helper::GetStringFromBuffer(rhs.fName);
        lName = Helper::GetStringFromBuffer(rhs.lName);
        quizN = new int[totalQuiz];
        assignmentN = new int[totalAssignments];
        for (int i = 0; i < totalQuiz; i++)
            quizN[i] = rhs.quizN[i];
        for (int i = 0; i < totalAssignments; i++)
            assignmentN[i] = rhs.assignmentN[i];

        total = rhs.total;
    }
    //Assignment Operator
    EvalReport& operator=(const EvalReport& rhs)
    {
        if (&rhs != this) // To Avoid Self-assignment
        {
            for (int i = 0; i < 9; i++)
                rollNo[i] = rhs.rollNo[i];    
            fName = Helper::GetStringFromBuffer(rhs.fName);
            lName = Helper::GetStringFromBuffer(rhs.lName);
            quizN = new int[totalQuiz];
            assignmentN = new int[totalAssignments];
            for (int i = 0; i < totalQuiz; i++)
                quizN[i] = rhs.quizN[i];
            for (int i = 0; i < totalAssignments; i++)
                assignmentN[i] = rhs.assignmentN[i];

            total = rhs.total;
        }
        return *this;
    }
    //Destructor For Non-Static Variables
    ~EvalReport()
    {
        delete[] fName, lName, quizN, assignmentN;
    }

    void ReadDataFromFile(ifstream& file)
    {
        total = 0;
        file >> rollNo;

        char temp[50];
        file >> temp;
        fName = Helper::GetStringFromBuffer(temp);

        file >> temp;
        lName = Helper::GetStringFromBuffer(temp);

        quizN = new int[totalQuiz];
        assignmentN = new int[totalAssignments];

        for (int i = 0; i < totalQuiz; i++)
        {
            file >> quizN[i];
            total = total + quizN[i];
        }
        for (int i = 0; i < totalAssignments; i++)
        {
            file >> assignmentN[i];
            total = total + assignmentN[i];
      }
    }

    void ReadStaticDataFromFile(ifstream& file)
    {
        file >> totalQuiz;
        file >> totalAssignments;
        quizMarks = new int[totalQuiz];
        assignmentMarks = new int[totalAssignments];
        for (int i = 0; i < totalQuiz; i++)
            file >> quizMarks[i];
        for (int i = 0; i < totalAssignments; i++)
            file >> assignmentMarks[i];
    }

    friend void PrintDataFromFile(EvalReport*, int);

    friend void PrintSortedData(EvalReport*);

    friend void StudentInfo(EvalReport*, const char* rollNo);

    friend void PrintStats(EvalReport*);

    friend int* maxMarks(EvalReport*);

    friend int* minMarks(EvalReport*);

    friend int* avgMarks(EvalReport*);

    void DeleteStaticData()
    {
        delete[] quizMarks, assignmentMarks;
    }

};
//Initialize Static Variables
int EvalReport::totalStudents = 0;
int EvalReport::totalQuiz = 0;
int EvalReport::totalAssignments = 0;
int* EvalReport::quizMarks = new int;
int* EvalReport::assignmentMarks = new int;
//

EvalReport* ReadDataFromFile(const char* fileName)
{
    int students = 0;

    ifstream file(fileName);
    file >> students;

    EvalReport* list = new EvalReport[students];
    list->ReadStaticDataFromFile(file);

    for (int i = 0; i < students; i++)
        list[i].ReadDataFromFile(file);

    cout << "----------------------------------------------Data Read from File-------------------------------------------\n\n";
    PrintDataFromFile(list, students);

    file.close();
    return list;
}

void PrintDataFromFile(EvalReport* list, int students)
{
    list->totalStudents = students;
    cout << "Roll No.   Name \t\t\tQ1 \t Q2 \t Q3 \t Q4 \t A1 \t A2 \t A3 \t A4 \t Total\n";
    for (int i = 0; i < list->totalStudents; i++)
    {
        cout << list[i].rollNo << "  " << list[i].fName << " " << list[i].lName << "              \t";
        for (int j = 0; j < list->totalQuiz; j++)
            cout << " " << list[i].quizN[j] << "  \t";
        for (int j = 0; j < list->totalAssignments; j++)
            cout << " " << list[i].assignmentN[j] << "  \t";
        cout << "  " << list[i].total;
        cout << endl;
    }
}

void PrintSortedData(EvalReport* list)
{
    int i, j;
   // EvalReport temp;
    bool swapped;
    for (i = 0; i < list->totalStudents - 1; i++) { // Bubble Sort in Ascending order 
        swapped = false;
        for (j = 0; j < list->totalStudents - i - 1; j++)
            if (list[j + 1].total < list[j].total) {
                EvalReport temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
                swapped = true;
            }
        if (swapped == false)
            break;
    }

    cout << "\n\n---------------------------------------------------Sorted List------------------------------------------------\n\n";
    PrintDataFromFile(list, list->totalStudents);
}

void StudentInfo(EvalReport* list, const char* roll)
{
    int totalMarks = 0;
    for (int i = 0; i < list->totalQuiz; i++)
        totalMarks = totalMarks + list->quizMarks[i];
    for (int i = 0; i < list->totalAssignments; i++)
        totalMarks = totalMarks + list->assignmentMarks[i];
    bool found = true;
    for (int i = 0; i < list->totalStudents; i++)
    {
        if (Helper::matchStrings(roll, list[i].rollNo) == false)
            found = false;
        else
        {
            cout << "Roll No: \t" << list[i].rollNo << endl;
            cout << "Name: \t" << list[i].fName << " " << list[i].lName << endl;
            cout << "Quizzes Marks: \n";
            for (int j = 0; j < list->totalQuiz; j++)
                cout << "Q" << j + 1 << ":\t" << list[i].quizN[j] << "/" << list->quizMarks[j] << endl;
            cout << endl;
            for (int j = 0; j < list->totalAssignments; j++)
                cout << "A" << j + 1<< ":\t" << list[i].assignmentN[j] << "/" << list->assignmentMarks[j] << endl;
            cout << endl;
            cout << "Total:\t" << list[i].total << "/" << totalMarks << endl;
            found = true;
            break;
        }
    }
    if (found == false)
        cout << "Student not found.\n\n";
}

void PrintStats(EvalReport* list)
{
    cout << "\n\n--------------------------------------------------Class Statistics-----------------------------------------------\n\n";
    int *max = 0, *min = 0, *avg = 0;
    max = maxMarks(list);
    min = minMarks(list);
    avg = avgMarks(list);
    
    cout << "\t\t";
    for (int j = 0; j < list->totalQuiz; j++)
        cout << "Q" << j + 1<< "\t";
    for (int j = 0; j < list->totalAssignments; j++)
        cout << "A" << j + 1<< "\t";
    cout << "\nTotal:\t\t";
    for (int j = 0; j < list->totalQuiz; j++)
        cout << list->quizMarks[j] << "\t";
    for (int j = 0; j < list->totalAssignments; j++)
        cout << list->assignmentMarks[j] << "\t";
    cout << "\nMaximum:\t";
    for (int j = 0; j < list->totalAssignments + list->totalQuiz; j++)
        cout << max[j] << "\t";
    cout << "\nMinimum:\t";
    for (int j = 0; j < list->totalAssignments + list->totalQuiz; j++)
        cout << min[j] << "\t";
    cout << "\nAverage:\t";
    for (int j = 0; j < list->totalAssignments + list->totalQuiz; j++)
        cout << avg[j] << "\t";
}

int* maxMarks(EvalReport* list)
{
    int cMax;
    int* temp = new int[list->totalQuiz + list->totalAssignments];
    for (int k = 0; k < list->totalQuiz + list->totalAssignments;)
    {
        for (int j = 0; j < list->totalQuiz; j++)
        {
            cMax = 0;
            for (int i = 0; i < list->totalStudents; i++)
            {
                if (list[i].quizN[j] > cMax)
                    cMax = list[i].quizN[j];
            }
            temp[k++] = cMax;
        }
        for (int j = 0; j < list->totalAssignments; j++)
        {
            cMax = 0;
            for (int i = 0; i < list->totalStudents; i++)
            {
                if (list[i].assignmentN[j] > cMax)
                    cMax = list[i].assignmentN[j];
            }
            temp[k++] = cMax;
        }
    }
    return temp;
}

int* minMarks(EvalReport* list)
{
    int cMin;
    int* temp = new int[list->totalQuiz + list->totalAssignments];
    for (int k = 0; k < list->totalQuiz + list->totalAssignments;)
    {
        for (int j = 0; j < list->totalQuiz; j++)
        {
            cMin = 100; // Set minimum to outside of possible range so that it always changes
            for (int i = 0; i < list->totalStudents; i++)
            {
                if (list[i].quizN[j] < cMin)
                    cMin = list[i].quizN[j];
            }
            temp[k++] = cMin;
        }
        for (int j = 0; j < list->totalAssignments; j++)
        {
            cMin = 100;
            for (int i = 0; i < list->totalStudents; i++)
            {
                if (list[i].assignmentN[j] < cMin)
                    cMin = list[i].assignmentN[j];
            }
            temp[k++] = cMin;
        }
    }
    return temp;
}

int* avgMarks(EvalReport* list)
{
    int cAvg;
    int* temp = new int[list->totalQuiz + list->totalAssignments];
    for (int k = 0; k < list->totalQuiz + list->totalAssignments;) // Loop for Current Quiz/Assignment
    {
        for (int j = 0; j < list->totalQuiz; j++) // Loop for current quiz
        {
            cAvg = 0;
            for (int i = 0; i < list->totalStudents; i++) //Loop for total Students 
            {
                cAvg = cAvg + list[i].quizN[j];
            }
            cAvg = cAvg / list->totalStudents;
            temp[k++] = cAvg;
        }
        for (int j = 0; j < list->totalAssignments; j++)
        {
            cAvg = 0;
            for (int i = 0; i < list->totalStudents; i++)
            {
                cAvg = cAvg + list[i].assignmentN[j];
            }
            cAvg = cAvg / list->totalStudents;
            temp[k++] = cAvg;
        }
    }
    return temp;
}

void main()
{
    EvalReport* list = ReadDataFromFile("gradesheet.txt");
    PrintSortedData(list);
    cout << endl;
    cout << "\n\n--------------------------------------------------Student Information-----------------------------------------------\n\n";
    cout << "Enter Student Roll No: 15L-1234\n";
    StudentInfo(list, "15L-1234");
    cout << endl;
    cout << "\n\n--------------------------------------------------Student Information-----------------------------------------------\n\n";
    cout << "Enter Student Roll No: 15L-4023\n";
    StudentInfo(list, "15L-4023");
    cout << endl;
    PrintStats(list);
    cout << endl;
    cout << "\n\n-------------------------------------------------------------------------------------------------------------------\n\n";

    list->DeleteStaticData();
}