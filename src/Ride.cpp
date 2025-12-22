#include "Ride.h"
using namespace std;

Ride::Ride() : id(""), riderId(""), driverId(""), fare(0.0), distance(0.0),
        status(RideStatus::REQUESTED), requestTime(0) {}

Ride::Ride(const string& rideId, const string& riderId, time_t requestTime) 
        : id(rideId), riderId(riderId), driverId(""), fare(0.0),distance(0.0),
        status(RideStatus::REQUESTED), requestTime(requestTime) {}
