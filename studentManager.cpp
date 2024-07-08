#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <fstream>
#include "student.cpp"
#include "fullTimeStudent.cpp"
#include "partTimeStudent.cpp"
#include "dataValidation.cpp"
#include "studentRepository.cpp"

// Class managing student
class studentManager : public studentRepository {
private:
    std::vector<Student*> students;
    const std::string filename = "student.dat";

    Student* findStudentById(int id) {
        auto it = std::find_if(students.begin(), students.end(), [id](Student* students) {
            return student->getId() == id;
        });
        return (it != students.end()) ? *it : nullptr;
    }

    Student* findStudentByName(const std::string& name) {
        auto it = std::find_if(students.begin(), students.end(), [&name](Student* students) {
            return student->getName() == name;
        });
        return (it != students.end()) ? *it : nullptr;
    }

    // Function to save all student to a file
    void saveAllStudent() {
        std::ofstream ofs(filename, std::ios::binary);
        if (!ofs) {
            dataValidation::SetColor(12);
            std::cerr << "Error opening file for saving!" << std::endl;
            return;
        }
        for (const auto& student : students) {
            student->saveToFile(ofs);
        }
    }

    // Function to load all students from a file
    void loadAllStudent() {
        std::ifstream ifs(filename, std::ios::binary);
        if (!ifs) {
            return;
        }
        while (ifs.peek() != EOF) {
            std::string type;
            std::getline(ifs, type);
            Student* student = nullptr;
            if (type == "FullTimeStudent") {
                student = new FullTimeStudent();
            } else if (type == "PartTimeStudent") {
                student = new PartTimeStudent();
            }
            if (student) {
                student->loadFromFile(ifs);
                students.push_back(student);
            }
        }
    }

public:
    // Constructor to load students from file on creation
    studentManager() {
        loadAllStudent();
    }

    // Destructor to save students to file and clean up memory
    ~studentManager() {
        saveAllStudent();
        for (auto student : students) {
            delete student;
        }
    }

    void addStudent(const std::string& name, int id, const std::string& dob,const std::string& department, int type) override {
        if (type == 1) {
            double price = dataValidation::getDoubleInput("Enter the total amount for the Full time student: ");
            students.push_back(new FullTimeStudent(name, id, phone, address, price));
        } else if (type == 2) {
            double price = dataValidation::getDoubleInput("Enter the total amount for the Part time student: ");
            students.push_back(new PartTimeStudent(name, id, phone, address, price));
        } else {
            dataValidation::SetColor(12);
            throw std::invalid_argument("Invalid Student type.");
        }
        saveAllStudent();
        std::cout << "Student added successfully.\n";
    }

    void editStudent(int id) override {
        Student* student = findStudentById(id);
        if (student == nullptr) {
            dataValidation::SetColor(12);
            throw std::invalid_argument("Student not found");
        }

        std::string newName = dataValidation::getStringInput("Enter new student name: ");
        std::string newDob = dataValidation::getStringInput("Enter new student dob: ");
        std::string newDepartment = dataValidation::getStringInput("Enter new student department: ");

        student->setName(newName);
        student->setDob(newDob);
        student->setDepartment(newDepartment);
        saveAllStudent();
        std::cout << "Student updated successfully.\n";
    }

    void deleteStudent(int id) override {
        auto it = std::find_if(students.begin(), students.end(), [id](Student* student) {
            return student->getId() == id;
        });

        if (it != students.end()) {
            char choice;
            do {
                std::cout << "Do you want to delete? (Y/N): ";
                std::cin >> choice;
                choice = toupper(choice);
                if (choice == 'Y') {
                    delete *it;
                    students.erase(it);
                    saveAllStudent();
                    std::cout << "Student deleted successfully.\n";
                } else if (choice == 'N') {
                    std::cout << "Deletion canceled.\n";
                } else {
                    dataValidation::SetColor(12);
                    std::cout << "Invalid input. Please enter 'Y' or 'N'.\n";
                }
            } while (choice != 'Y' && choice != 'N');
        } else {
            dataValidation::SetColor(12);
            throw std::invalid_argument("Student not found");
        }
    }

    void viewStudent() override {
        if (students.empty()) {
            dataValidation::SetColor(12);
            throw std::invalid_argument("No student available");
        }
        Student::displayHeader();
        for (const auto& student : students) {
            student->display();
            loadAllStudent();
        }

        // Adding "press any key to conti   nue" functionality
        std::cout << "\nPress any key to continue...";
        std::cin.get();  // Waits for user to press any key
    }

    void searchStudentByName(const std::string& name) override {
        Student* student = findStudentByName(name);
        if (student == nullptr) {
            dataValidation::SetColor(12);
            throw std::invalid_argument("Student not found");
        } else {
            Student::displayHeader();
            student->display();
        }
        // Adding "press any key to continue" functionality
        std::cout << "\nPress any key to continue...";
        std::cin.get();  // Waits for user to press any key
    }
};