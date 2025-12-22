#include "RideManager.h"
#include "Search.h"
#include "Sort.h"
#include <iostream>
#include <queue>
#include <cmath>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <sstream>
using namespace std;

RideManager::RideManager(const string passkey) 
            : passkey (passkey), baseFare(50), perKmRate(10), rideCounter(0) {}

// ================== Menus ==================
int RideManager::login() {
    cout << "\n * * * MINI-UBER APP * * *\n";
    cout << "1. User\n2. Manager\n";
    cout << "Select option (1 or 2): ";
    int op;
    cin >> op;
    return op;
}

int RideManager::userMenu() {
    cout << "\n * * * USER INTERFACE * * *\n";
    cout << "1. Register\n2. Request Ride\n3. Cancel Ride\n4. Complete Ride\n";
    cout << "5. Ride Bookings\n6. Update Rider\n7. Exit\n";
    cout << "Select option: ";
    int op;
    cin >> op;
    return op;
}

int RideManager::managerMenu() {
    cout << "\n * * * MANAGER INTERFACE * * *\n";
    cout << "1. Add Driver\n2. Remove Driver\n3. Update Driver Status\n4. View Drivers\n";
    cout << "5. View Active Rides\n6. View Completed Rides\n7. Statistics & Analytics\n";
    cout << "8. Manage Fare Rates\n9. Show Complete Status\n10. Manage Password\n";
    cout << "11. View Riders\n12. Search Driver (Linear vs Binary)\n13. Search Rider (Linear vs Binary)\n";
    cout << "14. Compare Bubble Sort vs Quick Sort (Drivers)\n15. Process Pending Requests\n16. Exit\n";
    cout << "Select option: ";
    int op;
    cin >> op;
    return op;
}

// ================== Manager Features ==================
void RideManager::addDriver(const Driver &driver) {
    for(auto &d : drivers){
        if(d.second.id == driver.id){
            cout << "Driver id already exit" << endl;
            return;
        }
    }
    drivers[driver.id] = driver;
    cout << "Driver added successfully " << endl;
}

void RideManager::removeDriver(const string &driverId) {
    auto it = drivers.find(driverId);
    if (it != drivers.end()) {
        drivers.erase(it);
        cout << "Driver removed successfully.\n";
    } else {
        cout << "Driver not found.\n";
    }
}

void RideManager::updateDriver(const string &driverId, const string &contact, const string &newName, bool availability, double x, double y) {
    auto it = drivers.find(driverId);
    if (it != drivers.end()) {
        it->second.name = newName;
        it->second.contact = contact;
        it->second.available = availability;
        it->second.x = x;
        it->second.y = y;
        cout << "Driver updated successfully.\n";
        processPendingRequests();
        return;
    }
    cout << "Driver not found.\n";
    return;
}

void RideManager::viewDrivers() {
    if (drivers.empty()) {
        cout << "No drivers available.\n";
        return;
    }
    for (const auto &pair : drivers) {
        const Driver &d = pair.second;
        cout << "ID: " << d.id
             << " | Name: " << d.name
             << " | contact: " << d.contact
             << " | x: " << d.x
             << " | y: " << d.y
             << " | Rating count: " << d.ratingCount
             << " | Total Rating: " << d.totalRating
             << " | Status: " << (d.available ? "Available" : "Busy") << endl;
    }
}

void RideManager::viewRiders(){
    if (riders.empty()) {
        cout << "No riders available.\n";
        return;
    }
    for (const auto &pair : riders) {
        const Rider &r = pair.second;
        cout << "ID: " << r.id
             << " | Name: " << r.name
             << " | Contact: " << r.contact
             << " | x: " << r.x
             << " | y: " << r.y << endl;
    }
}

bool RideManager::searchDriver(const string &driverId){
    auto it = drivers.find(driverId);

    if (it == drivers.end()) {
        cout << "Driver not found.\n";
        return false;
    }

    Driver &d = it->second;
     cout << "ID: " << d.id
             << " | Name: " << d.name
             << " | contact: " << d.contact
             << " | x: " << d.x
             << " | y: " << d.y
             << " | Rating count: " << d.ratingCount
             << " | Total Rating: " << d.totalRating
             << " | Status: " << (d.available ? "Available" : "Busy") << endl;
    return true;
}

bool RideManager::searchRider(const string &riderId){
    auto it = riders.find(riderId);
    if (it == riders.end()) {
        cout << "Rider not found.\n";
        return false;
    }

    Rider &r = it->second;
    cout << "ID: " << r.id
             << " | Name: " << r.name
             << " | Contact: " << r.contact
             << " | x: " << r.x
             << " | y: " << r.y << endl;
    return true;
}

void RideManager::activeRides() {
    if (rides.empty()) {
        cout << "No active rides.\n";
        return;
    }
    for (const auto &pair : rides) {
        const Ride &r = pair.second;
        cout << "Ride ID: " << r.id
             << " | Driver ID: " << r.driverId
             << " | Rider ID: " << r.riderId
             << " | Status: " << static_cast<int>(r.status)
             << endl;
    }
}

void RideManager::completedRidesList() {
    if (completedRides.empty()) {
        cout << "No completed rides.\n";
        return;
    }
    for (const auto &r : completedRides) {
        cout << "Ride ID: " << r.id
             << " | Driver ID: " << r.driverId
             << " | Rider ID: " << r.riderId
             << " | Status: " << static_cast<int>(r.status)
             << endl;
    }
}

// ================== User Features ==================
void RideManager::addRider(const Rider& rider) {
    riders[rider.id] = rider;
    cout << "Id assigned to rider is " << rider.id << endl;
}

void RideManager::updateRider(const string &riderId, const string &newName, const string &contact, double x, double y) {
    auto it = riders.find(riderId);
    if (it != riders.end()) {
        it->second.name = newName;
        it->second.contact = contact;
        it->second.x = x;
        it->second.y = y;
        cout << "Rider updated successfully.\n";
        return;
    }
    cout << "Rider not found.\n";
    return;
}

void RideManager::requestRide(const string &riderId) {
    if (riders.find(riderId) == riders.end()) {
        cout << "Rider not found.\n";
        return;
    }

    // Create ride
    string rideId = "R" + to_string(++rideCounter);        // When empty size is 0
    time_t time = getCurrentTime();
    rides[rideId] = Ride(rideId, riderId, time);
    Ride &ride = rides[rideId];             // & use to point to the original ride to update
    if (!AssignNearestDriver(ride))
        requests.push(ride.id); //Added rideId to the queue not ride whose status is requested
}

void RideManager::processPendingRequests(){
    if(requests.empty()) return;
    string rideId = requests.front();
    Ride &ride = rides[rideId];
    AssignNearestDriver(ride);
}

bool RideManager::AssignNearestDriver(Ride &ride){
    priority_queue<DriverDistance, vector<DriverDistance>, greater<DriverDistance>> pq;    // By default max-Heap

    for (auto &pair : drivers) {
        Driver &driver = pair.second;           // Not making copy but pointing to original
        if (!driver.available) continue;    // Ignore busy driver

        double dist = calculateDistance(driver.x, driver.y, riders[ride.riderId].x, riders[ride.riderId].y);
        pq.push(DriverDistance(dist, &driver));
    }

    if (pq.empty()) {
        cout << "No driver available. Request added to queue.\n";
        return false;
    }

    auto best = pq.top();   // minimum distance driver at the top of queue
    pq.pop();

    Driver *selectedDriver = best.driver;
    selectedDriver->available = false;
    ride.driverId = selectedDriver->id;
    ride.distance = best.distance;
    ride.fare = getFare(best.distance);
    ride.status = RideStatus::ASSIGNED;

    if (!requests.empty() && requests.front() == ride.id)
        requests.pop();

    cout << "Ride " << ride.id << " assigned to driver " << selectedDriver->id
         << " and rider " << ride.riderId << " | Fare: Rs " << ride.fare << endl;
    return true;
}

void RideManager::cancelRide(const string &riderId, const string &rideId) {
    auto it = rides.find(rideId);
    if (it == rides.end()) {
        cout << "Ride not found.\n";
        return;
    }

    Ride &ride = it->second;

    if (ride.riderId != riderId) {
        cout << "Ride cannot be cancelled. Rider ID mismatch.\n";
        return;
    }

    if (ride.status == RideStatus::IN_PROGRESS || ride.status == RideStatus::COMPLETED) {
        cout << "Ride cannot be cancelled after it has started or completed.\n";
        return;
    }

    ride.status = RideStatus::CANCELLED;
    
    if (drivers.find(ride.driverId) != drivers.end())
        drivers[ride.driverId].available = true;

    cancelledRides.push_back(ride);
    rides.erase(it);
    cout << "Ride cancelled successfully.\n";
    processPendingRequests();
}

void RideManager::completeRide(const string &rideId, const string &riderId) {
    auto it = rides.find(rideId);
    if (it == rides.end()) {
        cout << "Ride not found.\n";
        return;
    }

    Ride &ride = it->second;

    if (ride.riderId != riderId) {
        cout << "Ride cannot be completed. Rider ID mismatch.\n";
        return;
    }

    ride.status = RideStatus::COMPLETED;
    if (drivers.find(ride.driverId) != drivers.end())
        drivers[ride.driverId].available = true;

    double rating;
    cout << "Enter rating (1-5): "; cin >> rating;
    rateDriver(ride.driverId, rating);
    completedRides.push_back(ride);
    rides.erase(it);
    cout << "Ride completed successfully.\n";
    processPendingRequests();
}

vector<Ride> RideManager::RiderBookings(const string &riderId) {
    vector<Ride> result;

    for (auto &pair : rides){
        if (pair.second.riderId == riderId)
            result.push_back(pair.second);
    }

    for (auto &r : completedRides){
        if (r.riderId == riderId)
            result.push_back(r);
    }
    return result; 
}

// ================== Utility ==================
double RideManager::totalEarnings(){
    double e = 0;
    for (auto &r : completedRides){
        e += r.fare;
    }
    return e;
}

double RideManager::calculateDistance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));   // Eucliean Distance Formula
} 

double RideManager::getFare(double distance) {
    return baseFare + distance * perKmRate;
}

string RideManager::statustoString(RideStatus s){
    switch(s){
        case RideStatus::REQUESTED:
            return "REQUESTED";
        break;
        case RideStatus::ASSIGNED:
            return "ASSIGNED";
        break;
        case RideStatus::IN_PROGRESS:
            return "IN_PROGRESS";
        break;
        case RideStatus::COMPLETED:
            return "COMPLETED";
        break;
        case RideStatus::CANCELLED:
            return "CANCELLED";
        break;
        default:
            return "UNKNOWN";
    }
}

vector<string> RideManager::activeDriver(){
    unordered_map<string, int> count;   // count have id and number of count
    int maxRides = 0;
    for(auto &r : completedRides){
     count[r.driverId]++;           // Count map on the driverId increments each time when driverId found in completedRides
     maxRides = max(maxRides, count[r.driverId]);
    }
    vector<string> result;      // DriverIDs list
    for(auto &c : count){
        if(c.second == maxRides)
           result.push_back(c.first);
    }
    return result;
}

vector<string> RideManager::mostBookingsRider(){
    unordered_map<string, int> count;
    int maxRides = 0;
    for(auto &r : completedRides){
        count[r.riderId]++;
        maxRides = max(maxRides, count[r.riderId]);
    }
    vector<string> result;  // RderIds list
    for(auto &c : count){
        if(c.second == maxRides)
            result.push_back(c.first);
    }
    return result;
}

double RideManager::earningPerDriver(const string& driverId){
   double earn = 0;
    for(auto &r : completedRides){
        if(r.driverId == driverId)
            earn += r.fare;
    }
    return earn;
}

double RideManager::AverageDistance(){
    double sum = 0;
    int count = 0;
    for(auto& ride : completedRides){
        sum += ride.distance;
        count++; 
    }
    return (count == 0) ? 0.0 : sum / count;
}

double RideManager::AverageRating(){
    double sum = 0;
    int count = 0;

    for(auto &p : drivers){
        sum += p.second.totalRating;
        count += p.second.ratingCount;
    }
    return (count == 0) ? 0 : sum / count;  // Check to avoid infinity errors
}

void RideManager::RideStatistics(){
    cout << "\n=== Summary Statistics ===\n";
    cout << "Rides Completed:" << completedRides.size() << endl;
    cout << "Rides Cancelled:" << cancelledRides.size() << endl;
    cout << "Total Earnings:" <<  totalEarnings() << endl;
    cout << "Average driver rating:" << AverageRating() << endl;
    cout << "Average distance:" << AverageDistance() << endl;
}

void RideManager::analytics(){
    cout << "\n=== Analytics ===\n";
    cout << "Earnings Per Driver" << endl;
    for (auto &d : drivers){
        double earn = earningPerDriver(d.first);
        cout << d.first << " | " << "Earnings:" << earn << endl;
    }
    auto driver = activeDriver();
    cout << "Most Active Driver:" << endl;
    for (auto &id : driver){
        Driver &d = drivers[id];
        cout << d.id << " | " << d.name << endl;
    }
    auto rider = mostBookingsRider();
    cout << "Most Booking Rider:"  << endl;
    for (auto &id : rider){
        Rider &r = riders[id];
        cout << r.id << " | " << r.name << endl;
    }
}

void RideManager::rateDriver(const string &driverId, double rating) {
    if (rating < 1 || rating > 5) {
        cout << "Rating must be in range 1-5.\n";
        return;
    }
    drivers[driverId].totalRating += rating;
    drivers[driverId].ratingCount++;
    cout << "Driver rated successfully.\n";
}

void RideManager::fareRates(double newBaseFare, double newPerKmRate) {
    baseFare = newBaseFare;
    perKmRate = newPerKmRate;
    cout << "Fare rates updated successfully.\n";
    cout << "Base Fare: " << baseFare << " | Per KM Rate: " << perKmRate << endl;
}

void RideManager::setPasskey(string passkey){
    this->passkey = passkey;
    cout << "Password updated successfully.\n";
}

string RideManager::getPassKey(){
    return passkey;
}

void RideManager::saveDriversData(){
    ofstream out("DriversData.txt");
    for (auto &pair : drivers){
        const Driver &driver = pair.second;
        out << driver.id  << " | " << driver.name << " | "
        << driver.contact << " | "  << driver.x << " | "
        << driver.y << " | " << driver.totalRating << " | "
        << driver.ratingCount << endl;
    }
    out.close();
}

void RideManager::saveCompletedRidesData(){
    ofstream out("CompletedRidesData.txt");
    for (auto &ride : completedRides){
        out << ride.id << " | " << ride.riderId << " | "
        << ride.driverId << " | "  << ride.fare << " | "  
        << " | "  << ride.distance << " | " << ride.requestTime << endl;
    }
    out.close();
}

void RideManager::saveCancelledRidesData(){
    ofstream out("CancelledRidesData.txt");
    for (auto &ride : cancelledRides){
        out << ride.id << " | " << ride.riderId << " | "
        << ride.driverId << " | "  << ride.fare << " | "  
        << " | "  << ride.distance << " | " << ride.requestTime << endl;
    }
    out.close();
}

void RideManager::saveRidersData(){
    ofstream out("RidersData.txt");
    for (auto &pair : riders){
        const Rider &rider = pair.second;
        out << rider.id << " | " << rider.name << " | "
        << rider.contact << " | "  << rider.x << " | " << rider.y << endl;
    }
    out.close();
}

void RideManager::loadDriversData(){
    ifstream in("DriversData.txt");
    if (!in) return;

    Driver d;
    string line, a;
    while(getline(in, line)){
    stringstream ss(line);
    ss >> d.id >> a >> d.name >> a >> d.contact >> a
       >> d.x >> a >> d.y >> a >> d.totalRating >> a >> d.ratingCount;
        d.available = true;
    drivers[d.id] = d;
    }
    in.close();
}

void RideManager::loadCompletedRidesData(){
    ifstream in("CompletedRidesData.txt");
    if (!in) return;

    Ride r;
    string line, a;
    while(getline(in, line)){
    stringstream ss(line);
    ss >> r.id >> a >> r.riderId >> a >> r.driverId >> a
       >> r.fare >> a >> r.distance >> a >> r.requestTime;
        r.status = RideStatus::COMPLETED;
    completedRides.push_back(r);
    }
    in.close();
}

void RideManager::loadCancelledRidesData(){
    ifstream in("CancelledRidesData.txt");
    if (!in) return;

    Ride r;
    string line, a;
    while(getline(in, line)){
    stringstream ss(line);
    ss >> r.id >> a >> r.riderId >> a >> r.driverId >> a
       >> r.fare >> a >> r.distance >> a >> r.requestTime;
        r.status = RideStatus::CANCELLED;
    cancelledRides.push_back(r);
    }
    in.close();
}

void RideManager::loadRidersData(){
    ifstream in("RidersData.txt");
    if (!in) return;

    Rider r;
    string line, a;
    while(getline(in, line)){
    stringstream ss(line);
    ss >> r.id >> a >> r.name >> a >> r.contact >> a
       >> r.x >> a >> r.y;
    riders[r.id] = r;
    }
    in.close();
}

void RideManager::savePasskey(){
    ofstream out("Passkey.txt");
    out << passkey;
    out.close();
}

time_t RideManager::getCurrentTime(){
     return chrono::system_clock::to_time_t(chrono::system_clock::now());
}

void RideManager::showStatus() {
    cout << "\nRiders:\n";
    for (auto &pair : riders) {
        const Rider &rider = pair.second;
        cout  <<  rider.id << ": " << rider.name << endl;
    }

    cout << "\nDrivers:\n";
    for (auto &pair : drivers) {
        const Driver &driver = pair.second;
        cout << driver.id << ": " << driver.name
             << " (" << (driver.available ? "Available" : "Busy") << ")\n";
    }

    cout << "\nRides:\n";
    for (auto &pair : rides) {
        const Ride &ride = pair.second;
        cout << pair.first << ": Rider " << ride.riderId
             << ", Driver " << ride.driverId
             << ", Status " << statustoString(ride.status) << endl;
    }
}

void RideManager::searchDriverCompare(const string &driverId) {

    vector<Driver> driverList;
    for (auto &p : drivers)
        driverList.push_back(p.second);

    Search::searchCompare<Driver>(
        driverList,
        driverId,
        [](const Driver& d) { return d.id; },
        [](const Driver& d) {
            cout << "Driver Found:\n";
            cout << "ID: " << d.id
                 << " | Name: " << d.name
                 << " | Contact: " << d.contact << endl;
        }
    );
}

void RideManager::searchRiderCompare(const string &riderId) {

    vector<Rider> riderList;
    for (auto &p : riders)
        riderList.push_back(p.second);

    Search::searchCompare<Rider>(
        riderList,
        riderId,
        [](const Rider& r) { return r.id; },
        [](const Rider& r) {
            cout << "Rider Found:\n";
            cout << "ID: " << r.id
                 << " | Name: " << r.name
                 << " | Contact: " << r.contact << endl;
        }
    );

}

void RideManager::compareDriverSorts() {
    vector<Driver> driverList;
    for (auto &p : drivers)
        driverList.push_back(p.second);

    if (driverList.empty()) {
        cout << "No drivers available.\n";
        return;
    }

    // Make copies so both algorithms sort SAME data
    vector<Driver> bubbleList = driverList;
    vector<Driver> quickList  = driverList;

    // ================= BUBBLE SORT =================
    auto startBubble = chrono::high_resolution_clock::now();

    Sort::bubbleSort<Driver>(
        bubbleList,
        [](const Driver &a, const Driver &b) {
            return a.totalRating > b.totalRating;   // DESCENDING
        }
    );

    auto endBubble = chrono::high_resolution_clock::now();

    auto bubbleTime =
        chrono::duration_cast<chrono::microseconds>(endBubble - startBubble).count();

    // ================= QUICK SORT =================
    auto startQuick = chrono::high_resolution_clock::now();

    Sort::quickSort<Driver>(
        quickList,
        [](const Driver &a, const Driver &b) {
            return a.totalRating > b.totalRating;   // DESCENDING
        }
    );

    auto endQuick = chrono::high_resolution_clock::now();

    auto quickTime =
        chrono::duration_cast<chrono::microseconds>(endQuick - startQuick).count();

    // ================= OUTPUT =================
    cout << "\n=== SORT COMPARISON (DRIVERS BY RATING) ===\n";
    cout << "Bubble Sort Time : " << bubbleTime << " microseconds\n";
    cout << "Quick Sort Time  : " << quickTime << " microseconds\n";

    cout << "\nTop 5 Drivers (After Quick Sort):\n";
    for (int i = 0; i < min(5, (int)quickList.size()); i++) {
        cout << i + 1 << ". "
             << quickList[i].name
             << " | Rating: " << quickList[i].totalRating << endl;
    }
}
