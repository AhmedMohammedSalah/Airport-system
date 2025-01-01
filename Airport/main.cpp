#include <iostream>
#include "Passenger.h"
#include "Flight.h"
#include "Ticket.h"
#include "sqlite3.h"

using namespace std;

void createTables(sqlite3* db);
void insertTestFlights(sqlite3* db);
void insertTestPassenger(sqlite3* db);

int main() {
 sqlite3* db;
    int rc = sqlite3_open("airport_system.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    // Display available flights departing from "New York"
    Flight::displayAvailableFlights(db, "New York");

    sqlite3_close(db);
    return 0;
}
void createTables(sqlite3* db) {
    const char* query = R"(
        CREATE TABLE IF NOT EXISTS Persons (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT,
            gender TEXT,
            age INTEGER,
            username TEXT,
            password TEXT
        );
        CREATE TABLE IF NOT EXISTS Flights (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            flight_number TEXT,
            departure TEXT,
            destination TEXT,
            departure_time TEXT,
            arrival_time TEXT
        );
        CREATE TABLE IF NOT EXISTS Tickets (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            passenger_id INTEGER,
            flight_id INTEGER,
            booking_date TEXT,
            FOREIGN KEY(passenger_id) REFERENCES Persons(id),
            FOREIGN KEY(flight_id) REFERENCES Flights(id)
        );
    )";
    sqlite3_exec(db, query, nullptr, nullptr, nullptr);
}

void insertTestFlights(sqlite3* db) {
    string flights[] = {
        "INSERT INTO Flights (flight_number, departure, destination, departure_time, arrival_time) VALUES ('AA123', 'New York', 'Los Angeles', '2024-12-27 08:00', '2024-12-27 11:00');",
        "INSERT INTO Flights (flight_number, departure, destination, departure_time, arrival_time) VALUES ('AA124', 'Los Angeles', 'Chicago', '2024-12-28 09:00', '2024-12-28 12:00');"
    };
    for (const auto& query : flights) {
        sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);
    }
}

void insertTestPassenger(sqlite3* db) {
    const char* query = "INSERT INTO Persons (name, gender, age, username, password) VALUES ('John Doe', 'Male', 30, 'john_doe', 'password123');";
    sqlite3_exec(db, query, nullptr, nullptr, nullptr);
}
