#include "RideManager.h"
#include <iostream>

void RideManager::addDriver(const Driver& driver) {
    drivers[driver.id] = driver;
}

void RideManager::addRider(const Rider& rider) {
    riders[rider.id] = rider;
}

void RideManager::requestRide(const std::string& riderId) {
    Driver* selectedDriver = nullptr;
    for (auto& pair : drivers) {
        Driver& driver = pair.second;
        if (driver.available) {
            selectedDriver = &driver;
            break;
        }
    }

    if (!selectedDriver) {
        std::cout << "No available drivers.\n";
        return;
    }

    std::string rideId = "R" + std::to_string(rides.size() + 1);
    Ride ride(rideId, riderId);
    ride.driverId = selectedDriver->id;
    ride.status = RideStatus::ASSIGNED;

    rides[rideId] = ride;
    selectedDriver->available = false;

    std::cout << "Ride " << rideId << " assigned to driver " << selectedDriver->name << "\n";
}

void RideManager::showStatus() {
    std::cout << "\nDrivers:\n";
    for (auto& pair : drivers) {
        const std::string& id = pair.first;
        Driver& driver = pair.second;
        std::cout << id << ": " << driver.name
                  << " (" << (driver.available ? "Available" : "Busy") << ")\n";
    }

    std::cout << "\nRides:\n";
    for (auto& pair : rides) {
        const std::string& id = pair.first;
        Ride& ride = pair.second;
        std::cout << id << ": Rider " << ride.riderId
                  << ", Driver " << ride.driverId
                  << ", Status " << static_cast<int>(ride.status) << "\n";
    }
}