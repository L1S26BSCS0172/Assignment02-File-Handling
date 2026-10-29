/*
 * Name       : Muhammad Faizan
 * Reg No     : L1F24BSCS0081
 * Assignment : 02 - File Handling
 * Question   : Q5 - Expense Tracker
 */

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    int choice = 0;

    do {
        // The full menu is displayed before every choice
        cout << "===== Expense Tracker =====" << endl;
        cout << "1. Add an expense" << endl;
        cout << "2. Show all expenses" << endl;
        cout << "3. Show total of a category" << endl;
        cout << "4. Clear all expenses" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";

        // Stop instead of looping forever if the input ends unexpectedly
        if (!(cin >> choice)) {
            break;
        }

        if (choice == 1) {
            // Add an expense: ios::app keeps the old lines
            char category[20];
            int amount = 0;

            cout << "Enter category: ";
            cin >> category;
            cout << "Enter amount: ";
            cin >> amount;

            if (amount <= 0) {
                cout << "Invalid amount!" << endl;
            }
            else {
                ofstream outFile("expenses.txt", ios::app);
                outFile << category << " " << amount << endl;
                outFile.close();
                cout << "Expense saved." << endl;
            }
        }
        else if (choice == 2) {
            // Show all expenses: open the file again to see the latest data
            ifstream inFile("expenses.txt");

            char category[20];
            char largestCategory[20] = "";
            int amount;
            int count = 0;
            int total = 0;
            int largest = 0;

            if (inFile) {
                while (count < 100 && inFile >> category >> amount) {
                    count++;
                    cout << count << ". " << category << " " << amount << endl;
                    total = total + amount;

                    // ">" (not ">=") keeps the first one when amounts are equal
                    if (count == 1 || amount > largest) {
                        largest = amount;
                        strcpy(largestCategory, category);
                    }
                }
                inFile.close();
            }

            if (count == 0) {
                cout << "No expenses yet." << endl;
            }
            else {
                cout << "Total spent: " << total << endl;
                cout << "Largest expense: " << largestCategory << " (" << largest << ")" << endl;
            }
        }
        else if (choice == 3) {
            // Total of one category
            char wanted[20];
            cout << "Enter category: ";
            cin >> wanted;

            ifstream inFile("expenses.txt");

            char category[20];
            int amount;
            int count = 0;
            int total = 0;

            if (inFile) {
                while (inFile >> category >> amount) {
                    if (strcmp(category, wanted) == 0) {
                        count++;
                        total = total + amount;
                    }
                }
                inFile.close();
            }

            if (count == 0) {
                cout << "No expenses found for " << wanted << endl;
            }
            else {
                cout << "Expenses in " << wanted << ": " << count << endl;
                cout << "Total for " << wanted << ": " << total << endl;
            }
        }
        else if (choice == 4) {
            // Clear: a plain ofstream erases the file
            ofstream outFile("expenses.txt");
            outFile.close();
            cout << "All expenses cleared." << endl;
        }
        else if (choice == 5) {
            cout << "Goodbye!" << endl;
        }
        else {
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 5);

    return 0;
}