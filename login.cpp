#include <iostream>
#include<vector>
#include<string>
#include <fstream>
#include <iomanip>
#include "user.cpp"
#include "studentApplication.cpp"
#include "studentManager.cpp"
#include "bookApplication.cpp"
#include "bookManager.cpp"

using namespace std;

class Login {
  // instant class
  studentManager studentmanager;
  bookManager bookmanager;
 
private:
    vector<User> users;
    string usersFile = "users.dat";

public: 
// call method load user to class login
  Login() {
    loadUsers();
  }

  void loadUsers() {
    ifstream file(usersFile, ios::binary);
    if (file.is_open()) {
      User user;
      while (file.read((char*)&user, sizeof(User)))
      {
        users.push_back(user);
      }
      file.close();
    }
  }

  void saveUsers() {
    ofstream file(usersFile, ios::binary | ios::trunc);
    if (file.is_open()) {
      for (const auto& user : users) {
        file.write((char*)&user, sizeof(User));
      }
      file.close();
    } else {
      cerr << usersFile << "could not open for writting" << endl;
    }
  }

  void addUser() {
    string username, password, role;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;
    cout << "Enter role (admin/user): ";
    cin >> role;

    users.push_back(User(username, password, role));
    saveUsers();
    cout << "User added successfully!" << endl;
  }

  bool authenticate(const string& username, const string& password, User& authenticateUser) {
    for (const auto& user : users) {
      if (user.getUsername() == username && user.getPassword) {
        authenticateUser = user;
        return true;
      }
    }
    return false;
  }

  void login() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    User authenticatedUser; // instant class User

    if (authenticate(username, password, authenticatedUser)) {
        cout << "Login successful! Role: " << authenticatedUser.getRole() << endl;
        if (authenticatedUser.getRole() == "admin") {
            system("cls");
            adminMenu(); // call admin menu
        } else {
            system("cls"); // clear screen
            userMenu(); // call user menu
        }
    } else {
        cout << "Invalid username or password." << endl;
    }
  }

  void regist() {
    string username, password, role;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter role (admin/user): ";
    cin >> role;

    users.push_back(User(username, password, role));
    saveUsers();
    cout << "User saved successfully!" << endl;
  }

  void userMenu() {
    int choice;
    do {
        cout << "\t[=================]\n";
          cout << "\t   Admin Menu\n";
          cout << "\t[=================]\n";
        cout << "\n1. View Student\n";
        cout << "2. View Book\n";
        cout << "3. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                studentmanager.viewStudent();
                system("cls");
                break;
            case 2:
                bookmanager.viewBook();
                system("cls");
                break;
            case 3:
                menu();
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 2);
  }

  void adminMenu() {
      enum MainMenu {EXIT, STUDENT, BOOK};
      int choice;
      cout.setf(ios::fixed | ios::showpoint);
      cout << setprecision(2);

      do {
          system("cls");
          cout << "\t[=================]\n";
          cout << "\t   Admin Menu\n";
          cout << "\t[=================]\n";
          cout << "\n1. Student Management\n";
          cout << "2. Book Management\n";
          cout << "3. Logout\n";
          choice = dataValidation::getIntInput("Enter your choice: ");
          switch (choice) {
              case STUDENT: {
                  studentApplication studentApp;
                  studentApp.run();
                  break;
              }
              case BOOK: {
                bookApplication bookApp;
                bookApp.run();
              }
              case EXIT:
                  menu();
                  break;
              default:
                  cout << "Invalid input" << endl;
                  cout << "\a";
          }
      } while (choice != EXIT);
  }
  
  void viewUsers() {
    cout << "\nRegistered Users: \n";
    for (const auto& user : users) {
      cout << "Username: " << user.getUsername() << " / Role: " << user.getRole() << endl;
    }
  }

  void menu() {
        int choice;
        do {
               cout << "\t[=================]\n";
          cout << "\t   Main Menu\n";
          cout << "\t[=================]\n";
            cout << "\n1. Login\n";
            cout << "2. Register\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    login();  
                    break;
                case 2:
                    regist();
                    break;
                case 0:
                    cout << "Exiting program." << endl;
                    break;
                default:
                    cout << "Invalid ! please try again." << endl;
            }
        } while (choice != 0);
    }

};