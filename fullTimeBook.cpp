#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "book.cpp"

// Derived class  
class FullTimeBook : public Book {
    private:
        double price;

    public:
    FullTimeBook() : Book("", 0, ""), price(0) {}

    FullTimeBook(const std::string& title, int id, const std::string& desc, double price)
        : Book(title, id, desc), price(price) {
             applyDiscount(30); // Applying a 30% discount to the price
        }

    // Method to apply a discount to the price
    void applyDiscount(double discountPercentage) {
        price -= price * (discountPercentage / 100.0);
    }

    // Getter function for price
    double getPrice() const {
        return price;
    }

    // Override the getType function to return the type of book
    std::string getType() const override {
        return "FullTimeBook";
    }

    // Override the display function to include price and discount information
    void display() const override {
        Book::display(); 
        std::cout << std::right << std::setw(20)
                  << std::setw(0) << price << "$" << " Discount 30%" << std::endl;
    }

    // Override the saveToFile function to include price information
    virtual void saveToFile(std::ofstream& ofs) const override {
        Book::saveToFile(ofs); // Call the base class saveToFile function
        ofs.write(reinterpret_cast<const char*>(&price), sizeof(price));
    }

    // Override the loadFromFile function to load price information
    virtual void loadFromFile(std::ifstream& ifs) override {
        Book::loadFromFile(ifs); // Call the base class loadFromFile function
        ifs.read(reinterpret_cast<char*>(&price), sizeof(price));
    }
};