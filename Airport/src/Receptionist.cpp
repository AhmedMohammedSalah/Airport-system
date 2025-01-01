#include "Receptionist.h"
#include <iostream>
#include <sqlite3.h>

Receptionist::Receptionist(int id, const std::string& name, const std::string& gender, int age, const std::string& username,
                           const std::string& password, const std::string& address, double salary)
    : Employee(id, name, gender, age, username, password, address, salary) {}

Receptionist::~Receptionist() {}

bool Receptionist::checkInPassenger(sqlite3* db, int ticketId)
{
    std::string query = "UPDATE Tickets SET checked_in = 1 WHERE id = " + std::to_string(ticketId) + ";";
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
    if (rc == SQLITE_OK)
    {
        std::cout << "Passenger checked in successfully!" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Error checking in passenger: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
}

bool Receptionist::assignSeat(sqlite3* db, int ticketId, const std::string& seatNumber)
{
    std::string query = "UPDATE Tickets SET seat_number = '" + seatNumber + "' WHERE id = " + std::to_string(ticketId) + ";";
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
    if (rc == SQLITE_OK)
    {
        std::cout << "Seat assigned successfully!" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Error assigning seat: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
}

void Receptionist::viewPassengerInfo(sqlite3* db, int passengerId)
{
    std::string query = "SELECT * FROM Passengers WHERE id = " + std::to_string(passengerId) + ";";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            std::cout << "Passenger ID: " << sqlite3_column_int(stmt, 0)
                      << ", Name: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))
                      << ", Gender: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2))
                      << ", Age: " << sqlite3_column_int(stmt, 3) << std::endl;
        }
    }
    else
    {
        std::cout << "Error fetching passenger info: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void Receptionist::viewFlightInfo(sqlite3* db, int flightId)
{
    std::string query = "SELECT * FROM Flights WHERE id = " + std::to_string(flightId) + ";";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            std::cout << "Flight ID: " << sqlite3_column_int(stmt, 0)
                      << ", Flight Number: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))
                      << ", Departure: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2))
                      << ", Destination: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3))
                      << std::endl;
        }
    }
    else
    {
        std::cout << "Error fetching flight info: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}
