// main.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

// StateClimate.h
class StateClimate {
    private:
        int fips;
        int year;
        double temp;
        double tempc;

    public:
        // Constructor
        StateClimate(int f, int y, double t, double tc);

        // Getters
        int getFips() const;
        int getYear() const;
        double getTemp() const;
        double getTempC() const;

        // Setters
        void setFips(int f);
        void setYear(int y);
        void setTemp(double t);
        void setTempC(double tc);

        // Display function
        void display() const;
};

// StateClimate.cpp
StateClimate::StateClimate(int f, int y, double t, double tc) : fips(f), year(y),
temp(t), tempc(tc) {}

// Getters
int StateClimate::getFips() const { return fips; }
int StateClimate::getYear() const { return year; }
double StateClimate::getTemp() const { return temp; }
double StateClimate::getTempC() const { return tempc; }

// Setters
void StateClimate::setFips(int f) { fips = f; }
void StateClimate::setYear(int y) { year = y; }
void StateClimate::setTemp(double t) { temp = t; }
void StateClimate::setTempC(double tc) { tempc = tc; }

// Display function
void StateClimate::display() const {
    std::cout << "FIPS: " << fips << ", Year: " << year << ", Temp (F): " << temp << ", Temp (C): " << tempc << std::endl;
}

// Binary Search function (fixed)
int binarySearch(const std::vector<StateClimate> &data, int keyFips) {
    int left = 0;
    int right = data.size() - 1;
    int mid;
    int result = -1;

    while (left <= right) {
        mid = left + (right - left) / 2;
        if (data[mid].getFips() == keyFips) {
            result = mid;
            right = mid - 1; // Keep searching for the first occurrence
        } else if (data[mid].getFips() < keyFips) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result; // Returns the first occurrence index or -1 if not found
}

// Function to display all entries with matching FIPS
void displayFipsEntries(const std::vector<StateClimate> &data, int keyFips) {
    int index = binarySearch(data, keyFips);

    // Display error message if FIPS code is not found
    if (index == -1) {
        std::cout << "FIPS code not found." << std::endl;
        return;
    }

    // Find the first occurrence of keyFips
    while (index > 0 && data[index - 1].getFips() == keyFips) {
        index--;
    }

    // Print all occurrences
    while (index < data.size() && data[index].getFips() == keyFips) {
        data[index].display();
        index++;
    }
}

int main() {
    std::vector<StateClimate> climateData;
    std::ifstream file("climdiv_state_year.csv");
    
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(file, line); // Skip header line
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int fips, year;
        double temp, tempc;
        char comma;

        ss >> fips >> comma >> year >> comma >> temp >> comma >> tempc;
        climateData.emplace_back(fips, year, temp, tempc);
    }

    file.close();

    // Allow user to search for a FIPS code
    int searchFips;
    std::cout << "Enter a FIPS number to search: ";
    std::cin >> searchFips;
    displayFipsEntries(climateData, searchFips);

    return 0;
}
