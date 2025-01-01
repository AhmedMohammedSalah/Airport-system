#include "Flight.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

Flight::Flight(int id, string flightNumber, string departure, string destination, string departureTime, string arrivalTime)
    : id(id), flightNumber(flightNumber), departure(departure), destination(destination), departureTime(departureTime), arrivalTime(arrivalTime) {}

Flight::~Flight() {}

void Flight::saveToDatabase(sqlite3* db) {
    stringstream query;
    query << "INSERT INTO Flights (flight_number, departure, destination, departure_time, arrival_time) "
          << "VALUES ('" << flightNumber << "', '" << departure << "', '" << destination << "', '" << departureTime << "', '" << arrivalTime << "');";

    char* errorMessage = nullptr;
    int rc = sqlite3_exec(db, query.str().c_str(), nullptr, nullptr, &errorMessage);

    if (rc == SQLITE_OK) {
        cout << "Flight saved successfully to database." << endl;
    } else {
        cout << "Error saving flight to database: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }
}

Flight* Flight::getFlightById(sqlite3* db, int flightId) {
    stringstream query;
    query << "SELECT id, flight_number, departure, destination, departure_time, arrival_time FROM Flights WHERE id = " << flightId << ";";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            string flightNumber = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            string departure = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            string destination = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            string departureTime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            string arrivalTime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
            sqlite3_finalize(stmt);
            return new Flight(id, flightNumber, departure, destination, departureTime, arrivalTime);
        }
    }
    sqlite3_finalize(stmt);
    return nullptr;
}

vector<Flight*> Flight::getFlightsByDeparture(sqlite3* db, const string& departure) {
    stringstream query;
    query << "SELECT id, flight_number, departure, destination, departure_time, arrival_time FROM Flights WHERE departure = '" << departure << "';";
    sqlite3_stmt* stmt;
    vector<Flight*> flights;

    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            string flightNumber = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            string departure = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            string destination = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            string departureTime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            string arrivalTime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
            flights.push_back(new Flight(id, flightNumber, departure, destination, departureTime, arrivalTime));
        }
    }
    sqlite3_finalize(stmt);
    return flights;
}

void Flight::displayFlightDetails() {
    cout << "Flight ID: " << id << endl
         << "Flight Number: " << flightNumber << endl
         << "Departure: " << departure << endl
         << "Destination: " << destination << endl
         << "Departure Time: " << departureTime << endl
         << "Arrival Time: " << arrivalTime << endl;
}

void Flight::displayAvailableFlights(sqlite3* db, const std::string& departureLocation)
{
    // SQL query to get available flights from a specific departure location
    std::stringstream query;
    query << "SELECT id, flight_number, departure, destination, departure_time, arrival_time "
          << "FROM Flights WHERE departure = '" << departureLocation << "';";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        std::cout << "Available flights from " << departureLocation << ":\n";
        // Loop through the results and display them
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int id = sqlite3_column_int(stmt, 0);
            std::string flightNumber = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::string departure = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            std::string destination = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            std::string departureTime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            std::string arrivalTime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

            // Display flight details
            std::cout << "Flight ID: " << id
                      << ", Flight Number: " << flightNumber
                      << ", From: " << departure
                      << ", To: " << destination
                      << ", Departure: " << departureTime
                      << ", Arrival: " << arrivalTime << std::endl;
        }
    }
    else
    {
        std::cout << "Error fetching available flights: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}
// Getters and Setters
int Flight::getId() { return id; }
void Flight::setId(int id) { this->id = id; }
string Flight::getFlightNumber() { return flightNumber; }
void Flight::setFlightNumber(string flightNumber) { this->flightNumber = flightNumber; }
string Flight::getDeparture() { return departure; }
void Flight::setDeparture(string departure) { this->departure = departure; }
string Flight::getDestination() { return destination; }
void Flight::setDestination(string destination) { this->destination = destination; }
string Flight::getDepartureTime() { return departureTime; }
void Flight::setDepartureTime(string departureTime) { this->departureTime = departureTime; }
string Flight::getArrivalTime() { return arrivalTime; }
void Flight::setArrivalTime(string arrivalTime) { this->arrivalTime = arrivalTime; }
