#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "partTimeStudent.cpp"
#include "fullTimeStudent.cpp"
#include "studentManager.cpp"
#include "dataValidation.cpp"

// Class to run the book management application
class studentApplication {
private:
    // Display the menu for book management
    void displayMenu() {

        std::cout << "\n\t[=================================]\n";
        std::cout << "\t       Student Manager Menu\n";
        std::cout << "\t[=================================]\n";
        std::cout << "\n1. Add Student\n";
        std::cout << "2. Edit Student\n";
        std::cout << "3. Delete Student\n";
        std::cout << "4. View Student\n";
        std::cout << "5. Search Student\n";
        std::cout << "6. Back to Main Menu\n";
        std::cout << std::endl;
    }
    
public:
    enum MenuChoice {
        ADD_STUDENT= 1,
        EDIT_STUDENT,
        DELETE_STUDENT,
        VIEW_STUDENT,
        SEARCH_STUDENT,
        EXIT
    };

    // Run the book management application
    void run() {
        studentManager studentmanager;
        int choice;
        bool done = false;
        while (!done) {
            displayMenu();
            choice = dataValidation::getIntInput("Enter your choice: ");
            try {
                switch (choice) {
                    case ADD_STUDENT: {
                        std::string name, dob, department;
                        int id;
                        int type;

                        name = dataValidation::getStringInput("Enter student name: ");
                        dob = dataValidation::getStringInput("Enter student date of birth: ");
                        department = name = dataValidation::getStringInput("Enter student's department: ");
                        id = dataValidation::getIntInput("Enter student id: ");                 
                        dataValidation::validateId(id);
                        type = dataValidation::getIntInput("Enter 1 for full-time, 2 for part-time: ");
                        studentmanager.addStudent(name, id, dob, department, type);
                        break;
                    }
                    case EDIT_STUDENT: {
                        int id;
                        id = dataValidation::getIntInput("Enter student id: ");
                        dataValidation::validateId(id);
                        studentmanager.editStudent(id);
                        break;
                    }
                    case DELETE_STUDENT: {
                        int id;
                        id = dataValidation::getIntInput("Enter student id: ");
                        dataValidation::validateId(id);
                        studentmanager.deleteStudent(id);
                        break;
                    }
                    case VIEW_STUDENT: {
                        studentmanager.viewStudent();
                        break;
                    }
                    case SEARCH_STUDENT: {
                        std::string name;
                        name = dataValidation::getStringInput("Enter student name: ");
                        studentmanager.SearchStudentByName(name);
                        break;
                    }
                    case EXIT:
                        done = true;
                        break;
                    default:
                        std::cout << "Invalid choice. Please try again.\n";
                }
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
    }
};