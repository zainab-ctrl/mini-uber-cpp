#pragma once
#include <string>
#include<chrono>
#include<ctime>
using namespace std;

enum class RideStatus { REQUESTED, ASSIGNED, IN_PROGRESS, COMPLETED, CANCELLED };

class Ride {
public:
    string id;
    string riderId;
    string driverId;
    double fare;
    double distance;
    time_t  requestTime;
    RideStatus status;

    Ride();
    Ride(const string& rideId, const string& riderId, time_t requestTime);
};
