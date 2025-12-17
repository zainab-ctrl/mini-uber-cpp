#pragma once
#include "Driver.h"
#include "Rider.h"
#include "Ride.h"
#include <unordered_map>
#include <string>
using namespace std;

// Driver distance from rider
struct DriverDistance{
    double distance;
    Driver* driver;

    DriverDistance(double d, Driver* driver): distance(d), driver(driver) {}
    bool operator> (const DriverDistance& other) const {
        return distance > other.distance ; // min-heap
    }
};

class RideManager {
public:
    unordered_map<string, Driver> drivers;
    unordered_map<string, Rider> riders;
    unordered_map<string, Ride> rides;

    void addDriver(const Driver& driver);
    void addRider(const Rider& rider);
    double calculateDistance(double x1, double y1, double x2, double y2);
    void requestRide(const string& riderId);
    void rateDriver(string &riderId, double rating);
    void saveDriversData();
    void loadDriversData();
    void saveRidesData();
    void loadRidesData();
    double getFare(double distance);
    void showStatus();
};