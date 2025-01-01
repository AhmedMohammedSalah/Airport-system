// Manager.h
#ifndef MANAGER_H
#define MANAGER_H

#include "Empolyee.h"
#include <string>

using namespace std;

class Manager : public Employee {
public:
    // Updated Constructor to match Employee's constructor
    Manager(int id, const string& name, const string& gender, int age, const string& username, const string& password, const string& phoneNumber, double salary);
    ~Manager();

    // Method to add a new employee to the database
    bool addEmployee(sqlite3* db, const string& name, const string& gender, int age, const string& username, const string& password, const string& role);

    // Method to remove an employee from the database
    bool removeEmployee(sqlite3* db, int employeeId);

    // Method to view all employees in the system
    void viewAllEmployees(sqlite3* db);

    // Method to display available flights
    void displayAvailableFlights(sqlite3* db);
};

#endif // MANAGER_H
