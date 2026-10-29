/*
 * Name       : Muhammad Faizan
 * Reg No     : L1S26BSCS0172
 * Assignment : 02 - File Handling
 * Question   : Q3 - Scholarship List
 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    // The user types the file name (it may contain spaces, so use getline)
    char path[100];
    cout << "Enter the file name: ";
    cin.getline(path, 100);

    // Open -> Check
    ifstream inFile(path);
    if (!inFile.is_open()) {
        cout << "Could not open " << path << "!" << endl;
        return 1;
    }

    // Read the number of students, then skip the rest of line 1
    int n = 0;
    inFile >> n;
    inFile.ignore(100, '\n');

    if (n > 30) {
        cout << "Too many students!" << endl;
        inFile.close();
        return 1;
    }

    ofstream outFile("scholarship.txt");   // created fresh every run

    char name[30];
    double cgpa;
    int count = 0;          // records actually read
    int eligible = 0;
    double sum = 0;
    char topName[30] = "";
    double topCgpa = -1;

    for (int i = 0; i < n; i++) {
        // If either read fails, the file ended early
        if (!inFile.getline(name, 30, ',')) {
            break;
        }
        if (!(inFile >> cgpa)) {
            break;
        }
        inFile.ignore(100, '\n');

        cout << "[" << name << "] CGPA: " << cgpa << endl;

        count++;
        sum = sum + cgpa;

        if (cgpa >= 3.5) {
            outFile << name << "," << cgpa << endl;
            eligible++;
        }

        // ">" (not ">=") keeps the first student when two CGPAs are equal
        if (cgpa > topCgpa) {
            topCgpa = cgpa;
            strcpy(topName, name);
        }
    }
    inFile.close();
    outFile.close();

    if (count < n) {
        cout << "Warning: only " << count << " of " << n << " records found." << endl;
    }

    if (count == 0) {
        cout << "No students found!" << endl;
        return 0;
    }

    cout << "Students: " << count << endl;
    cout << "Average CGPA: " << sum / count << endl;
    cout << "Eligible for scholarship: " << eligible << endl;
    cout << "Top student: " << topName << " (" << topCgpa << ")" << endl;

    return 0;
}