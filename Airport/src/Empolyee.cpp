#include "Empolyee.h"


Employee::Employee(int id, const string& name, const string& gender, int age, const string& username, const string& password, const string& position, double salary)
    : Person(id, name, gender, age, username, password), position(position), salary(salary) {}

Employee::~Employee() {}

string Employee::getPosition() const {
    return position;
}

void Employee::setPosition(const string& position) {
    this->position = position;
}

double Employee::getSalary() const {
    return salary;
}

void Employee::setSalary(double salary) {
    this->salary = salary;
}
