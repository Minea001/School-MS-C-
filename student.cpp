#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <fstream>

// Base class representing a student
class Student {
protected:
    std::string name;
    std::string dob;
    std::string department;
    int id;

public:
    Student() {}
    Student(const std::string& name, int id, const std::string& dob, const std::string& department) : : name(name), id(id), dob(dob), department(department) {}

     // Virtual destructor
    virtual ~Student() {}

    // Pure virtual function to get the type of student
    virtual std::string getType() const = 0;

    // Getter functions
    int getId(){
        return id;
    }
    std::string getName(){
        return name;
    }
    std::string getDob(){
        return dob;
    }
    std::string getDepartment(){
        return department;
    }

   // Setter functions
    void setId(int id){
        this->id = id;
    }
    void setName(std::string name){
        this->name = name;
    }
    void setDob(std::string dob){
        this->dob = dob;
    }
    void setDepartment(std::string department){
        this->department = department;
    }

    // Static function to display the header for student information
    static void displayHeader() {
        std::cout << "\n";
        std::cout << std::left << std::setw(20) << "Type"
                  << std::setw(15) << "Name"
                  << std::setw(15) << "Id"
                  << std::setw(15) << "DOB"
                  << std::setw(15) << "Department"
                  << std::setw(15) << "Total" << std::endl;
        std::cout << std::string(90, '-') << std::endl;
    }

    // Virtual function to display student information
    virtual void display() const {
        std::cout << std::left << std::setw(20) << getType()
                  << std::setw(15) << name
                  << std::setw(15) << id
                  << std::setw(15) << dob
                  << std::setw(15) << department
    }
    
    // Virtual function to save student information to a file
    virtual void saveToFile(std::ofstream& ofs) const {
        size_t nameSize = name.size();
        ofs.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
        ofs.write(name.c_str(), nameSize);
        ofs.write(reinterpret_cast<const char*>(&id), sizeof(id));
        size_t dobSize = dob.size();
        ofs.write(reinterpret_cast<const char*>(&dobSize), sizeof(dobSize));
        ofs.write(dob.c_str(), dobSize);
        size_t departmentSize = department.size();
        ofs.write(reinterpret_cast<const char*>(&departmentSize), sizeof(departmentSize));
        ofs.write(department.c_str(), departmentSize);
    }

    // Virtual function to load student information from a file
    virtual void loadFromFile(std::ifstream& ifs) {
        size_t nameSize;
        ifs.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        name.resize(nameSize);
        ifs.read(&name[0], nameSize);

        ifs.read(reinterpret_cast<char*>(&id), sizeof(id));

        size_t dobSize;
        ifs.read(reinterpret_cast<char*>(&dobSize), sizeof(dobSize));
        dob.resize(dobSize);
        ifs.read(&dob[0], dobSize);

        size_t deparmentSize;
        ifs.read(reinterpret_cast<char*>(&deparmentSize), sizeof(deparmentSize));
        department.resize(deparmentSize);
        ifs.read(&department[0], deparmentSize);

    }
};