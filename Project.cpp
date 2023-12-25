#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    int rollNumber;
    string name;
    int age;
    string course;
    double marks;
};

void addStudent(Student *&students, int &numStudents);
void showStudentList(const Student *students, int numStudents);
void editStudentInformation(Student *students, int numStudents);
void deleteStudent(Student *&students, int &numStudents);
void registerStudentInCourse(Student *students, int numStudents);
void enterMarks(Student *students, int numStudents);
void printGrades(const Student *students, int numStudents);
string Calculating_Grades(double marks);

int main() {
    Student *students = nullptr;
    int numStudents = 0;
    int choice;

    do {
        cout << "\n===== University Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Show List of Students\n";
        cout << "3. Edit Student Information\n";
        cout << "4. Delete Student\n";
        cout << "5. Register Student in a Course\n";
        cout << "6. Enter Marks of a Student or Complete Class\n";
        cout << "7. Print Grades of Students\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students, numStudents);
                break;
            case 2:
                showStudentList(students, numStudents);
                break;
            case 3:
                editStudentInformation(students, numStudents);
                break;
            case 4:
                deleteStudent(students, numStudents);
                break;
            case 5:
                addStudent(students, numStudents);
                // registerStudentInCourse(students, numStudents);
                break;
            case 6:
                enterMarks(students, numStudents);
                break;
            case 7:
                printGrades(students, numStudents);
                break;
            case 8:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 8.\n";
        }

    } while (choice != 8);

    // Deallocate memory before exiting
    delete[] students;

    return 0;
}

void addStudent(Student *&students, int &numStudents) {
    // Allocate memory for a new student
    Student newStudent;

    cout << "Enter Roll Number: ";
    cin >> newStudent.rollNumber;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, newStudent.name);
    cout << "Enter Age: ";
    cin >> newStudent.age;
    cout << "Enter Course: ";
    cin.ignore();
    getline(cin, newStudent.course);
    cout << "Enter Marks: ";
    cin >> newStudent.marks;

    // Resize the array to accommodate the new student
    Student *temp = new Student[numStudents + 1];
    for (int i = 0; i < numStudents; ++i) {
        temp[i] = students[i];
    }

    // Add the new student to the array
    temp[numStudents] = newStudent;

    // Deallocate the old array
    delete[] students;

    // Update the pointer to the new array
    students = temp;

    numStudents++;

    // Save to file
    ofstream outputFile("student404_data.txt", ios::app);
    if (outputFile.is_open()) {
        outputFile << newStudent.rollNumber << " "
                   << newStudent.name << " "
                   << newStudent.age << " "
                   << newStudent.course << " "
                   << newStudent.marks << endl;

        outputFile.close();
        cout << "Student data has been saved to student404_data.txt.\n";
    } else {
        cout << "Error opening file for writing!\n";
    }
}

void showStudentList(const Student *students, int numStudents) {
    ifstream inputFile("student404_data.txt");
    if (inputFile.is_open()) {
        cout << "\nList of Students:\n";
        for (int i = 0; i < numStudents; ++i) {
            cout << "Roll Number: " << students[i].rollNumber << endl;
            cout << "Name: " << students[i].name << endl;
            cout << "Age: " << students[i].age << endl;
            cout << "Course: " << students[i].course << endl;
            cout << "Marks: " << students[i].marks << endl;
            cout << "-------------------------\n";
        }
        inputFile.close();
    } else {
        cout << "Error opening file for reading!\n";
    }
}

void editStudentInformation(Student *students, int numStudents) {
    cout << "Enter the Roll Number of the student you want to edit: ";
    int rollNumber;
    cin >> rollNumber;

    bool found = false;

    for (int i = 0; i < numStudents; ++i) {
        if (students[i].rollNumber == rollNumber) {
            cout << "Enter updated information:\n";
            cout << "Name: ";
            cin.ignore();
            getline(cin, students[i].name);
            cout << "Age: ";
            cin >> students[i].age;
            cout << "Course: ";
            cin.ignore();
            getline(cin, students[i].course);
            cout << "Marks: ";
            cin >> students[i].marks;

            found = true;
            break;
        }
    }

    if (found) {
        // Save to file
        ofstream outputFile("student404_data.txt");
        if (outputFile.is_open()) {
            for (int i = 0; i < numStudents; ++i) {
                outputFile << students[i].rollNumber << " "
                           << students[i].name << " "
                           << students[i].age << " "
                           << students[i].course << " "
                           << students[i].marks << endl;
            }
            outputFile.close();
            cout << "Successfully edited\n";
        } else {
            cout << "Error opening file for writing!\n";
        }
    } else {
        cout << "Student with Roll Number " << rollNumber << " not found.\n";
    }
}

void deleteStudent(Student *&students, int &numStudents) {
    cout << "Enter the Roll Number of the student you want to delete: ";
    int rollNumber;
    cin >> rollNumber;

    bool found = false;

    for (int i = 0; i < numStudents; ++i) {
        if (students[i].rollNumber == rollNumber) {
            found = true;
            // Shift the remaining elements to fill the gap
            for (int j = i; j < numStudents - 1; ++j) {
                students[j] = students[j + 1];
            }
            numStudents--;

            // Resize the array to accommodate the removed student
            Student *temp = new Student[numStudents];
            for (int k = 0; k < numStudents; ++k) {
                temp[k] = students[k];
            }

            // Deallocate the old array
            delete[] students;

            // Update the pointer to the new array
            students = temp;

            break;
        }
    }

    if (found) {
        // Save to file
        ofstream outputFile("student404_data.txt");
        if (outputFile.is_open()) {
            for (int i = 0; i < numStudents; ++i) {
                outputFile << students[i].rollNumber << " "
                           << students[i].name << " "
                           << students[i].age << " "
                           << students[i].course << " "
                           << students[i].marks << endl;
            }
            outputFile.close();
            cout << "Student with Roll Number " << rollNumber << " has been deleted.\n";
        } else {
            cout << "Error opening file for writing!\n";
        }
    } else {
        cout << "Student with Roll Number " << rollNumber << " not found.\n";
    }
}

void registerStudentInCourse(Student *students, int numStudents) {
    // Implementation for registering a student in a course
    // ...
}

void enterMarks(Student *students, int numStudents) {
    cout << "Enter the Roll Number of the student you want to Enter Marks of: ";
    int rollNumber;
    cin >> rollNumber;

    bool found = false;

    for (int i = 0; i < numStudents; ++i) {
        if (students[i].rollNumber == rollNumber) {
            cout << "Enter updated Marks:\n";
            cout << "Marks: ";
            cin >> students[i].marks;
            found = true;
            break;
        }
    }

    if (found) {
        // Save to file
        ofstream outputFile("student404_data.txt");
        if (outputFile.is_open()) {
            for (int i = 0; i < numStudents; ++i) {
                outputFile<< students[i].marks << endl;
            }
            outputFile.close();
            cout << "Successfully edited\n";
        } else {
            cout << "Error opening file for writing!\n";
        }
    } else {
        cout << "Student with Roll Number " << rollNumber << " not found.\n";
    }
}

void printGrades(const Student *students, int numStudents) {
    ifstream inputFile("student404_data.txt");
    if (inputFile.is_open()) {
        cout << "\nList of Students:\n";
        for (int i = 0; i < numStudents; ++i) {
            cout << "Roll Number: " << students[i].rollNumber << endl;
            cout << "Course: " << students[i].course << endl;
            cout << "Grades: " << Calculating_Grades(students[i].marks)<< endl;
            cout << "-------------------------\n";
        }
        inputFile.close();
    } else {
        cout << "Error opening file for reading!\n";
    }
}
string Calculating_Grades(double a){
    if(a>90)
        return "A+";
    else if(a>80)
        return "A";
    else if(a>70)
        return "B";
    else if(a>60)
        return "C";
    else if(a>50)
        return "D";
    else
        return "E";
}
