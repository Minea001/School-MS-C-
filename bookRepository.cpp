#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "fullTimeBook.cpp"
#include "partTimeBook.cpp"
#include "dataValidation.cpp"
#include "book.cpp"

class bookRepository {
public:
    virtual void addBook(const std::string& title, int id) = 0;
    virtual void editBook(int id) = 0;
    virtual void deleteBook(int id) = 0;
    virtual void viewBook() = 0;
    virtual void searchBookByTitle(const std::string& title) = 0;
    virtual ~bookRepository() = default;
};
