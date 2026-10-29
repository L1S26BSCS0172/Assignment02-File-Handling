/*
 * Name         : Muhammad Faizan
 * Reg No       : L1S26BSCS0172
 * Assignment   : O2 - File Handling
 * Question     : Q1 - Stock Report (Debugging)
 */

 // FIX 1: <fstream> is needed to use ifstream and ofstream.
#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ifstream inFile("stock.txt");
    if (!inFile) {
        cout << "stock.txt not found!" << endl;
        return 1;
    }

    // FIX 2: ofstream alone overwrites the existing file;
    // ios::app appends new lines and preserves the old data.
    ofstream reorder("reorder.txt", ios::app);

    char code[10];
    int qty, count = 0, low = 0;
    double price;

    // FIX 3: total must be double to preserve decimal values.
    double total = 0;

    // FIX 4: Read and discard the header before reading items.
    inFile.ignore(1000, '\n');

    while (count < 50 && inFile >> code >> qty >> price) {
        count++;

        // FIX 5: Use += to accumulate each item's value.
        total += qty * price;

        if (qty < 10) {
            // FIX 6: Separate code and quantity with a space,
            // and write each reorder entry on its own line.
            reorder << code << " " << qty << '\n';
            low++;
        }
    }

    inFile.close();
    reorder.close();

    cout << "Items: " << count << endl;
    cout << "Total stock value: " << total << endl;
    cout << "Low stock items: " << low << endl;

    return 0;
}