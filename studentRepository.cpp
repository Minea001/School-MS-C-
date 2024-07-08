#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "FullTimeStudent.cpp"
#include "PartTimeStudent.cpp"
#include "student.cpp"
#include "dataValidation.cpp"

class studentRepository {
public:
    virtual void addStudent(const std::string& name, int id) = 0;
    virtual void editStudent(int id) = 0;
    virtual void deleteStudent(int id) = 0;
    virtual void viewStudent() = 0;
    virtual void searchStudentByName(const std::string& name) = 0;
    virtual ~studentRepository() = default;
};
