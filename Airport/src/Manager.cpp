#include "Manager.h"
#include <iostream>
#include <sstream>
#include <sqlite3.h>

#include "Manager.h"
#include "sqlite3.h"
#include <iostream>

// Updated constructor for Manager class
Manager::Manager(int id, const string& name, const string& gender, int age, const string& username, const string& password, const string& phoneNumber, double salary)
    : Employee(id, name, gender, age, username, password, phoneNumber, salary) {
    // Additional initialization if needed
}

// Destructor
Manager::~Manager() {
    // Cleanup if needed
}

bool Manager::addEmployee(sqlite3* db, const string& name, const string& gender, int age, const string& username, const string& password, const string& role)
{
    stringstream query;
    query << "INSERT INTO Employees (name, gender, age, username, password, role) VALUES ('"
          << name << "', '" << gender << "', " << age << ", '" << username << "', '" << password << "', '" << role << "');";

    char* errorMessage = nullptr;
    int rc = sqlite3_exec(db, query.str().c_str(), nullptr, nullptr, &errorMessage);

    if (rc == SQLITE_OK) {
        cout << "Employee added successfully." << endl;
        return true;
    } else {
        cout << "Error adding employee: " << errorMessage << endl;
        sqlite3_free(errorMessage);
        return false;
    }
}

bool Manager::removeEmployee(sqlite3* db, int employeeId)
{
    stringstream query;
    query << "DELETE FROM Employees WHERE id = " << employeeId << ";";

    char* errorMessage = nullptr;
    int rc = sqlite3_exec(db, query.str().c_str(), nullptr, nullptr, &errorMessage);

    if (rc == SQLITE_OK) {
        cout << "Employee removed successfully." << endl;
        return true;
    } else {
        cout << "Error removing employee: " << errorMessage << endl;
        sqlite3_free(errorMessage);
        return false;
    }
}

void Manager::viewAllEmployees(sqlite3* db)
{
    string query = "SELECT id, name, role FROM Employees;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        cout << "Employee List:" << endl;
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int id = sqlite3_column_int(stmt, 0);
            string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            string role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

            cout << "ID: " << id << ", Name: " << name << ", Role: " << role << endl;
        }
    }
    else
    {
        cout << "Error fetching employees: " << sqlite3_errmsg(db) << endl;
    }
    sqlite3_finalize(stmt);
}

void Manager::displayAvailableFlights(sqlite3* db)
{
    string query = "SELECT id, flight_number, departure, destination, departure_time, arrival_time FROM Flights;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        cout << "Available Flights:" << endl;
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int flightId = sqlite3_column_int(stmt, 0);
            string flightNumber = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            string departure = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            string destination = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            string departureTime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            string arrivalTime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

            cout << "Flight ID: " << flightId << ", Flight Number: " << flightNumber
                 << ", From: " << departure << " To: " << destination
                 << ", Departure: " << departureTime << ", Arrival: " << arrivalTime << endl;
        }
    }
    else
    {
        cout << "Error fetching flights: " << sqlite3_errmsg(db) << endl;
    }
    sqlite3_finalize(stmt);
}
