#pragma once
#include "Driver.h"
#include "Rider.h"
#include "Ride.h"
#include <unordered_map>
#include <queue>
#include <string>

class RideManager {
public:
    std::unordered_map<std::string, Driver> drivers;
    std::unordered_map<std::string, Rider> riders;
    std::unordered_map<std::string, Ride> rides;

    void addDriver(const Driver& driver);
    void addRider(const Rider& rider);
    void requestRide(const std::string& riderId);
    void showStatus();
};