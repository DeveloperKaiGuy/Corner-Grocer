/*
 * Kai Amos
 * 8/13/2025
 * CS-210
*/


#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>
#include <limits>

using namespace std;

// Function to read file and store frequencies
map<string, int> LoadFrequencies(const string& filename) {
    map<string, int> freqMap;
    ifstream inFile(filename);
    if (!inFile) {
        // If the file fails to open, display this error message.
        cerr << "Error: Could not open file " << filename << endl;
        return freqMap;
    }

    string item;
    // Reading each word from the file and increment the count based on the word's frequency.
    while (inFile >> item) {
        ++freqMap[item];
    }
    // Close the file and return the map of word counts/frequencies
    inFile.close();
    return freqMap;
}

// Option 1: Search for a specific word
void SearchWordFrequency(const map<string, int>& freqMap) {
    string searchWord;
    cout << "Enter the item/word to search: ";
    cin >> searchWord;

    auto it = freqMap.find(searchWord);
    if (it != freqMap.end()) {
        // display the count if the word is in the file
        cout << searchWord << " appears " << it->second << " times.\n";
    } else {
        // Return message if the word isnt in the file
        cout << searchWord << " not found in records.\n";
    }
}

// Option 2: Display all word frequencies
void DisplayAllFrequencies(const map<string, int>& freqMap) {
    for (const auto& pair : freqMap) {
        cout << pair.first << " " << pair.second << "\n";
    }
}

// Option 3: Display a histogram of all word frequencies
void DisplayHistogram(const map<string, int>& freqMap) {
    for (const auto& pair : freqMap) {
        cout << setw(12) << left << pair.first << " ";
        // Print one asterisk for each time the word is found
        for (int i = 0; i < pair.second; ++i) {
            cout << "*";
        }
        cout << "\n";
    }
}

// Save to frequency.dat file
void SaveToFile(const map<string, int>& freqMap, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        // Error message for if the file couldn't be created
        cerr << "Error: Could not create file " << filename << endl;
        return;
    }

    // Writing each item and the respective frequency to the file
    for (const auto& pair : freqMap) {
        outFile << pair.first << " " << pair.second << "\n";
    }
    outFile.close();
}

int main() {
    const string inputFileName = "CS210_Project_Three_Input_File.txt";
    const string backupFileName = "frequency.dat";

    // Load the data from the file
    map<string, int> frequencies = LoadFrequencies(inputFileName);

    // Error message for if the data file was empty
    if (frequencies.empty()) {
        cerr << "No data loaded. Exiting.\n";
        return 1;
    }

    SaveToFile(frequencies, backupFileName);


    int choice = 0;
    while (true) {
        cout << "\n===== MENU =====\n";
        cout << "1. Search for a specific item frequency\n";
        cout << "2. Display all item frequencies\n";
        cout << "3. Display histogram of items\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        // Validation for the input choice; discards the bad input and clears the error flag, then outputs the error message
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 4.\n";
            continue;
        }

        // Processing the menu choice based on what it is
        switch (choice) {
        case 1:
            SearchWordFrequency(frequencies);
            break;
        case 2:
            DisplayAllFrequencies(frequencies);
            break;
        case 3:
            DisplayHistogram(frequencies);
            break;
        case 4:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice. Please select between 1 and 4.\n";
        }
    }

    return 0;
}
