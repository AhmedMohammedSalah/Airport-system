#include "Ticket.h"
#include <iostream>
#include <sstream>
#include <vector>

Ticket::Ticket(int id, int passengerId, int flightId, string bookingDate)
    : id(id), passengerId(passengerId), flightId(flightId), bookingDate(bookingDate) {}
Ticket::Ticket(int passengerId, int flightId, string bookingDate)
    : passengerId(passengerId), flightId(flightId), bookingDate(bookingDate) {
    this->id = -1; // Placeholder for when the ticket is saved to the database.
}
Ticket::~Ticket() {}

void Ticket::saveToDatabase(sqlite3* db) {
    stringstream query;
    query << "INSERT INTO Tickets (passenger_id, flight_id, booking_date) "
          << "VALUES (" << passengerId << ", " << flightId << ", '" << bookingDate << "');";

    char* errorMessage = nullptr;
    int rc = sqlite3_exec(db, query.str().c_str(), nullptr, nullptr, &errorMessage);

    if (rc == SQLITE_OK) {
        // Retrieve the last inserted row ID as the ticket ID
        this->id = sqlite3_last_insert_rowid(db);
        cout << "Ticket saved successfully to database with ID: " << this->id << endl;
    } else {
        cout << "Error saving ticket to database: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }
}

Ticket* Ticket::getTicketById(sqlite3* db, int ticketId) {
    stringstream query;
    query << "SELECT id, passenger_id, flight_id, booking_date FROM Tickets WHERE id = " << ticketId << ";";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            int passengerId = sqlite3_column_int(stmt, 1);
            int flightId = sqlite3_column_int(stmt, 2);
            string bookingDate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            sqlite3_finalize(stmt);
            return new Ticket(id, passengerId, flightId, bookingDate);
        }
    }
    sqlite3_finalize(stmt);
    return nullptr;
}

vector<Ticket*> Ticket::getTicketsByPassenger(sqlite3* db, int passengerId) {
    stringstream query;
    query << "SELECT id, passenger_id, flight_id, booking_date FROM Tickets WHERE passenger_id = " << passengerId << ";";
    sqlite3_stmt* stmt;
    vector<Ticket*> tickets;

    if (sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            int passengerId = sqlite3_column_int(stmt, 1);
            int flightId = sqlite3_column_int(stmt, 2);
            string bookingDate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            tickets.push_back(new Ticket(id, passengerId, flightId, bookingDate));
        }
    }
    sqlite3_finalize(stmt);
    return tickets;
}

void Ticket::displayTicketDetails() {
    cout << "Ticket ID: " << id << endl
         << "Passenger ID: " << passengerId << endl
         << "Flight ID: " << flightId << endl
         << "Booking Date: " << bookingDate << endl;
}

// Getters and Setters
int Ticket::getId() { return id; }
void Ticket::setId(int id) { this->id = id; }
int Ticket::getPassengerId() { return passengerId; }
void Ticket::setPassengerId(int passengerId) { this->passengerId = passengerId; }
int Ticket::getFlightId() { return flightId; }
void Ticket::setFlightId(int flightId) { this->flightId = flightId; }
string Ticket::getBookingDate() { return bookingDate; }
void Ticket::setBookingDate(string bookingDate) { this->bookingDate = bookingDate; }
