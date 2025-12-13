#include "RideManager.h"
#include <iostream>

int main() {
    RideManager manager;

    manager.addDriver(Driver("D1", "Alice", 0, 0));
    manager.addDriver(Driver("D2", "Bob", 0, 0));

    manager.addRider(Rider("U1", "John"));
    manager.addRider(Rider("U2", "Emma"));

    manager.requestRide("U1");
    manager.requestRide("U2");

    manager.showStatus();

    return 0;
}