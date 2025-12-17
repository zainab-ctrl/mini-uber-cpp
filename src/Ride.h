#pragma once
#include <string>
using namespace std;

enum class RideStatus { REQUESTED, ASSIGNED, IN_PROGRESS, COMPLETED, CANCELLED };

class Ride {
public:
    string id;
    string riderId;
    string driverId;
    double fare;
    RideStatus status;

    Ride() : id(""), riderId(""), driverId(""), fare(0), status(RideStatus::REQUESTED) {}
    Ride(const string& rideId, const string& riderId)
        : id(rideId), riderId(riderId), driverId(""), fare(fare), status(RideStatus::REQUESTED) {}
};