#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <fstream>
#include "book.cpp"
#include "fullTimeBook.cpp"
#include "partTimeBook.cpp"
#include "dataValidation.cpp"
#include "bookRepository.cpp"

// Class managing book
class bookManager : public bookRepository {
private:
    std::vector<Book*> books;
    const std::string filename = "book.dat";

    Book* findBookById(int id) {
        auto it = std::find_if(books.begin(), books.end(), [id](Book* books) {
            return book->getId() == id;
        });
        return (it != books.end()) ? *it : nullptr;
    }

    Book* findBookByTitle(const std::string& title) {
        auto it = std::find_if(books.begin(), books.end(), [&title](Book* books) {
            return book->getTitle() == title;
        });
        return (it != books.end()) ? *it : nullptr;
    }

    // Function to save all book to a file
    void saveAllBook() {
        std::ofstream ofs(filename, std::ios::binary);
        if (!ofs) {
            dataValidation::SetColor(12);
            std::cerr << "Error opening file for saving!" << std::endl;
            return;
        }
        for (const auto& book : books) {
            book->saveToFile(ofs);
        }
    }

    // Function to load all book from a file
    void loadAllBook() {
        std::ifstream ifs(filename, std::ios::binary);
        if (!ifs) {
            return;
        }
        while (ifs.peek() != EOF) {
            std::string type;
            std::getline(ifs, type);
            Book* book = nullptr;
            if (type == "FullTimeBook") {
                book = new FullTimeBook();
            } else if (type == "PartTimeBook") {
                book = new PartTimeBook();
            }
            if (book) {
                book->loadFromFile(ifs);
                book.push_back(book);
            }
        }
    }

public:
    // Constructor to load book from file on creation
    bookManager() {
        loadAllBook();
    }

    // Destructor to save book to file and clean up memory
    ~bookManager() {
        saveAllBook();
        for (auto book : books) {
            delete book;
        }
    }

    void addBook(const std::string& title, int id, const std::string& desc, int type) override {
        if (type == 1) {
            double price = dataValidation::getDoubleInput("Enter the total amount for the Full time book: ");
            books.push_back(new FullTimeBook(title, id, desc, price));
        } else if (type == 2) {
            double price = dataValidation::getDoubleInput("Enter the total amount for the Part time book: ");
            books.push_back(new PartTimeBook(title, id, desc, price));
        } else {
            dataValidation::SetColor(12);
            throw std::invalid_argument("Invalid Book type.");
        }
        saveAllBook();
        std::cout << "Book added successfully.\n";
    }

    void editBook(int id) override {
        Book* book = findBookById(id);
        if (book == nullptr) {
            dataValidation::SetColor(12);
            throw std::invalid_argument("Book not found");
        }

        std::string newTitle = dataValidation::getStringInput("Enter new book title: ");
        std::string newDesc = dataValidation::getStringInput("Enter new book description: ");

        book->setName(newTitle);
        book->setDob(newDesc);
        saveAllBook();
        std::cout << "Book updated successfully.\n";
    }

    void deleteBook(int id) override {
        auto it = std::find_if(books.begin(), books.end(), [id](Book* book) {
            return book->getId() == id;
        });

        if (it != books.end()) {
            char choice;
            do {
                std::cout << "Do you want to delete? (Y/N): ";
                std::cin >> choice;
                choice = toupper(choice);
                if (choice == 'Y') {
                    delete *it;
                    books.erase(it);
                    saveAllBook();
                    std::cout << "Book deleted successfully.\n";
                } else if (choice == 'N') {
                    std::cout << "Deletion canceled.\n";
                } else {
                    dataValidation::SetColor(12);
                    std::cout << "Invalid input. Please enter 'Y' or 'N'.\n";
                }
            } while (choice != 'Y' && choice != 'N');
        } else {
            dataValidation::SetColor(12);
            throw std::invalid_argument("Book not found");
        }
    }

    void viewBook() override {
        if (books.empty()) {
            dataValidation::SetColor(12);
            throw std::invalid_argument("No book available");
        }
        Book::displayHeader();
        for (const auto& book : books) {
            book->display();
            loadAllBook();
        }

        // Adding "press any key to conti   nue" functionality
        std::cout << "\nPress any key to continue...";
        std::cin.get();  // Waits for user to press any key
    }

    void searchBookByTitle(const std::string& title) override {
        Book* book = findBookByTitle(title);
        if (book == nullptr) {
            dataValidation::SetColor(12);
            throw std::invalid_argument("Book not found");
        } else {
            Book::displayHeader();
            book->display();
        }
        // Adding "press any key to continue" functionality
        std::cout << "\nPress any key to continue...";
        std::cin.get();  // Waits for user to press any key
    }
};