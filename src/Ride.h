#pragma once
#include <string>

enum class RideStatus { REQUESTED, ASSIGNED, IN_PROGRESS, COMPLETED, CANCELLED };

class Ride {
public:
    std::string id;
    std::string riderId;
    std::string driverId;
    RideStatus status;

    Ride() : id(""), riderId(""), driverId(""), status(RideStatus::REQUESTED) {}
    Ride(const std::string& rideId, const std::string& riderId)
        : id(rideId), riderId(riderId), driverId(""), status(RideStatus::REQUESTED) {}
};