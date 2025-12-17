#pragma once
#include <string>
using namespace std;

class Driver {
public:
    string id;
    string name;
    string contact;
    double x, y;
    bool available;
    double totalRating;
    int countRating;

    Driver() : id(""), name(""), contact(""), x(0), y(0), available(true) {}
    Driver(const string& id, const string& name, const string& contact, double lat, double lon);

    void setContact(const string &contact);

    double getAverageRating(){
        if(countRating == 0)
            return 0.0;
        return totalRating / countRating;
    }

};