#pragma once
#include <string>

class Driver {
public:
    std::string id;
    std::string name;
    double latitude;
    double longitude;
    bool available;

    Driver() : id(""), name(""), latitude(0), longitude(0), available(true) {}
    Driver(const std::string& id, const std::string& name, double lat, double lon)
        : id(id), name(name), latitude(lat), longitude(lon), available(true) {}
};