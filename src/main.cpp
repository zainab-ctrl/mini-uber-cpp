#include "RideManager.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Load passkey from file
string loadPasskey() {
    ifstream in("Passkey.txt");
    string passKey;
    if (in) {
        in >> passKey;
    } else {
        passKey = "123"; // default
    }
    in.close();
    return passKey;
}

int main() {
    string passkey = loadPasskey();
    RideManager manager(passkey);

    // Load saved data
    manager.loadDriversData();
    manager.loadCompletedRidesData();
    manager.loadCancelledRidesData();
    manager.loadRidersData();

    while (true) {
        int choice = manager.login();

        if (choice == 1) { // User
            while (true) {
                int userChoice = manager.userMenu();
                switch (userChoice) {
                    case 1: { // Register Rider
                        string id, name, contact;
                        double x, y;
                        cin.ignore();
                        cout << "Enter Name: "; getline(cin, name);
                        cout << "Enter Contact: "; cin >> contact;
                        cout << "Enter Location (x y): "; cin >> x >> y;
                        id = "RR" + to_string(manager.riders.size() + 1);

                        Rider rider(id, name, contact, x, y);
                        manager.addRider(rider);
                        break;
                    }
                    case 2: { // Request Ride
                        string riderId;
                        cout << "Enter Rider ID: "; cin >> riderId;
                        manager.requestRide(riderId);
                        break;
                    }
                    case 3: { // Cancel Ride
                        string riderId, rideId;
                        cout << "Enter Rider ID: "; cin >> riderId;
                        cout << "Enter Ride ID: "; cin >> rideId;
                        manager.cancelRide(riderId, rideId);
                        break;
                    }
                    case 4: { // Complete Ride
                        string riderId, rideId;
                        cout << "Enter Rider ID: "; cin >> riderId;
                        cout << "Enter Ride ID: "; cin >> rideId;
                        manager.completeRide(rideId, riderId);
                        break;
                    }
                    case 5: { // Rider Bookings
                        string riderId;
                        cout << "Enter Rider ID: "; cin >> riderId;
                        auto rides = manager.RiderBookings(riderId);
                        for (auto &r : rides) {
                            cout << "Ride ID: " << r.id
                                 << " | Driver ID: " << r.driverId
                                 << " | Status: " << manager.statustoString(r.status) << endl;
                        }
                        if(rides.empty())
                          cout << "No Bookings" << endl;
                        break;
                    }
                    case 6: { // Update Rider
                        string id, name, contact;
                        double x, y;
                        cout << "Enter Rider ID: "; cin >> id;
                        cout << "Enter new Name: "; cin >> name;
                        cout << "Enter new Contact: "; cin >> contact;
                        cout << "Enter x, y: "; cin >> x >> y;
                        manager.updateRider(id, name, contact, x, y);
                        break;
                    }
                    case 7:   goto save_and_exit;
                    default:
                        cout << "Invalid Input\n";
                }
            }

        } else if (choice == 2) { // Manager
            string password;
            cout << "Enter password: "; cin >> password;
            if (password != manager.getPassKey()) {
                cout << "Invalid password\n";
                continue;
            }
            while (true) {
                int managerChoice = manager.managerMenu();
                switch (managerChoice) {
                    case 1: { // Add Driver
                        string id, name, contact;
                        double x, y;
                        cin.ignore();
                        cout << "Enter Driver ID: "; cin >> id;
                        cin.ignore();
                        cout << "Enter Name: "; getline(cin, name);
                        cout << "Enter Contact: "; cin >> contact;
                        cout << "Enter Location (x y): "; cin >> x >> y;

                        Driver driver(id, name, contact, x, y);
                        manager.addDriver(driver);
                        break;
                    }
                    case 2: { // Remove Driver
                        string id;
                        cout << "Enter Driver ID: "; cin >> id;
                        manager.removeDriver(id);
                        break;
                    }
                    case 3: { // Update Driver
                        string id, name, contact;
                        bool available;
                        double x, y;
                        cout << "Enter Driver ID: "; cin >> id;
                        cout << "Enter new Name: "; cin >> name;
                        cout << "Enter new Contact: "; cin >> contact;
                        cout << "Availability (1=Available,0=Busy): "; cin >> available;
                        cout << "Enter x, y: "; cin >> x >> y;
                        manager.updateDriver(id, contact, name, available, x, y);
                        break;
                    }
                    case 4: manager.viewDrivers(); break;
                    case 5: manager.activeRides(); break;
                    case 6: manager.completedRidesList(); break;
                    case 7: {
                        manager.RideStatistics();
                        manager.analytics();
                        break;
                    }
                    case 8: {
                        double base, perKm;
                        cout << "Enter new Base Fare: "; cin >> base;
                        cout << "Enter new Per KM Rate: "; cin >> perKm;
                        manager.fareRates(base, perKm);
                        break;
                    }
                    case 9: manager.showStatus(); break;
                    case 10: {
                        string newPass;
                        cout << "Enter new Password: "; cin >> newPass;
                        manager.setPasskey(newPass);
                        break;
                    }
                    case 11:  manager.viewRiders();   break;
                    case 12: {
                        string id;
                        cout << "Enter Driver ID: ";
                        cin >> id;
                        manager.searchDriverCompare(id);
                        break;
                    }
                    case 13: {
                        string id;
                        cout << "Enter Rider ID: ";
                        cin >> id;
                        manager.searchRiderCompare(id);
                        break;
                    }
                    case 14: {
                        manager.compareDriverSorts();
                        break;
                    }
                     case 15: {
                        manager.processPendingRequests();
                        break;
                    }
                    case 16:  goto save_and_exit;
                    default: cout << "Invalid Input\n";
                }
            }

        } else {
            cout << "Invalid Input\n";
        }
    }

save_and_exit:
    // Save all data before exiting
    manager.saveDriversData();
    manager.saveCompletedRidesData();
    manager.saveRidersData();
    manager.savePasskey();
    manager.saveCancelledRidesData();

    cout << "Data saved. Exiting program.\n";
    return 0;
}
