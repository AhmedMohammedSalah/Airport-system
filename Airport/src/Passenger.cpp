#include "Passenger.h"
#include <iostream>
#include <sstream>
#include <sqlite3.h>


Passenger::Passenger(int id, const string& name, const string& gender, int age, const string& username, const string& password, const string& phoneNumber, const string& bloodType)
    : Person(id, name, gender, age, username, password), phoneNumber(phoneNumber), bloodType(bloodType) {
}

Passenger::~Passenger() {}

bool Passenger::bookTicket(sqlite3* db, int flightId)
{
    // Check if the flight exists before booking a ticket
    stringstream checkQuery;
    checkQuery << "SELECT COUNT(*) FROM Flights WHERE id = " << flightId << ";";

    sqlite3_stmt* checkStmt;
    if (sqlite3_prepare_v2(db, checkQuery.str().c_str(), -1, &checkStmt, nullptr) == SQLITE_OK)
    {
        if (sqlite3_step(checkStmt) == SQLITE_ROW)
        {
            int flightCount = sqlite3_column_int(checkStmt, 0);
            if (flightCount == 0)
            {
                cout << "Error: Flight with ID " << flightId << " does not exist." << endl;
                sqlite3_finalize(checkStmt);
                return false;
            }
        }
        else
        {
            cout << "Error checking flight existence." << endl;
            sqlite3_finalize(checkStmt);
            return false;
        }
    }

    sqlite3_finalize(checkStmt);

    // Proceed with booking the ticket
    stringstream query;
    query << "INSERT INTO Tickets (passenger_id, flight_id) VALUES (" << id << ", " << flightId << ");";

    char* errorMessage = nullptr;
    int rc = sqlite3_exec(db, query.str().c_str(), nullptr, nullptr, &errorMessage);

    if (rc == SQLITE_OK)
    {
        cout << "Ticket successfully booked for flight ID: " << flightId << endl;
        return true;
    }
    else
    {
        cout << "Error booking ticket: " << errorMessage << endl;
        sqlite3_free(errorMessage);
        return false;
    }
}

void Passenger::viewTickets(sqlite3* db)
{
    string query = "SELECT T.id, F.flight_number, F.departure, F.destination, F.departure_time, F.arrival_time FROM Tickets T "
                   "JOIN Flights F ON T.flight_id = F.id WHERE T.passenger_id = " + to_string(id) + ";";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        cout << "Your tickets:" << endl;
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int ticketId = sqlite3_column_int(stmt, 0);
            string flightNumber = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            string departure = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            string destination = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            string departureTime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            string arrivalTime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

            cout << "Ticket ID: " << ticketId << ", Flight: " << flightNumber << ", From: " << departure
                 << ", To: " << destination << ", Departure: " << departureTime << ", Arrival: " << arrivalTime << endl;
        }
    }
    else
    {
        cout << "Error fetching tickets: " << sqlite3_errmsg(db) << endl;
    }
    sqlite3_finalize(stmt);
}

string Passenger::getPhoneNumber()
{
    return phoneNumber;
}

void Passenger::setPhoneNumber(const std::string& phoneNumber)
{
    this->phoneNumber = phoneNumber;
}

void Passenger::setBloodType(const std::string& bloodType)
{
    this->bloodType = bloodType;
}


string Passenger::getBloodType()
{
    return bloodType;
}

