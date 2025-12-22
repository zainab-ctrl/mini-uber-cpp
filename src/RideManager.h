# include "Driver.h"
# include "Rider.h"
# include "Ride.h"
#include <unordered_map>
#include<queue>
#include<string>
#include<vector>
using namespace std;

struct DriverDistance{ 
    double distance;
    Driver* driver;
    DriverDistance(double d, Driver* driver)
        : distance(d), driver(driver) {} 

        // operator >: works for sorting in a priority_queue (min-heap using greater)
        bool operator > (const DriverDistance& other) const { 
            return distance > other.distance ; // min-heap 
        } 
};

class RideManager {
private:
    double baseFare;
    double perKmRate;
    string passkey;
    int rideCounter;
public:
    unordered_map<string, Driver> drivers;
    unordered_map<string, Rider> riders;
    unordered_map<string, Ride> rides;
    queue<string> requests;
    vector<Ride> cancelledRides;
    vector<Ride> completedRides;    // Append-only data

    RideManager(string passkey);

    int login();
    int managerMenu();
    int userMenu();

    void addRider(const Rider& rider);
    void updateRider(const string& riderId, const string& contact, const string& newName, double x, double y);
    void requestRide(const string& riderId);  
    void processPendingRequests();
    bool AssignNearestDriver(Ride &ride);
    void completeRide(const string &rideId, const string &riderId);
    void cancelRide(const string &riderId, const string &rideId);
    vector<Ride> RiderBookings(const string &riderId);

    void addDriver(const Driver& driver);
    void removeDriver(const string& driverId);
    void updateDriver(const string& driverId, const string& contact, const string& newName, bool availability, double x, double y);
    void viewDrivers();
    void viewRiders();
    bool searchDriver(const string& driverId);
    bool searchRider(const string& riderId);
    // void sortByName();
    // void sortByRating();

    void activeRides();
    void completedRidesList();

    void saveDriversData();
    void saveCompletedRidesData();
    void saveCancelledRidesData();
    void saveRidersData();
    void loadDriversData();
    void loadCompletedRidesData();
    void loadCancelledRidesData();
    void loadRidersData();
    void savePasskey();
    time_t getCurrentTime();

    void fareRates(double newBaseFare, double newPerKmRate);
    void rateDriver(const string &driverId, double rating);
    void setPasskey(string passkey);

    double calculateDistance(double x1, double y1, double x2, double y2);
    double getFare(double distance);
    string statustoString(RideStatus s);
    string getPassKey();

    vector<string> activeDriver();
    vector<string> mostBookingsRider();
    double earningPerDriver(const string& driverId);
    double AverageDistance();
    double AverageRating();
    double totalEarnings();
    void RideStatistics();
    void analytics();

    void showStatus();
    void searchDriverCompare(const string &driverId);
    void searchRiderCompare(const string &riderId);
    void compareDriverSorts();
};
