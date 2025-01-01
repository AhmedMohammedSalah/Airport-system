#ifndef TICKET_H
#define TICKET_H

#include <vector>
#include <string>
#include <sqlite3.h>
#include "Flight.h"
using namespace std;

class Ticket {
private:
    int id;
    int passengerId;
    int flightId;
    string bookingDate;

public:
    Ticket(int passengerId, int flightId, string bookingDate);
    // Constructor and Destructor
    Ticket(int id, int passengerId, int flightId, string bookingDate);
    ~Ticket();

    // Methods
    void saveToDatabase(sqlite3* db);
    static Ticket* getTicketById(sqlite3* db, int ticketId);
    static vector<Ticket*> getTicketsByPassenger(sqlite3* db, int passengerId);
    void displayTicketDetails();

    // Getters and Setters
    int getId();
    void setId(int id);
    int getPassengerId();
    void setPassengerId(int passengerId);
    int getFlightId();
    void setFlightId(int flightId);
    string getBookingDate();
    void setBookingDate(string bookingDate);
};

#endif
