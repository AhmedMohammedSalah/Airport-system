#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Person.h"
#include <string>
using namespace std;

class Employee : public Person {
protected:
    string position;
    double salary;

public:
    // Constructor and Destructor
    Employee(int id, const string& name, const string& gender, int age, const string& username, const string& password, const string& position, double salary);
    virtual ~Employee();

    // Getter and Setter functions
    string getPosition() const;
    void setPosition(const string& position);

    double getSalary() const;
    void setSalary(double salary);
};

#endif
