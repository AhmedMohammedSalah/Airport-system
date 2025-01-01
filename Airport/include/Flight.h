#ifndef FLIGHT_H
#define FLIGHT_H
#include <vector>

#include <string>
#include <sqlite3.h>
using namespace std;

class Flight {
private:
    int id;
    string flightNumber;
    string departure;
    string destination;
    string departureTime;
    string arrivalTime;

public:
    // Constructor and Destructor
    Flight(int id, string flightNumber, string departure, string destination, string departureTime, string arrivalTime);
    ~Flight();
    static void displayAvailableFlights(sqlite3* db, const std::string& departureLocation);


    // Methods
    void saveToDatabase(sqlite3* db);
    static Flight* getFlightById(sqlite3* db, int flightId);
    static vector<Flight*> getFlightsByDeparture(sqlite3* db, const string& departure);
    void displayFlightDetails();

    // Getters and Setters
    int getId();
    void setId(int id);
    string getFlightNumber();
    void setFlightNumber(string flightNumber);
    string getDeparture();
    void setDeparture(string departure);
    string getDestination();
    void setDestination(string destination);
    string getDepartureTime();
    void setDepartureTime(string departureTime);
    string getArrivalTime();
    void setArrivalTime(string arrivalTime);
};

#endif
