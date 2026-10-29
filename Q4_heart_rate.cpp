/*
 * Name       : Muhammad Faizan
 * Reg No     : L1S26BSCS0172
 * Assignment : 02 - File Handling
 * Question   : Q4 - Heart Rate Cleaner
 */

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream inFile("heart_rate.txt");
    if (!inFile) {
        cout << "heart_rate.txt not found!" << endl;
        return 1;
    }

    int rate[100];
    int count = 0;      // number of valid readings stored in rate[]
    int bad = 0;        // number of junk words skipped
    int x;
    char junk[50];
    int reason = 0;     // 1 = sentinel found, 2 = end of file, 3 = array full

    while (true) {
        if (count == 100) {                // the array is full
            reason = 3;
            break;
        }
        if (inFile >> x) {                 // a number was read
            if (x == -1) {                 // the sentinel value
                reason = 1;
                break;
            }
            rate[count] = x;
            count++;
        }
        else if (inFile.eof()) {           // nothing left in the file
            reason = 2;
            break;
        }
        else {                             // a junk word
            inFile.clear();
            inFile >> junk;
            bad++;
        }
    }
    inFile.close();

    // TODO 1: Write every valid reading to clean_heart_rate.txt (one per line).
    ofstream outFile("clean_heart_rate.txt");
    for (int i = 0; i < count; i++) {
        outFile << rate[i] << endl;
    }
    outFile.close();

    // TODO 2: Display "Valid readings: " and "Junk skipped: ".
    cout << "Valid readings: " << count << endl;
    cout << "Junk skipped: " << bad << endl;

    // TODO 3: If count is 0, display "No valid readings!".
    //         Otherwise display the Average, Highest, Above average
    //         and Alerts (above 100) lines.
    if (count == 0) {
        cout << "No valid readings!" << endl;
    }
    else {
        int total = 0;
        int highest = rate[0];
        for (int i = 0; i < count; i++) {
            total = total + rate[i];
            if (rate[i] > highest) {
                highest = rate[i];
            }
        }

        double average = (double)total / count;

        int aboveAverage = 0;
        int alerts = 0;
        for (int i = 0; i < count; i++) {
            if (rate[i] > average) {
                aboveAverage++;
            }
            if (rate[i] > 100) {
                alerts++;
            }
        }

        cout << "Average: " << average << endl;
        cout << "Highest: " << highest << endl;
        cout << "Above average: " << aboveAverage << endl;
        cout << "Alerts (above 100): " << alerts << endl;
    }

    // TODO 4: Display "Stopped because: " followed by
    //         sentinel found, end of file or array full.
    cout << "Stopped because: ";
    if (reason == 1) {
        cout << "sentinel found" << endl;
    }
    else if (reason == 2) {
        cout << "end of file" << endl;
    }
    else {
        cout << "array full" << endl;
    }

    return 0;
}
