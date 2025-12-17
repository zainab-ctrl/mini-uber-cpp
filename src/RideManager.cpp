#include "RideManager.h"
#include <iostream>
#include <queue>
#include <cmath>
#include <fstream>
using namespace std;

void RideManager::addDriver(const Driver& driver) {
    drivers[driver.id] = driver;
}

void RideManager::addRider(const Rider& rider) {
    riders[rider.id] = rider;
}

double RideManager::calculateDistance(double x1, double y1, double x2, double y2) {
   return sqrt( pow(x2 - x1, 2) + pow(y2 - y1, 2) ); //Euclidean formula to calculate distance from cooridnates
}

void RideManager::rateDriver(string &rideId, double rating){
     if (rides.find(rideId) == rides.end()) { 
        cout << "Ride not found\n";
        return;
    }

    if(rating < 1 || rating > 5){
        cout << "Rating must be in range of 1-5 " << endl;
        return;
    }

    string driverId  = rides[rideId].driverId;  //Driver assign to the ride
    drivers[driverId].totalRating += rating;
    drivers[driverId].countRating++;
    cout << "Driver rated successfully" << endl;
}

void RideManager::saveDriversData(){
    ofstream out("DriverData.txt");
    for (auto&  d : drivers){
        out << d.second.id << " | "
            << d.second.name << " | "
            << d.second.contact << " | "
            << d.second.x << " | "
            << d.second.y << " | "
            << d.second.totalRating << " | "
            << d.second.countRating  << endl;
    }
    out.close();
    cout << "Drivers Data Saved Successfully." << endl;
}

void RideManager::loadDriversData(){
    ifstream in("DriverData.txt");
    if (!in) return;

    Driver d;
    while (in >> d.id >> d.name 
            >> d.contact >> d.x
            >> d.y >> d.totalRating >> d.countRating
         ){
            d.available = true;
            drivers[d.id] = d;
         }
    
    in.close();
    cout << "Drivers Data loaded Successfully." << endl;
}

void RideManager::saveRidesData(){
    ofstream out("RidesData.txt");
    for (auto&  r : rides){
        out << r.second.id << " | "
            << r.second.riderId << " | "
            << r.second.driverId << " | "
            << r.second.fare  << endl;
    }
    out.close();
    cout << "Rides Data Saved Successfully." << endl;
}

void RideManager::loadRidesData(){
    ifstream in("RidesData.txt");
    if (!in) return;

    Ride r;
    while (in >> r.id >> r.riderId 
            >> r.driverId >> r.fare
         ){
            r.status = RideStatus::REQUESTED;
            rides[r.id] = r;
         }
    
    in.close();
    cout << "Rides Data loaded Successfully." << endl;
}

double RideManager::getFare(double distance){
    return 50 + distance * 10;  // base + per km
}

void RideManager::requestRide(const string& riderId) {
    priority_queue <DriverDistance, 
                    vector <DriverDistance>,
                    greater <DriverDistance>
                    > pq;     // heap

    if (riders.find(riderId) == riders.end()) { 
        cout << "Rider not found\n";
        return;
    }

    for (auto &value : drivers) {
        Driver& driver = value.second; //second means value in the map or dict
        if (!driver.available) 
            continue;   // Skip the not available drivers
        double dist = calculateDistance(
                driver.x, driver.y,
                riders[riderId].x, riders[riderId].y
                );
        pq.push(DriverDistance(dist, &driver));   // DriverDistance struct
    }

    if (pq.empty()) {
        cout << "No driver available\n";
        return;
    }

    auto best = pq.top();
    Driver* selectedDriver = best.driver; 
    double DriverDistace = best.distance; 

    selectedDriver->available = false;

    string rideId = "R" + to_string(rides.size() + 1); // ride list or map size was 0 at start
    Ride ride(rideId, riderId);
    ride.driverId = selectedDriver->id;
    ride.fare = getFare(DriverDistace);
    ride.status = RideStatus::ASSIGNED;
    rides[rideId] = ride;

    cout << "Ride " << rideId << " assigned to driver " << selectedDriver->name << " | Fare: Rs " << getFare(DriverDistace) << endl;
}

void RideManager::showStatus() {
    cout << "\nDrivers:\n";
    for (auto& pair : drivers) {
        const string& id = pair.first;
        Driver& driver = pair.second;
        cout << id << ": " << driver.name
                  << " (" << (driver.available ? "Available" : "Busy") << ")\n";
    }

    cout << "\nRides:\n";
    for (auto& pair : rides) {
        const string& id = pair.first;
        Ride& ride = pair.second;
        cout << id << ": Rider " << ride.riderId
                  << ", Driver " << ride.driverId
                  << ", Status " << static_cast<int>(ride.status) << endl;
    }
}