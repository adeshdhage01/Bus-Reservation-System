#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

// Forward declarations
class Bus;
class Route;
class Reservation;

// Class to handle date
class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int d = 1, int m = 1, int y = 2023) : day(d), month(m), year(y) {}

    void setDate(int d, int m, int y) {
        day = d;
        month = m;
        year = y;
    }

    string getDate() const {
        return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    }

    void display() const {
        cout << setfill('0') << setw(2) << day << "/" 
             << setw(2) << month << "/" << year << setfill(' ');
    }
};

// Class to handle time
class Time {
private:
    int hour;
    int minute;

public:
    Time(int h = 0, int m = 0) : hour(h), minute(m) {}

    void setTime(int h, int m) {
        hour = h;
        minute = m;
    }

    string getTime() const {
        return to_string(hour) + ":" + (minute < 10 ? "0" : "") + to_string(minute);
    }

    void display() const {
        cout << setfill('0') << setw(2) << hour << ":" 
             << setw(2) << minute << setfill(' ');
    }
};

// Bus class
class Bus {
private:
    int busId;
    string busNumber;
    string model;
    int capacity;
    bool isAvailable;

public:
    Bus(int id = 0, string number = "", string m = "", int cap = 0)
        : busId(id), busNumber(number), model(m), capacity(cap), isAvailable(true) {}

    // Getters
    int getBusId() const { return busId; }
    string getBusNumber() const { return busNumber; }
    string getModel() const { return model; }
    int getCapacity() const { return capacity; }
    bool getAvailability() const { return isAvailable; }

    // Setters
    void setBusId(int id) { busId = id; }
    void setBusNumber(string number) { busNumber = number; }
    void setModel(string m) { model = m; }
    void setCapacity(int cap) { capacity = cap; }
    void setAvailability(bool available) { isAvailable = available; }

    void display() const {
        cout << setw(5) << busId << setw(15) << busNumber 
             << setw(15) << model << setw(10) << capacity 
             << setw(12) << (isAvailable ? "Available" : "Booked") << endl;
    }
};

// Route class
class Route {
private:
    int routeId;
    string source;
    string destination;
    int distance; // in km
    Time departureTime;
    Time arrivalTime;
    float fare;

public:
    Route(int id = 0, string src = "", string dest = "", int dist = 0, 
          Time dep = Time(), Time arr = Time(), float f = 0.0f)
        : routeId(id), source(src), destination(dest), distance(dist), 
          departureTime(dep), arrivalTime(arr), fare(f) {}

    // Getters
    int getRouteId() const { return routeId; }
    string getSource() const { return source; }
    string getDestination() const { return destination; }
    int getDistance() const { return distance; }
    Time getDepartureTime() const { return departureTime; }
    Time getArrivalTime() const { return arrivalTime; }
    float getFare() const { return fare; }

    // Setters
    void setRouteId(int id) { routeId = id; }
    void setSource(string src) { source = src; }
    void setDestination(string dest) { destination = dest; }
    void setDistance(int dist) { distance = dist; }
    void setDepartureTime(Time dep) { departureTime = dep; }
    void setArrivalTime(Time arr) { arrivalTime = arr; }
    void setFare(float f) { fare = f; }

    void display() const {
        cout << setw(5) << routeId << setw(15) << source 
             << setw(15) << destination << setw(10) << distance << " km"
             << setw(10);
        departureTime.display();
        cout << setw(10);
        arrivalTime.display();
        cout << setw(10) << fare << " Rs" << endl;
    }
};

// Reservation class
class Reservation {
private:
    int reservationId;
    int busId;
    int routeId;
    Date journeyDate;
    string passengerName;
    int seatNumber;
    string contactNumber;
    string status; // "Confirmed", "Cancelled"

public:
    Reservation(int resId = 0, int bId = 0, int rId = 0, Date date = Date(), 
                string name = "", int seat = 0, string contact = "", string stat = "Confirmed")
        : reservationId(resId), busId(bId), routeId(rId), journeyDate(date), 
          passengerName(name), seatNumber(seat), contactNumber(contact), status(stat) {}

    // Getters
    int getReservationId() const { return reservationId; }
    int getBusId() const { return busId; }
    int getRouteId() const { return routeId; }
    Date getJourneyDate() const { return journeyDate; }
    string getPassengerName() const { return passengerName; }
    int getSeatNumber() const { return seatNumber; }
    string getContactNumber() const { return contactNumber; }
    string getStatus() const { return status; }

    // Setters
    void setReservationId(int id) { reservationId = id; }
    void setBusId(int id) { busId = id; }
    void setRouteId(int id) { routeId = id; }
    void setJourneyDate(Date date) { journeyDate = date; }
    void setPassengerName(string name) { passengerName = name; }
    void setSeatNumber(int seat) { seatNumber = seat; }
    void setContactNumber(string contact) { contactNumber = contact; }
    void setStatus(string stat) { status = stat; }

    void display() const {
        cout << setw(5) << reservationId << setw(10) << busId 
             << setw(10) << routeId << setw(15);
        journeyDate.display();
        cout << setw(20) << passengerName << setw(10) << seatNumber 
             << setw(15) << contactNumber << setw(15) << status << endl;
    }
};

// Bus Reservation System class
class BusReservationSystem {
private:
    vector<Bus> buses;
    vector<Route> routes;
    vector<Reservation> reservations;
    int nextBusId;
    int nextRouteId;
    int nextReservationId;

public:
    BusReservationSystem() : nextBusId(1), nextRouteId(1), nextReservationId(1) {}

    // Add a new bus to the system
    void addBus(string busNumber, string model, int capacity) {
        Bus newBus(nextBusId++, busNumber, model, capacity);
        buses.push_back(newBus);
        cout << "Bus added successfully with ID: " << newBus.getBusId() << endl;
    }

    // Add a new route to the system
    void addRoute(string source, string destination, int distance, 
                  Time departureTime, Time arrivalTime, float fare) {
        Route newRoute(nextRouteId++, source, destination, distance, departureTime, arrivalTime, fare);
        routes.push_back(newRoute);
        cout << "Route added successfully with ID: " << newRoute.getRouteId() << endl;
    }

    // Make a new reservation
    void makeReservation(int busId, int routeId, Date journeyDate, 
                         string passengerName, int seatNumber, string contactNumber) {
        // Check if bus exists
        auto busIt = find_if(buses.begin(), buses.end(), 
                            [busId](const Bus& b) { return b.getBusId() == busId; });
        if (busIt == buses.end()) {
            cout << "Bus with ID " << busId << " not found." << endl;
            return;
        }

        // Check if route exists
        auto routeIt = find_if(routes.begin(), routes.end(), 
                               [routeId](const Route& r) { return r.getRouteId() == routeId; });
        if (routeIt == routes.end()) {
            cout << "Route with ID " << routeId << " not found." << endl;
            return;
        }

        // Check if seat is available
        for (const auto& res : reservations) {
            if (res.getBusId() == busId && res.getJourneyDate().getDate() == journeyDate.getDate() 
                && res.getSeatNumber() == seatNumber && res.getStatus() == "Confirmed") {
                cout << "Seat " << seatNumber << " is already booked for this bus on the selected date." << endl;
                return;
            }
        }

        // Check if seat number is valid
        if (seatNumber < 1 || seatNumber > busIt->getCapacity()) {
            cout << "Invalid seat number. Please select between 1 and " << busIt->getCapacity() << endl;
            return;
        }

        Reservation newReservation(nextReservationId++, busId, routeId, journeyDate, 
                                  passengerName, seatNumber, contactNumber);
        reservations.push_back(newReservation);
        cout << "Reservation successful! Your reservation ID is: " << newReservation.getReservationId() << endl;
    }

    // Cancel a reservation
    void cancelReservation(int reservationId) {
        auto it = find_if(reservations.begin(), reservations.end(), 
                          [reservationId](const Reservation& r) { 
                              return r.getReservationId() == reservationId && r.getStatus() == "Confirmed"; 
                          });

        if (it != reservations.end()) {
            it->setStatus("Cancelled");
            cout << "Reservation ID " << reservationId << " has been cancelled successfully." << endl;
        } else {
            cout << "Reservation ID " << reservationId << " not found or already cancelled." << endl;
        }
    }

    // Display all buses
    void displayAllBuses() const {
        if (buses.empty()) {
            cout << "No buses available in the system." << endl;
            return;
        }

        cout << "\nList of All Buses:\n";
        cout << "------------------------------------------------------------\n";
        cout << setw(5) << "ID" << setw(15) << "Bus Number" << setw(15) << "Model" 
             << setw(10) << "Capacity" << setw(12) << "Status" << endl;
        cout << "------------------------------------------------------------\n";

        for (const auto& bus : buses) {
            bus.display();
        }
        cout << "------------------------------------------------------------\n";
    }

    // Display all routes
    void displayAllRoutes() const {
        if (routes.empty()) {
            cout << "No routes available in the system." << endl;
            return;
        }

        cout << "\nList of All Routes:\n";
        cout << "------------------------------------------------------------------------------------------\n";
        cout << setw(5) << "ID" << setw(15) << "Source" << setw(15) << "Destination" 
             << setw(12) << "Distance" << setw(10) << "Departure" << setw(10) << "Arrival" 
             << setw(10) << "Fare" << endl;
        cout << "------------------------------------------------------------------------------------------\n";

        for (const auto& route : routes) {
            route.display();
        }
        cout << "------------------------------------------------------------------------------------------\n";
    }

    // Display all reservations
    void displayAllReservations() const {
        if (reservations.empty()) {
            cout << "No reservations available in the system." << endl;
            return;
        }

        cout << "\nList of All Reservations:\n";
        cout << "--------------------------------------------------------------------------------------------------------\n";
        cout << setw(5) << "Res ID" << setw(10) << "Bus ID" << setw(10) << "Route ID" 
             << setw(15) << "Journey Date" << setw(20) << "Passenger Name" << setw(10) << "Seat No" 
             << setw(15) << "Contact No" << setw(15) << "Status" << endl;
        cout << "--------------------------------------------------------------------------------------------------------\n";

        for (const auto& res : reservations) {
            res.display();
        }
        cout << "--------------------------------------------------------------------------------------------------------\n";
    }

    // Display available seats for a bus on a specific date
    void displayAvailableSeats(int busId, Date date) const {
        auto busIt = find_if(buses.begin(), buses.end(), 
                            [busId](const Bus& b) { return b.getBusId() == busId; });

        if (busIt == buses.end()) {
            cout << "Bus with ID " << busId << " not found." << endl;
            return;
        }

        int capacity = busIt->getCapacity();
        vector<bool> seats(capacity + 1, true); // seats[0] unused, seats 1 to capacity

        // Mark booked seats as false
        for (const auto& res : reservations) {
            if (res.getBusId() == busId && res.getJourneyDate().getDate() == date.getDate() 
                && res.getStatus() == "Confirmed") {
                seats[res.getSeatNumber()] = false;
            }
        }

        cout << "\nAvailable seats for Bus ID " << busId << " on ";
        date.display();
        cout << ":\n";

        cout << "Total capacity: " << capacity << endl;
        cout << "Available seats: ";
        for (int i = 1; i <= capacity; ++i) {
            if (seats[i]) {
                cout << i << " ";
            }
        }
        cout << endl;
    }

    // Get bus by ID
    Bus* getBusById(int busId) {
        for (auto& bus : buses) {
            if (bus.getBusId() == busId) {
                return &bus;
            }
        }
        return nullptr;
    }

    // Get route by ID
    Route* getRouteById(int routeId) {
        for (auto& route : routes) {
            if (route.getRouteId() == routeId) {
                return &route;
            }
        }
        return nullptr;
    }

    // Get reservation by ID
    Reservation* getReservationById(int reservationId) {
        for (auto& res : reservations) {
            if (res.getReservationId() == reservationId) {
                return &res;
            }
        }
        return nullptr;
    }
};

// Utility functions
void displayMainMenu() {
    cout << "\nBus Reservation System\n";
    cout << "----------------------\n";
    cout << "1. Bus Management\n";
    cout << "2. Route Management\n";
    cout << "3. Reservation Management\n";
    cout << "4. View Reports\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

void displayBusManagementMenu() {
    cout << "\nBus Management\n";
    cout << "--------------\n";
    cout << "1. Add New Bus\n";
    cout << "2. View All Buses\n";
    cout << "3. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

void displayRouteManagementMenu() {
    cout << "\nRoute Management\n";
    cout << "---------------\n";
    cout << "1. Add New Route\n";
    cout << "2. View All Routes\n";
    cout << "3. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

void displayReservationManagementMenu() {
    cout << "\nReservation Management\n";
    cout << "---------------------\n";
    cout << "1. Make New Reservation\n";
    cout << "2. Cancel Reservation\n";
    cout << "3. View Available Seats\n";
    cout << "4. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

void displayReportsMenu() {
    cout << "\nReports\n";
    cout << "-------\n";
    cout << "1. View All Reservations\n";
    cout << "2. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

int main() {
    BusReservationSystem system;

    // Add some sample data
    system.addBus("MH01AB1234", "Volvo AC", 40);
    system.addBus("MH02CD5678", "Tata Non-AC", 50);
    system.addBus("MH03EF9012", "Ashok Leyland AC", 35);

    system.addRoute("Mumbai", "Pune", 150, Time(7, 30), Time(11, 0), 500.0f);
    system.addRoute("Delhi", "Jaipur", 280, Time(8, 0), Time(13, 30), 800.0f);
    system.addRoute("Bangalore", "Chennai", 350, Time(6, 0), Time(12, 0), 900.0f);

    int choice;
    do {
        displayMainMenu();
        cin >> choice;

        switch (choice) {
            case 1: { // Bus Management
                int busChoice;
                do {
                    displayBusManagementMenu();
                    cin >> busChoice;

                    switch (busChoice) {
                        case 1: { // Add New Bus
                            string busNumber, model;
                            int capacity;

                            cout << "Enter Bus Number: ";
                            cin.ignore();
                            getline(cin, busNumber);
                            cout << "Enter Model: ";
                            getline(cin, model);
                            cout << "Enter Capacity: ";
                            cin >> capacity;

                            system.addBus(busNumber, model, capacity);
                            break;
                        }
                        case 2: // View All Buses
                            system.displayAllBuses();
                            break;
                        case 3: // Back to Main Menu
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                    }
                } while (busChoice != 3);
                break;
            }
            case 2: { // Route Management
                int routeChoice;
                do {
                    displayRouteManagementMenu();
                    cin >> routeChoice;

                    switch (routeChoice) {
                        case 1: { // Add New Route
                            string source, destination;
                            int distance, depH, depM, arrH, arrM;
                            float fare;

                            cout << "Enter Source: ";
                            cin.ignore();
                            getline(cin, source);
                            cout << "Enter Destination: ";
                            getline(cin, destination);
                            cout << "Enter Distance (km): ";
                            cin >> distance;
                            cout << "Enter Departure Time (HH MM): ";
                            cin >> depH >> depM;
                            cout << "Enter Arrival Time (HH MM): ";
                            cin >> arrH >> arrM;
                            cout << "Enter Fare: ";
                            cin >> fare;

                            system.addRoute(source, destination, distance, 
                                          Time(depH, depM), Time(arrH, arrM), fare);
                            break;
                        }
                        case 2: // View All Routes
                            system.displayAllRoutes();
                            break;
                        case 3: // Back to Main Menu
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                    }
                } while (routeChoice != 3);
                break;
            }
            case 3: { // Reservation Management
                int resChoice;
                do {
                    displayReservationManagementMenu();
                    cin >> resChoice;

                    switch (resChoice) {
                        case 1: { // Make New Reservation
                            int busId, routeId, seatNumber, day, month, year;
                            string passengerName, contactNumber;

                            system.displayAllBuses();
                            cout << "Enter Bus ID: ";
                            cin >> busId;

                            system.displayAllRoutes();
                            cout << "Enter Route ID: ";
                            cin >> routeId;

                            cout << "Enter Journey Date (DD MM YYYY): ";
                            cin >> day >> month >> year;
                            Date journeyDate(day, month, year);

                            system.displayAvailableSeats(busId, journeyDate);

                            cout << "Enter Seat Number: ";
                            cin >> seatNumber;
                            cout << "Enter Passenger Name: ";
                            cin.ignore();
                            getline(cin, passengerName);
                            cout << "Enter Contact Number: ";
                            getline(cin, contactNumber);

                            system.makeReservation(busId, routeId, journeyDate, 
                                                  passengerName, seatNumber, contactNumber);
                            break;
                        }
                        case 2: { // Cancel Reservation
                            int reservationId;
                            cout << "Enter Reservation ID to cancel: ";
                            cin >> reservationId;
                            system.cancelReservation(reservationId);
                            break;
                        }
                        case 3: { // View Available Seats
                            int busId, day, month, year;
                            cout << "Enter Bus ID: ";
                            cin >> busId;
                            cout << "Enter Date (DD MM YYYY): ";
                            cin >> day >> month >> year;
                            Date date(day, month, year);
                            system.displayAvailableSeats(busId, date);
                            break;
                        }
                        case 4: // Back to Main Menu
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                    }
                } while (resChoice != 4);
                break;
            }
            case 4: { // Reports
                int reportChoice;
                do {
                    displayReportsMenu();
                    cin >> reportChoice;

                    switch (reportChoice) {
                        case 1: // View All Reservations
                            system.displayAllReservations();
                            break;
                        case 2: // Back to Main Menu
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                    }
                } while (reportChoice != 2);
                break;
            }
            case 5: // Exit
                cout << "Thank you for using Bus Reservation System. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}