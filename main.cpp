#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Gradebook {
private:
    struct Student {
        string firstName;
        string lastName;
        int studentID;
        vector<double> grades;
    };

    struct Assignment {
        string name;
        double totalPoints;
    };

    vector<Student> students;
    vector<Assignment> assignments;

public:

    void addStudent(const string& firstName, const string& lastName, int studentID) {
        students.push_back({firstName, lastName, studentID, {}});
        for (auto& student : students) {
            student.grades.resize(assignments.size(), 0.0);
        }
    }


    void addAssignment(const string& assignmentName, double totalPoints) {
        assignments.push_back({assignmentName, totalPoints});
        for (auto& student : students) {
            student.grades.push_back(0.0);
        }
    }


    bool giveGrade(int studentID, int assignmentIndex, double grade) {
        if (assignmentIndex < 0 || assignmentIndex >= assignments.size()) {
            cerr << "Invalid assignment index." << endl;
            return false;
        }

        for (auto& student : students) {
            if (student.studentID == studentID) {
                if (grade >= 0 && grade <= assignments[assignmentIndex].totalPoints) {
                    student.grades[assignmentIndex] = grade;
                    return true;
                } else {
                    cerr << "Invalid grade. Must be between 0 and " << assignments[assignmentIndex].totalPoints << endl;
                    return false;
                }
            }
        }
        cerr << "Student not found." << endl;
        return false;
    }

    void printReport() const {
        if (assignments.empty()) {
            cout << "No assignments available to report." << endl;
            return;
        }

        cout << "\n============================== GRADEBOOK REPORT ==============================\n";
        cout << left << setw(20) << "Student Name" << setw(15) << "Student ID";
        for (const auto& assignment : assignments) {
            cout << setw(20) << assignment.name;
        }
        cout << "\n-------------------------------------------------------------------------------\n";

        for (const auto& student : students) {
            cout << left << setw(20) << (student.firstName + " " + student.lastName)
                      << setw(15) << student.studentID;
            for (const auto& grade : student.grades) {
                cout << fixed << setprecision(2) << setw(20) << grade;
            }
            cout << "\n";
        }
        cout << "===============================================================================\n";
    }
};

int main() {
    Gradebook gradebook;

    gradebook.addStudent("John", "Doe", 12345);
    gradebook.addStudent("Jane", "Smith", 67890);
    gradebook.addStudent("Alice", "Johnson", 11223);
    gradebook.addStudent("Bob", "Brown", 33445);
    gradebook.addStudent("Ben", "Ten", 224409);

    gradebook.addAssignment("Homework 1", 100);
    gradebook.addAssignment("Midterm", 200);
    gradebook.addAssignment("Final Project", 150);

    gradebook.giveGrade(12345, 0, 85);
    gradebook.giveGrade(12345, 1, 180);
    gradebook.giveGrade(12345, 2, 140);

    gradebook.giveGrade(67890, 0, 95);
    gradebook.giveGrade(67890, 1, 190);
    gradebook.giveGrade(67890, 2, 145);

    gradebook.giveGrade(11223, 0, 78);
    gradebook.giveGrade(11223, 1, 160);
    gradebook.giveGrade(11223, 2, 130);

    gradebook.giveGrade(33445, 0, 88);
    gradebook.giveGrade(33445, 1, 170);
    gradebook.giveGrade(33445, 2, 135);

    gradebook.giveGrade(224409, 0, 40);
    gradebook.giveGrade(224409, 1, 130);
    gradebook.giveGrade(224409, 2, 60);

    gradebook.printReport();

    return 0;
}
