#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "fullTimeStudent.cpp"
#include "partTimeStudent.cpp"
#include "student.cpp"
#include <windows.h>

using namespace std;
// Utility class for data validation and input
class dataValidation {
public:
    // Validate the Id to ensure it's positive
    static void validateId(int id) {
        if (id <= 0) {
            throw std::invalid_argument("ID must be a positive integer.");
        }
    }
    
    // Get a string input from the user
    static std::string getStringInput(const std::string& prompt) {
        std::string input;
        std::cout << prompt;
        std::getline(std::cin, input);
        return input;
    }
    
    // Get an integer input from the user
    static int getIntInput(const std::string& prompt) {
        int input;
        std::cout << prompt;
        while (!(std::cin >> input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer: ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return input;
    }

    // Get an Double input from the user
    static double getDoubleInput(const std::string& prompt) {
        double input;
        std::cout << prompt;
        while (!(std::cin >> input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return input;
    }

    //Set Color
    static void SetColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    }
};