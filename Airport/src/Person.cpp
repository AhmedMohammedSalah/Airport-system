#include "Person.h"
#include <iostream>

// Constructor
Person::Person(int id, string name, string gender, int age, string username, string password)
    : id(id), name(name), gender(gender), age(age), username(username), password(password) {}

// Destructor
Person::~Person() {}

// Methods
void Person::login(sqlite3* db)
{
    string query = "SELECT * FROM Persons WHERE username = ? AND password = ?";
    sqlite3_stmt* stmt;

    // Prepare the query
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        // Bind parameters
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

        // Execute the query
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            cout << "Login successful for user: " << username << endl;
        }
        else
        {
            cout << "Login failed: Invalid username or password." << endl;
        }
    }
    else
    {
        cout << "Error executing login query: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
}

Person Person::login(sqlite3* db, string username, string password)
{
    string query = "SELECT * FROM Persons WHERE username = ? AND password = ?;";
    sqlite3_stmt* stmt;

    // Prepare the SQL query
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        // Bind parameters to prevent SQL injection
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

        // Execute the query
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            // Extract values from the query result
            int id = sqlite3_column_int(stmt, 0);
            string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            string gender = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            int age = sqlite3_column_int(stmt, 3);
            string username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            string password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

            // Finalize the statement and return the populated Person object
            sqlite3_finalize(stmt);
            return Person(id, name, gender, age, username, password);
        }
        else
        {
            cout << "Login failed: Invalid username or password." << endl;
        }
    }
    else
    {
        cout << "Error preparing login query: " << sqlite3_errmsg(db) << endl;
    }

    // Finalize the statement and return an invalid Person object
    sqlite3_finalize(stmt);
    return Person(-1, "", "", 0, "", ""); // Special "invalid" Person object
}
// Getters and Setters
int Person::getId()
{
    return id;
}

void Person::setId(int id)
{
    this->id = id;
}

string Person::getName()
{
    return name;
}

void Person::setName(string name)
{
    this->name = name;
}

string Person::getGender()
{
    return gender;
}

void Person::setGender(string gender)
{
    this->gender = gender;
}

int Person::getAge()
{
    return age;
}

void Person::setAge(int age)
{
    this->age = age;
}

string Person::getUsername()
{
    return username;
}

void Person::setUsername(string username)
{
    this->username = username;
}

string Person::getPassword()
{
    return password;
}

void Person::setPassword(string password)
{
    this->password = password;
}
