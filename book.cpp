#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <fstream>

// Base class representing a book
class Book {
protected:
    std::string title;
    std::string desc;
    int id;

public:
    Book() {}
    Book(const std::string& title, int id, const std::string& desc) : : title(title), id(id), desc(desc) {}

     // Virtual destructor
    virtual ~Book() {}

    // Pure virtual function to get the type of book
    virtual std::string getType() const = 0;

    // Getter functions
    int getId(){
        return id;
    }
    std::string getTitle(){
        return title;
    }
    std::string getDesc(){
        return desc;
    }

   // Setter functions
    void setId(int id){
        this->id = id;
    }
    void setTitle(std::string title){
        this->title = title;
    }
    void setDesc(std::string desc){
        this->desc = desc;
    }

    // Static function to display the header for book information
    static void displayHeader() {
        std::cout << "\n";
        std::cout << std::left << std::setw(20) << "Type"
                  << std::setw(15) << "Title"
                  << std::setw(15) << "Id"
                  << std::setw(15) << "Description"
                  << std::setw(15) << "Total" << std::endl;
        std::cout << std::string(90, '-') << std::endl;
    }

    // Virtual function to display student information
    virtual void display() const {
        std::cout << std::left << std::setw(20) << getType()
                  << std::setw(15) << title
                  << std::setw(15) << id
                  << std::setw(15) << desc
    }
    
    // Virtual function to save student information to a file
    virtual void saveToFile(std::ofstream& ofs) const {
        size_t titleSize = title.size();
        ofs.write(reinterpret_cast<const char*>(&titleSize), sizeof(titleSize));
        ofs.write(title.c_str(), titleSize);

        ofs.write(reinterpret_cast<const char*>(&id), sizeof(id));

        size_t descSize = desc.size();
        ofs.write(reinterpret_cast<const char*>(&descSize), sizeof(descSize));
        ofs.write(desc.c_str(), descSize);
    }

    // Virtual function to load book information from a file
    virtual void loadFromFile(std::ifstream& ifs) {
        size_t titleSize;
        ifs.read(reinterpret_cast<char*>(&titleSize), sizeof(titleSize));
        title.resize(titleSize);
        ifs.read(&title[0], titleSize);

        ifs.read(reinterpret_cast<char*>(&id), sizeof(id));

        size_t descSize;
        ifs.read(reinterpret_cast<char*>(&descSize), sizeof(descSize));
        desc.resize(descSize);
        ifs.read(&desc[0], descSize);

    }
};