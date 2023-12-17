// In this project, you have to create Management System used by admission office of the university. This
// software is used by office to enter info about new students as well as used by teachers to enter marks of the students for a given exam and course. The program has features like
//  Add Student
//  Show list Student
//  Edit Student Information
//  Delete Student
//  Register student in a course
//  Enter marks of the student or complete class
//  Print Grades of students
// Note: use arrays, structures, files, loops 

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Define a structure to represent a student
struct Student {
    int rollNumber;
    string name;
    int age;
    string course;
    double marks;
};

// Function prototypes
int displayMenu(int);
void addStudent(Student& student);
void showStudentList();
void editStudentInformation();
void deleteStudent();
void registerStudentInCourse();
void enterMarks();
void printGrades();

int main() {
    
    int choice;
    do{
        Student new_student;
        choice=displayMenu(choice);
        if(choice==1)
            addStudent(new_student);
        else if(choice==2)
            showStudentList();
        else if(choice==3)
            editStudentInformation();
        else if(choice==4)
            deleteStudent();
        else if(choice==5)
            registerStudentInCourse();
        else if(choice==7)
            printGrades();
    }while(choice !=8);

    return 0;
}

int displayMenu(int choice1) {
    cout << "\n===== University Admission Office Management System =====\n";
    cout << "1. Add Student\n";
    cout << "2. Show List of Students\n";
    cout << "3. Edit Student Information\n";
    cout << "4. Delete Student\n";
    cout << "5. Register Student in a Course\n";
    cout << "6. Enter Marks of a Student or Complete Class\n";
    cout << "7. Print Grades of Students\n";
    cout << "8. Exit\n";
    cin>>choice1;
    while (choice1 < 1 || choice1 > 8) {
        cout << "Invalid choice. Please enter a number between 1 and 8: ";
        cin >> choice1;
    }
    return choice1;
}

void addStudent(Student& student) {
    cout << "Enter Roll Number: ";
    cin >> student.rollNumber;
    cout << "Enter Name: ";
    cin.ignore(); 
    getline(cin, student.name);
    cout << "Enter Age: ";
    cin >> student.age;
    cout << "Enter Course: ";
    cin.ignore();  
    getline(cin, student.course);
    cout << "Enter Marks: ";
    cin >> student.marks;

    ofstream outputFile("student_data.txt", ios::app);
    if (outputFile.is_open()) {
        outputFile << "Roll Number: " << student.rollNumber << endl;
        outputFile << "Name: " << student.name << endl;
        outputFile << "Age: " << student.age << endl;
        outputFile << "Course: " << student.course << endl;
        outputFile << "Marks: " << student.marks << endl;
        outputFile << "-------------------------\n";  // Separator for multiple students data
        outputFile.close();
        cout << "Student data has been saved to student_data.txt.\n";
    } else {
        cout << "Error opening file for writing!\n";
    }
}

void showStudentList() {
    ifstream inputFile("student_data.txt");
    if (inputFile.is_open())
    {
        cout << "\nContents of user_data.txt:\n";
        string line;
        while (getline(inputFile, line))
        {
            cout << line << endl;
        }
        inputFile.close();
    }
    else
    {
        cout << "Error opening file for reading!" << endl;;
    }

}

void editStudentInformation(Student& student) {
    cout << "Enter the Roll Number of the student you want to edit: ";
    int rollNumber;
    cin >> rollNumber;
    ifstream inputFile("student_data.txt");
    
    if (inputFile.is_open()) {
        while (inputFile >> student.rollNumber >> student.name >> student.age >> student.course >> student.marks) {
            if (student.rollNumber == rollNumber) {
                inputFile.close();
                // return true;  // Found the student with the given roll number
            }
        }

        inputFile.close();
    } else {
        cout << "Error opening file for reading!\n";
    }
    // return false;
}

void deleteStudent() {
    // Implementation for deleting a student
    // ...
}

void registerStudentInCourse() {
    // Implementation for registering a student in a course
    // ...
}

void enterMarks() {
    // Implementation for entering marks of a student or complete class
    // ...
}

void printGrades() {
    // Implementation for printing grades of students
    // ...
}
