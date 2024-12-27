#include <iostream>
#include <Person.h>
#include "sqlite3.h"

using namespace std;

void initializeDatabase(sqlite3* db) {
    const char* createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS Persons (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            gender TEXT NOT NULL,
            age INTEGER NOT NULL,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL
        );
    )";

    char* errorMessage = nullptr;
    int rc = sqlite3_exec(db, createTableQuery, nullptr, nullptr, &errorMessage);

    if (rc != SQLITE_OK) {
        cout << "Error creating table: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    } else {
        cout << "Database initialized successfully." << endl;
    }
}

void insertSampleData(sqlite3* db) {
    const char* insertDataQuery = R"(
        INSERT OR IGNORE INTO Persons (name, gender, age, username, password)
        VALUES
        ('Alice', 'Female', 30, 'alice123', 'pass123'),
        ('Bob', 'Male', 35, 'bob123', 'pass456');
    )";

    char* errorMessage = nullptr;
    int rc = sqlite3_exec(db, insertDataQuery, nullptr, nullptr, &errorMessage);

    if (rc != SQLITE_OK) {
        cout << "Error inserting data: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    } else {
        cout << "Sample data inserted successfully." << endl;
    }
}

int main() {
    // Open SQLite database (creates file if it doesn't exist)
    sqlite3* db;
    int rc = sqlite3_open("airport_system.db", &db);
    if (rc != SQLITE_OK) {
        cout << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        return 1;
    }

    // Initialize the database and insert sample data
    initializeDatabase(db);
    insertSampleData(db);
// Test login with valid credentials
    cout << "Testing login with valid credentials:" << endl;
    Person validUser = Person::login(db, "alice123", "pass123");
    if (validUser.getId() != -1) {
        cout << "Login successful! Welcome, " << validUser.getName() << "." << endl;
        cout << "Details: " << endl;
        cout << "ID: " << validUser.getId() << endl;
        cout << "Name: " << validUser.getName() << endl;
        cout << "Gender: " << validUser.getGender() << endl;
        cout << "Age: " << validUser.getAge() << endl;
        cout << "Username: " << validUser.getUsername() << endl;
    } else {
        cout << "Invalid login attempt." << endl;
    }

    // Test login with invalid credentials
    cout << "\nTesting login with invalid credentials:" << endl;
    Person invalidUser = Person::login(db, "bob123", "wrongpass");
    if (invalidUser.getId() != -1) {
        cout << "Login successful! Welcome, " << invalidUser.getName() << "." << endl;
    } else {
        cout << "Invalid login attempt." << endl;
    }

    // Close the database
    sqlite3_close(db);
    return 0;
}
