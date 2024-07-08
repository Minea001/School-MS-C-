#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "student.cpp"

// Derived class  
class FullTimeStudent : public Student {
    private:
        double price;

    public:
    FullTimeStudent() : Student("", 0, "", ""), price(0) {}

    FullTimeStudent(const std::string& name, int id, const std::string& dob, const std::string& department, double price)
        : Student(name, id, dob, department), price(price) {
             applyDiscount(50); // Applying a 50% discount to the price
        }

    // Method to apply a discount to the price
    void applyDiscount(double discountPercentage) {
        price -= price * (discountPercentage / 100.0);
    }

    // Getter function for price
    double getPrice() const {
        return price;
    }

    // Override the getType function to return the type of student
    std::string getType() const override {
        return "FullTimeStudent";
    }

    // Override the display function to include price and discount information
    void display() const override {
        Student::display(); 
        std::cout << std::right << std::setw(20)
                  << std::setw(0) << price << "$" << " Discount 50%" << std::endl;
    }

    // Override the saveToFile function to include price information
    virtual void saveToFile(std::ofstream& ofs) const override {
        Student::saveToFile(ofs); // Call the base class saveToFile function
        ofs.write(reinterpret_cast<const char*>(&price), sizeof(price));
    }

    // Override the loadFromFile function to load price information
    virtual void loadFromFile(std::ifstream& ifs) override {
        Student::loadFromFile(ifs); // Call the base class loadFromFile function
        ifs.read(reinterpret_cast<char*>(&price), sizeof(price));
    }
};