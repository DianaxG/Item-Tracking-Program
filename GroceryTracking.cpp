/*
Diana Galvez Mendez
CS210
Project 3: Grocery Tracking
April 21st, 2024
This program will allow a user to retrieve data saved in a txt file and give the user options to display the data, 
and the item frequencies will be saved into a new back-up file*/



#include <iostream>
#include <fstream>
#include <map>
#include <string>

class ItemTracker {
private:
    // Map will store the item-frequency pairs
    std::map<std::string, int> itemFrequency; 

public:
    // This function will update the item frequency based on the input file
    void updateFrequencyFromFile(const std::string& filename) {
        std::ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return;
        }

        std::string item;
        while (inputFile >> item) {
            itemFrequency[item]++; // This will increment frequency by 1
        }
        inputFile.close();
    }

    // This function will retrieve the frequency of a specific item
    int getFrequency(const std::string& item) const {
        return itemFrequency.count(item) ? itemFrequency.at(item) : 0;
    }

    // This function willprint out the list with numbers representing frequency of all items
    void printListWithFrequency() const {
        for (const auto& pair : itemFrequency) {
            std::cout << pair.first << " " << pair.second << std::endl;
        }
    }

    // This function will print out a histogram of item frequencies
    void printHistogram() const {
        for (const auto& pair : itemFrequency) {
            std::cout << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                std::cout << "*"; // it'll print out the frequencies by using asterisks 
            }
            std::cout << std::endl;
        }
    }

    // This function will save item frequency data into our backup file
    void saveToBackup(const std::string& filename) const {
        std::ofstream backupFile(filename);
        if (!backupFile.is_open()) {
            std::cerr << "Error: Unable to create backup file " << filename << std::endl;
            return;
        }

        for (const auto& pair : itemFrequency) {
            backupFile << pair.first << " " << pair.second << std::endl;
        }
        backupFile.close();
    }
};

int main() {
    ItemTracker tracker;
    tracker.updateFrequencyFromFile("CS210_Project_Three_Input_File.txt");

    int choice;
    do {
        std::cout << "Menu Options:" << std::endl;
        std::cout << "1. Look for an item" << std::endl;
        std::cout << "2. Print frequency list" << std::endl;
        std::cout << "3. Print histogram" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string item;
            std::cout << "Enter the item you wish to look for: ";
            std::cin >> item;
            int frequency = tracker.getFrequency(item);
            std::cout << "Frequency of " << item << ": " << frequency << std::endl;
            break;
        }
        case 2:
            tracker.printListWithFrequency();
            break;
        case 3:
            tracker.printHistogram();
            break;
        case 4:
            tracker.saveToBackup("frequency.dat");
            std::cout << "Exiting program." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 4." << std::endl;
        }
    } while (choice != 4);

    return 0;
}
