#ifndef PASSENGER_H
#define PASSENGER_H

#include "Person.h"
#include <string>
#include <vector>

class Passenger : public Person
{
private:
    std::string phoneNumber;
    std::string bloodType;

public:
    // Constructor and Destructor
    Passenger(int id, const std::string& name, const std::string& gender, int age, const std::string& username, const std::string& password, const std::string& phoneNumber, const std::string& bloodType);
    ~Passenger();

    // Methods
    bool bookTicket(sqlite3* db, int flightId);  // Return success/failure
    void viewTickets(sqlite3* db);

    // Getters and Setters
    std::string getPhoneNumber();
    void setPhoneNumber(const std::string& phoneNumber);
    std::string getBloodType();
    void setBloodType(const std::string& bloodType);
};

#endif
