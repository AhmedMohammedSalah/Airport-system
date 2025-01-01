#ifndef PILOT_H
#define PILOT_H

#include "Empolyee.h"
#include <sqlite3.h>
#include <string>
#include <vector>

class Pilot : public Employee {
public:
    Pilot(int id, const std::string& name, const std::string& gender, int age,
          const std::string& username, const std::string& password, double salary, const std::string& address);
    // View flights assigned to the pilot
    virtual ~Pilot();
    void viewAssignedFlights(sqlite3* db);

    // View details of a specific flight
    void viewFlightDetails(sqlite3* db, int flightId);

    // Update the status of a flight
    bool updateFlightStatus(sqlite3* db, int flightId, const std::string& status);

private:
    // Add any additional attributes or methods for Pilot if needed
};

#endif
