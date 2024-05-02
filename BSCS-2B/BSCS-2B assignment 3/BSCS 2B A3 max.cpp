#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

using namespace std;

class EvalReport{
    string name, rollNo;
    int *quizzesArr = 0, *assignmentsArr = 0, total = 0;
    
    public:
    static int totalStd, totalQ, totalA, totalPossible, *totalQMarks, *totalAMarks;
    static int *globalMax, *globalMin, *globalAvg;

    EvalReport() {
        quizzesArr = new int[totalQ];
        assignmentsArr = new int[totalA];
        name = "";
    }

    ~EvalReport() {
        if(quizzesArr)
            delete[] quizzesArr;
        if(assignmentsArr)
            delete[] assignmentsArr;
        
        quizzesArr = assignmentsArr = 0;
    }

    void inputQ(int marks, int index) {quizzesArr[index] = marks;}

    void inputA(int marks, int index) {assignmentsArr[index] = marks;}

    void inputName(string input) {name += input;}

    void inputRoll(string input) {rollNo = input;}

    void calculateTotal() {
        int ptr = 0;
        for(int i=0; i < totalQ; i++) total += quizzesArr[i];
        for(int i=0; i < totalA; i++) total += assignmentsArr[i];
    }

    int getQuiz(int index) {return quizzesArr[index];}

    int getAssignment(int index) {return assignmentsArr[index];}

    int getTotal() {return total;}

    string getName() {return name;}

    string getRoll() {return rollNo;}
};

int EvalReport::totalStd, EvalReport::totalQ, EvalReport::totalA, EvalReport::totalPossible, *EvalReport::totalQMarks, *EvalReport::totalAMarks;
int *EvalReport::globalMax, *EvalReport::globalMin, *EvalReport::globalAvg;

void initalizeTotal(ifstream& file) {
    file >> EvalReport::totalStd;
    file >> EvalReport::totalQ;
    file >> EvalReport::totalA;
    EvalReport::totalPossible = 0;

    EvalReport::totalQMarks = new int[EvalReport::totalQ];
    for(int i=0; i < EvalReport::totalQ; i++) {
        file >> EvalReport::totalQMarks[i];
        EvalReport::totalPossible += EvalReport::totalQMarks[i];
    }
    
    EvalReport::totalAMarks = new int[EvalReport::totalA];
    for(int i=0; i < EvalReport::totalA; i++) {
        file >> EvalReport::totalAMarks[i]; 
        EvalReport::totalPossible += EvalReport::totalAMarks[i];
    }
}

void initalizeReport(EvalReport **&evalReport, ifstream&file) {
    for(int i=0; i < EvalReport::totalStd; i++) {
        evalReport[i] = new EvalReport;

        string name;

        file >> name;
        evalReport[i]->inputName(name); //First name

        name = " ";
        evalReport[i]->inputName(name); //Space

        file >> name;
        evalReport[i]->inputName(name); //Last name

        file >> name;
        evalReport[i]->inputRoll(name);

        int marks;

        for(int j=0; j < EvalReport::totalQ; j++) {
            file >> marks;
            evalReport[i]->inputQ(marks, j);
        }

        for(int j=0; j < EvalReport::totalA; j++) {
            file >> marks;
            evalReport[i]->inputA(marks, j);
        }
        
        evalReport[i]->calculateTotal();
    }
}

void updateStatistics(EvalReport **&evalReport) {
    int statsCount = EvalReport::totalA + EvalReport::totalQ;

    EvalReport::globalMax = new int[statsCount];
    EvalReport::globalMin = new int[statsCount];
    EvalReport::globalAvg = new int[statsCount]; 

    for(int i=0; i < statsCount; i++) {
        EvalReport::globalMax[i] = 0;
        EvalReport::globalMin[i] = 0;
        EvalReport::globalAvg[i] = 0;
    }

    int temp;

    for(int i=0; i < EvalReport::totalStd; i++) {
        int ptr = 0;
        for(int j = 0; j < EvalReport::totalQ; j++) {
            temp = evalReport[i]->getQuiz(j);
            if(temp > EvalReport::globalMax[ptr]) EvalReport::globalMax[ptr] = temp;
            if(temp < EvalReport::globalMin[ptr]) EvalReport::globalMin[ptr] = temp;
            EvalReport::globalAvg[ptr] += temp;
            ptr++;
        }

        for(int j = 0; j < EvalReport::totalA; j++) {
            temp = evalReport[i]->getAssignment(j);
            if(temp > EvalReport::globalMax[ptr]) EvalReport::globalMax[ptr] = temp;
            if(temp < EvalReport::globalMin[ptr]) EvalReport::globalMin[ptr] = temp;
            EvalReport::globalAvg[ptr] += temp;
            ptr++;
        }
    }


    for(int i=0; i < statsCount; i++) {
            EvalReport::globalAvg[i] /= EvalReport::totalStd;
    }
}

int strLen(string str) {
    int counter = 0;
    while(str[counter++] != '\0');
    return counter;
}

void printAll(EvalReport **evalReport, bool showAll = 1,  int length = EvalReport::totalStd) {
    if(length == 0) {
        printf("\n\nNo matching data was found.\n");
        return;
    }

    if(showAll) {
    cout << "\t\t";

    for(int i=0; i < EvalReport::totalQ ; i++) printf("Q%i\t", i+1);
    for(int i=0; i < EvalReport::totalA ; i++) printf("A%i\t", i+1);

    cout << "\nTotal:\t\t";
    for(int i=0; i < EvalReport::totalQ ; i++) printf("%i\t", EvalReport::totalQMarks[i]);
    for(int i=0; i < EvalReport::totalA ; i++) printf("%i\t", EvalReport::totalAMarks[i]);

    cout << "\nMaximum:\t";
    for(int i=0; i < EvalReport::totalQ + EvalReport::totalA ; i++) printf("%i\t", EvalReport::globalMax[i]);

    cout << "\nMinimum:\t";
    for(int i=0; i < EvalReport::totalQ + EvalReport::totalA; i++) printf("%i\t", EvalReport::globalMin[i]);

    cout << "\nAverage:\t";
    for(int i=0; i < EvalReport::totalQ + EvalReport::totalA; i++) printf("%i\t", EvalReport::globalAvg[i]);
    }

    cout << "\n\nRoll No.\tName\t\t ";
    
    for(int i=0; i < EvalReport::totalQ ; i++) printf("Q%i\t", i+1);
    for(int i=0; i < EvalReport::totalA ; i++) printf("A%i\t", i+1);
    
    cout << "Total";
    for(int i=0; i < length; i++) {
        printf("\n%s\t%s", evalReport[i]->getRoll().c_str(), evalReport[i]->getName().c_str());
        
        int length = strLen(evalReport[i]->getName());

        if(length < 17)
            cout << '\t';

        if(length < 9)
            cout << '\t';

        cout << ' ';

        for(int j=0; j < EvalReport::totalQ ; j++) printf("%i\t", evalReport[i]->getQuiz(j));
        for(int j=0; j < EvalReport::totalA ; j++) printf("%i\t", evalReport[i]->getAssignment(j));
        cout << evalReport[i]->getTotal();
    }
}

bool checkEquality(char a, char b) {
    if(a >= 'a' && a <= 'z')
        a -= 32;

    if(b >= 'a' && b <= 'z')
        b -= 32;
    
    return a == b;
}


bool stringContains(string original, string input) {
    int length = strLen(original);
    
    for(int i=0; i < length; i++) {
        int ptr = 0;
        
        while(checkEquality(original[i + ptr], input[ptr])) {
            ptr++;
        }

        if(ptr == strLen(input) - 1 || ptr == strLen(input))
            return 1;
    }

    return 0;
}

int countWord(EvalReport** evalReport, string input) {
    int counter = 0;
    for(int i=0; i < EvalReport::totalStd; i++) {
        if(stringContains(evalReport[i]->getName(), input)) {
            counter++;
            continue;
        }
        if(stringContains(evalReport[i]->getRoll(), input)) {
            counter++;
            continue;
        }
    }
    return counter;
}

EvalReport** searchStudents(EvalReport** evalReport, int &newLength) {
    string input;
    cout << "\n\nEnter the keyword to filter the list by: ";
    cin >> input;

    newLength = countWord(evalReport, input);

    EvalReport **filteredReport = new EvalReport*[newLength];

    int ptr = 0;

    for(int i=0; i < EvalReport::totalStd; i++) {
        
        if(stringContains(evalReport[i]->getName(), input)) {
            filteredReport[ptr++] = evalReport[i];
            continue;
        }

        if(stringContains(evalReport[i]->getRoll(), input)) {
            filteredReport[ptr++] = evalReport[i];
            continue;
        }
    }

    return filteredReport;
}

void sortListByChoice(EvalReport** &evalReport, bool byName) {
    for(int i=0; i < EvalReport::totalStd - 1; i++) {
        for(int j=0; j < EvalReport::totalStd - 1; j++) {
            if(byName && !(evalReport[j]->getName() > evalReport[j + 1]->getName()))
                continue;
            if(!byName && !(evalReport[j]->getTotal() > evalReport[j + 1]->getTotal()))
                continue;

            EvalReport *temp = evalReport[j];
            evalReport[j] = evalReport[j + 1];
            evalReport[j+1] = temp;
        }
    }
}

void sortList(EvalReport** &evalReport) {
    int choice = 0;
    while(choice != 1 && choice != 2) {
    cout << "\n\nBy what metric do you want to sort the list?\n1. Alphabetical\n2. Total marks\n";
    cin >> choice;
    switch(choice) {
        case 1: {
            sortListByChoice(evalReport, 1);
            break;
        }

        case 2: {
            sortListByChoice(evalReport, 0);
            break;
        }

        default: {
            cout << "\nInvalid input.";
        }
    }
    }
}

void dealloc(EvalReport** &evalReport) {
    delete[] EvalReport::totalQMarks, EvalReport::totalAMarks, EvalReport::globalMax, EvalReport::globalMin, EvalReport::globalAvg, evalReport;
}

void printDetailView(const char* rollNo, EvalReport **evalReport) {
    int index = -1;

    for(int i=0; i < EvalReport::totalStd; i++) {
        if(evalReport[i]->getRoll() == rollNo) {
            index = i;
            break;
        }
    }

    if(index == -1) {
        printf("\n\nStudent with the roll number %s was not found", rollNo);
        return;
    }

    printf("\n\nRoll No:\t%s\nName:\t\t%s\nQuizzes Marks:\n", evalReport[index]->getRoll().c_str(), evalReport[index]->getName().c_str());

    for(int i=0; i < EvalReport::totalQ; i++) printf("\t\tQ%i:\t%i/%i\n", i+1, evalReport[index]->getQuiz(i), EvalReport::totalQMarks[i]);
    printf("Assignment Marks:\n");
    for(int i=0; i < EvalReport::totalQ; i++) printf("\t\tA%i:\t%i/%i\n", i+1, evalReport[index]->getAssignment(i), EvalReport::totalAMarks[i]);

    printf("Total:\t\t\t%i/%i", evalReport[index]->getTotal(), EvalReport::totalPossible);
}

int main() {
    ifstream file("GradeSheet.txt");
    initalizeTotal(file);

    EvalReport **evalReport = new EvalReport*[EvalReport::totalStd]; 
    initalizeReport(evalReport, file);

    updateStatistics(evalReport);

    printAll(evalReport);

    int newLength;

    EvalReport **filteredReport = searchStudents(evalReport, newLength);

    printAll(filteredReport, 0, newLength);

    sortList(evalReport);

    printAll(evalReport, 0);
    
    printDetailView("23L-0655", evalReport);

    dealloc(evalReport);
}