#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
private:
    int rollNumber;
    string name;
    int age;
    string course;
    double marks;
public:
    // Constructor
    Student() {}

    // Member functions
    void setRollNumber(int roll) { rollNumber = roll; }
    void setName(const string& n) { name = n; }
    void setAge(int a) { age = a; }
    void setCourse(const string& c) { course = c; }
    void setMarks(double m) { marks = m; }

    int getRollNumber() const { return rollNumber; }
    const string& getName() const { return name; }
    int getAge() const { return age; }
    const string& getCourse() const { return course; }
    double getMarks() const { return marks; }
};

void addStudent(Student *&students, int &numStudents);
void showStudentList(const Student *students, int numStudents);
void editStudentInformation(Student *students, int numStudents);
void deleteStudent(Student *&students, int &numStudents);
void printGrades(const Student *students, int numStudents);
string Calculating_Grades(double marks);

int main() {
    Student *students = nullptr;
    int numStudents = 0;
    int choice;

    do {
        cout << "\n ========== Students Portal System =========== \n";
        cout << "|  Press '1' to Add Student                   |\n";
        cout << "|  Press '2' to Show List of Students         |\n";
        cout << "|  Press '3' to Edit Student Information      |\n";
        cout << "|  Press '4' to Delete Student                |\n";
        cout << "|  Press '5' to Print Grades of All Students  |\n";
        cout << "|  Press '6' to Exit                          |\n";
        cout << "|  Enter your choice:                         |\n";
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
                printGrades(students, numStudents);
                break;
            case 6:
                cout << "Exiting the Students Portal. Have a great day!\n";
                return 1;
            default:
                cout << "Invalid choice. Please enter a number From '1' to '6'.\n";
                continue;
        }

    } while (choice != 6);

    // Deallocate memory before exiting
    delete[] students;

    return 0;
}

void addStudent(Student *&students, int &numStudents) {
    // Allocate memory for a new student
    Student newStudent;

    cout << "Enter Roll Number: ";
    int roll;
    cin >> roll;
    newStudent.setRollNumber(roll);

    cout << "Enter Name: ";
    cin.ignore();
    string name;
    getline(cin, name);
    newStudent.setName(name);

    cout << "Enter Age: ";
    int age;
    cin >> age;
    newStudent.setAge(age);

    cout << "Enter Course: ";
    cin.ignore();
    string course;
    getline(cin, course);
    newStudent.setCourse(course);

    cout << "Enter Marks: ";
    double marks;
    cin >> marks;
    newStudent.setMarks(marks);

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
    ofstream outputFile("Students_Portal.txt", ios::app);
    if (outputFile.is_open()) {
        outputFile << newStudent.getRollNumber() << " "
                   << newStudent.getName() << " "
                   << newStudent.getAge() << " "
                   << newStudent.getCourse() << " "
                   << newStudent.getMarks() << endl;

        outputFile.close();
        cout << "Student data has been saved to Students_Portal.txt.\n";
    } else {
        cout << "Error opening file for writing!\n";
    }
}

void showStudentList(const Student *students, int numStudents) {
    ifstream inputFile("Students_Portal.txt");
    if (inputFile.is_open()) {
        int rollNumber;
        string name, course;
        int age, marks;
        
        cout << "\nList of Students:\n";
        int i = 0;
        while (inputFile >> rollNumber >> name >> age >> course >> marks) {
            cout << "Roll Number: " << rollNumber << endl;
            cout << "Name: " << name << endl;
            cout << "Age: " << age << endl;
            cout << "Course: " << course << endl;
            cout << "Marks: " << marks << endl;
            cout << "-------------------------\n";
            ++i;
        }
        
        if (i == 0) {
            cout << "Oops! There's no data to fetch.\n";
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
        if (students[i].getRollNumber() == rollNumber) {
            cout << "Enter updated information:\n";
            cout << "Name: ";
            cin.ignore();
            string name;
            getline(cin, name);
            students[i].setName(name);
            cout << "Age: ";
            int age;
            cin >> age;
            students[i].setAge(age);
            cout << "Course: ";
            cin.ignore();
            string course;
            getline(cin, course);
            students[i].setCourse(course);
            cout << "Marks: ";
            double marks;
            cin >> marks;
            students[i].setMarks(marks);

            found = true;
            break;
        }
    }

    if (found) {
        // Save to file
        ofstream outputFile("Students_Portal.txt");
        if (outputFile.is_open()) {
            for (int i = 0; i < numStudents; ++i) {
                outputFile << students[i].getRollNumber() << " "
                           << students[i].getName() << " "
                           << students[i].getAge() << " "
                           << students[i].getCourse() << " "
                           << students[i].getMarks() << endl;
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

    ifstream inFile("Students_Portal.txt"); // Open the input file
    if (!inFile.is_open()) {
        cerr << "Error opening input file." << endl;
        return;
    }

    ofstream outFile("temp.txt"); // Open a temporary file for writing

    string line;
    bool rollNumberFound = false;
    while (getline(inFile, line)) { // Read each line of the file
        // Extract the roll number from the line
        int extractedRollNumber;
        if (sscanf(line.c_str(), "%d", &extractedRollNumber) == 1) {
            // Check if the extracted roll number matches the one to delete
            if (extractedRollNumber == rollNumber) {
                rollNumberFound = true;
                continue; // Skip writing this line if roll number found
            }
        }

        outFile << line << endl; // Write the line to the temporary file
    }

    inFile.close(); // Close the input file
    outFile.close(); // Close the temporary file

    if (!rollNumberFound) {
        cout << "Roll Number " << rollNumber << " not found." << endl;
        remove("temp.txt"); // Delete the temporary file if roll number not found
    } else {
        if (remove("Students_Portal.txt") != 0) { // Delete the original file
            cerr << "Error deleting input file." << endl;
            return;
        }

        if (rename("temp.txt", "Students_Portal.txt") != 0) { // Rename the temporary file to the original file
            cerr << "Error renaming temporary file." << endl;
            return;
        }

        cout << "Student with Roll Number " << rollNumber << " deleted successfully." << endl;
    }
}


// void enterMarks(Student *students, int numStudents) {
//     cout << "Enter the Roll Number of the student you want to Enter Marks of: ";
//     int rollNumber;
//     cin >> rollNumber;

//     bool found = false;

//     for (int i = 0; i < numStudents; ++i) {
//         if (students[i].getRollNumber() == rollNumber) {
//             cout << "Enter updated Marks:\n";
//             cout << "Marks: ";
//             double marks;
//             cin >> marks;
//             students[i].setMarks(marks);
//             found = true;
//             break;
//         }
//     }

//     if (found) {
//         // Save to file
//         ofstream outputFile("Students_Portal.txt");
//         if (outputFile.is_open()) {
//             for (int i = 0; i < numStudents; ++i) {
//                 outputFile<< students[i].getMarks() << endl;
//             }
//             outputFile.close();
//             cout << "Successfully edited\n";
//         } else {
//             cout << "Error opening file for writing!\n";
//         }
//     } else {
//         cout << "Student with Roll Number " << rollNumber << " not found.\n";
//     }
// }

void printGrades(const Student *students, int numStudents) {
    ifstream inputFile("Students_Portal.txt");
    if (inputFile.is_open()) {
        cout << "\nList of Students:\n";
        for (int i = 0; i < numStudents; ++i) {
            cout << "Roll Number: " << students[i].getRollNumber() << endl;
            cout << "Course: " << students[i].getCourse() << endl;
            cout << "Grades: " << Calculating_Grades(students[i].getMarks()) << endl;
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
