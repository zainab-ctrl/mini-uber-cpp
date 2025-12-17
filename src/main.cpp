#include "RideManager.h"
#include <iostream>
using namespace std;

int main() {
    RideManager manager;
    manager.loadDriversData();
    manager.loadRidesData();

    manager.addDriver(Driver("D1", "Alice", "03123748388", 2, 4));
    manager.addDriver(Driver("D2", "Bob", "27389998765", 4, 4));

    manager.addRider(Rider("U1", "Zainab", "0678868975", 34, 0));
    manager.addRider(Rider("U3", "Sana", "06876788888", 4, 4));

    manager.requestRide("U1");
    manager.requestRide("U2");

    manager.showStatus();

    manager.saveDriversData();
    manager.saveRidesData();

    return 0;
}