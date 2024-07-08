#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "partTimeStudent.cpp"
#include "fullTimeStudent.cpp"
#include "bookManager.cpp"
#include "dataValidation.cpp"

// Class to run the book management application
class bookApplication {
private:
    // Display the menu for book management
    void displayMenu() {

        std::cout << "\n\t[=================================]\n";
        std::cout << "\t       Book Manager Menu\n";
        std::cout << "\t[=================================]\n";
        std::cout << "\n1. Add Book\n";
        std::cout << "2. Edit Book\n";
        std::cout << "3. Delete Book\n";
        std::cout << "4. View Book\n";
        std::cout << "5. Search Book\n";
        std::cout << "6. Back to Main Menu\n";
        std::cout << std::endl;
    }
    
public:
    enum MenuChoice {
        ADD_BOOK= 1,
        EDIT_BOOK,
        DELETE_BOOK,
        VIEW_BOOK,
        SEARCH_BOOK,
        EXIT
    };

    // Run the Book management application
    void run() {
        bookManager bookmanager;
        int choice;
        bool done = false;
        while (!done) {
            displayMenu();
            choice = dataValidation::getIntInput("Enter your choice: ");
            try {
                switch (choice) {
                    case ADD_BOOK: {
                        std::string title, desc;
                        int id;
                        int type;

                        title = dataValidation::getStringInput("Enter book title: ");
                        desc = dataValidation::getStringInput("Enter book description: ");
                        id = dataValidation::getIntInput("Enter book id: ");                 
                        dataValidation::validateId(id);
                        type = dataValidation::getIntInput("Enter 1 for full-time, 2 for part-time: ");
                        bookmanager.addBook(title, id, desc, type);
                        break;
                    }
                    case EDIT_BOOK: {
                        int id;
                        id = dataValidation::getIntInput("Enter book id: ");
                        dataValidation::validateId(id);
                        bookmanager.editBook(id);
                        break;
                    }
                    case DELETE_BOOK: {
                        int id;
                        id = dataValidation::getIntInput("Enter book id: ");
                        dataValidation::validateId(id);
                        bookmanager.deleteBook(id);
                        break;
                    }
                    case VIEW_BOOK: {
                        bookmanager.viewBook();
                        break;
                    }
                    case SEARCH_BOOK: {
                        std::string title;
                        title = dataValidation::getStringInput("Enter book title: ");
                        bookmanager.SearchBookByTitle(title);
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