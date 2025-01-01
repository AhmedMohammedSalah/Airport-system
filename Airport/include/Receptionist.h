#ifndef RECEPTIONIST_H
#define RECEPTIONIST_H

#include "Empolyee.h"
#include <sqlite3.h>
#include <string>

class Receptionist : public Employee {
public:
    // Update the constructor to match the base class Employee constructor
    Receptionist(int id, const std::string& name, const std::string& gender, int age, const std::string& username,
                const std::string& password, const std::string& address, double salary);

    ~Receptionist();

    // Method to check in a passenger
    bool checkInPassenger(sqlite3* db, int ticketId);

    // Method to assign a seat to a passenger
    bool assignSeat(sqlite3* db, int ticketId, const std::string& seatNumber);

    // Method to view passenger information
    void viewPassengerInfo(sqlite3* db, int passengerId);

    // Method to view flight information
    void viewFlightInfo(sqlite3* db, int flightId);
};

#endif
