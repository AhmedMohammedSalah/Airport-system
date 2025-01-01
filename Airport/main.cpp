#include <iostream>
#include <sqlite3.h>
#include "Passenger.h"
#include "Empolyee.h"
#include "Manager.h"
#include "Receptionist.h"
#include "Pilot.h"
#include "Ticket.h"
#include "Flight.h"

using namespace std;

void createTables(sqlite3* db) {
    const char* createFlightsTable =
        "CREATE TABLE IF NOT EXISTS Flights ("
        "id INTEGER PRIMARY KEY, "
        "flight_number TEXT, "
        "departure TEXT, "
        "destination TEXT, "
        "departure_time TEXT, "
        "arrival_time TEXT, "
        "status TEXT);";

    const char* createTicketsTable =
        "CREATE TABLE IF NOT EXISTS Tickets ("
        "id INTEGER PRIMARY KEY, "
        "passenger_id INTEGER, "
        "flight_id INTEGER, "
        "checked_in BOOLEAN, "
        "seat_number TEXT, "
        "FOREIGN KEY (passenger_id) REFERENCES Passengers(id), "
        "FOREIGN KEY (flight_id) REFERENCES Flights(id));";

    const char* createEmployeesTable =
        "CREATE TABLE IF NOT EXISTS Employees ("
        "id INTEGER PRIMARY KEY, "
        "name TEXT, "
        "gender TEXT, "
        "age INTEGER, "
        "username TEXT, "
        "password TEXT, "
        "salary REAL, "
        "address TEXT);";

    const char* createPilotAssignmentsTable =
        "CREATE TABLE IF NOT EXISTS PilotAssignments ("
        "id INTEGER PRIMARY KEY, "
        "pilot_id INTEGER, "
        "flight_id INTEGER, "
        "FOREIGN KEY (pilot_id) REFERENCES Employees(id), "
        "FOREIGN KEY (flight_id) REFERENCES Flights(id));";

    char* errorMessage = nullptr;
    int rc = sqlite3_exec(db, createFlightsTable, nullptr, nullptr, &errorMessage);
    if (rc != SQLITE_OK) {
        cout << "Error creating Flights table: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }

    rc = sqlite3_exec(db, createTicketsTable, nullptr, nullptr, &errorMessage);
    if (rc != SQLITE_OK) {
        cout << "Error creating Tickets table: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }

    rc = sqlite3_exec(db, createEmployeesTable, nullptr, nullptr, &errorMessage);
    if (rc != SQLITE_OK) {
        cout << "Error creating Employees table: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }

    rc = sqlite3_exec(db, createPilotAssignmentsTable, nullptr, nullptr, &errorMessage);
    if (rc != SQLITE_OK) {
        cout << "Error creating PilotAssignments table: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }
}

int main() {
    sqlite3* db;
    int rc = sqlite3_open("airport_system.db", &db);
    if (rc) {
        cout << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return 1;
    }

    // Create the necessary tables in the database
    createTables(db);

    // Create some initial data const std::string& username,

    Manager manager(1, "Alice", "Female", 35, "manager", "password", "123456789", 60000);
    Receptionist receptionist(2, "Bob", "Male", 28, "receptionist", "password", "Alminya", 30000);
    Pilot pilot(3, "Charlie", "Male", 40, "pilot", "password",50000, "Cairo");

    // Create some Flights
    Flight flight1(1, "FN123", "New York", "Los Angeles", "2025-01-15 08:00", "2025-01-15 11:00");
    Flight flight2(2, "FN456", "Los Angeles", "San Francisco", "2025-01-16 09:00", "2025-01-16 12:00");

    // Booking tickets
    Passenger passenger(1, "John Doe", "Male", 30, "john", "pass123", "5551234567", "AB+");
//    Ticket ticket1(1, 1, 1);
//    ticket1.bookTicket(db, passenger.getId(), flight1.getId());
//    ticket1.bookTicket(db, passenger.getId(), flight2.getId());
//
//    // Viewing tickets
//    ticket1.viewTickets(db, passenger.getId());
//
//    // Check-in passenger
//    receptionist.checkInPassenger(db, 1); // Assuming ticket ID is 1 for simplicity
//
//    // Assign pilot to a flight
//    pilot.assignFlight(db, 1, flight1.getId());
//
//    // Update flight status
//    pilot.updateFlightStatus(db, 1, "In-Flight");
//
//    // View assigned flights for pilot
//    pilot.viewAssignedFlights(db);
//
//    // Close the database connection
//    sqlite3_close(db);

    return 0;
}
