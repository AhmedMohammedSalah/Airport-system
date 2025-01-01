#include "Pilot.h"
#include <iostream>
#include <sstream>

Pilot::Pilot(int id, const std::string& name, const std::string& gender, int age,
          const std::string& username, const std::string& password,
          double salary, const std::string& address)
    : Employee(id, name, gender, age, username, password, address,salary) // Calling the Employee constructor
{
}

Pilot::~Pilot() {

}

void Pilot::viewAssignedFlights(sqlite3* db) {
    std::string query = "SELECT F.flight_number, F.departure, F.destination, F.departure_time, F.arrival_time FROM PilotAssignments PA "
                        "JOIN Flights F ON PA.flight_id = F.id WHERE PA.pilot_id = " + std::to_string(id) + ";";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        std::cout << "Assigned Flights:" << std::endl;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string flightNumber = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string departure = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::string destination = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            std::string departureTime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            std::string arrivalTime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

            std::cout << "Flight: " << flightNumber << ", From: " << departure
                      << ", To: " << destination << ", Departure: " << departureTime
                      << ", Arrival: " << arrivalTime << std::endl;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cout << "Error fetching assigned flights: " << sqlite3_errmsg(db) << std::endl;
    }
}

void Pilot::viewFlightDetails(sqlite3* db, int flightId) {
    std::string query = "SELECT flight_number, departure, destination, departure_time, arrival_time, status FROM Flights WHERE id = " + std::to_string(flightId) + ";";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string flightNumber = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string departure = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::string destination = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            std::string departureTime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            std::string arrivalTime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            std::string status = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

            std::cout << "Flight Details: " << std::endl;
            std::cout << "Flight Number: " << flightNumber << ", Departure: " << departure
                      << ", Destination: " << destination << ", Departure Time: " << departureTime
                      << ", Arrival Time: " << arrivalTime << ", Status: " << status << std::endl;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cout << "Error fetching flight details: " << sqlite3_errmsg(db) << std::endl;
    }
}

bool Pilot::updateFlightStatus(sqlite3* db, int flightId, const std::string& status) {
    std::stringstream query;
    query << "UPDATE Flights SET status = ? WHERE id = ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, status.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, flightId);

        int rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        if (rc == SQLITE_DONE) {
            std::cout << "Flight status updated to: " << status << std::endl;
            return true;
        } else {
            std::cout << "Error updating flight status: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
    }
    return false;
}
