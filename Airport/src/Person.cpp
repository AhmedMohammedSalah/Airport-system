#include "Person.h"
#include <iostream>

// Constructor
Person::Person(int id, string name, string gender, int age, string username, string password)
    : id(id), name(name), gender(gender), age(age), username(username), password(password) {}

// Destructor
Person::~Person() {}

// Methods
void Person::login(sqlite3* db) {
    string query = "SELECT * FROM Persons WHERE username = '" + username + "' AND password = '" + password + "';";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            cout << "Login successful for user: " << username << endl;
        } else {
            cout << "Login failed: Invalid username or password." << endl;
        }
    } else {
        cout << "Error executing login query." << endl;
    }

    sqlite3_finalize(stmt);
}

// Getters and Setters
int Person::getId() {
    return id;
}

void Person::setId(int id) {
    this->id = id;
}

string Person::getName() {
    return name;
}

void Person::setName(string name) {
    this->name = name;
}

string Person::getGender() {
    return gender;
}

void Person::setGender(string gender) {
    this->gender = gender;
}

int Person::getAge() {
    return age;
}

void Person::setAge(int age) {
    this->age = age;
}

string Person::getUsername() {
    return username;
}

void Person::setUsername(string username) {
    this->username = username;
}

string Person::getPassword() {
    return password;
}

void Person::setPassword(string password) {
    this->password = password;
}
