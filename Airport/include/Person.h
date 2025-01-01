#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <sqlite3.h>
using namespace std;

class Person
{
protected:
    int id;
    string name;
    string gender;
    int age;
    string username;
    string password;

public:
    // ructor and Destructor
    Person(int id,  string name,  string gender, int age,  string username,  string password);
    virtual ~Person();

    // Methods
    virtual void login(sqlite3* db);
    static Person login(sqlite3* db, string username, string password);

    // Getters and Setters
    int getId() ;
    void setId(int id);
    string getName() ;
    void setName( string name);
    string getGender() ;
    void setGender( string gender);
    int getAge() ;
    void setAge(int age);
    string getUsername() ;
    void setUsername( string username);
    string getPassword() ;
    void setPassword( string password);
};

#endif
