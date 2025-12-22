#pragma once
#include <string>
using namespace std;

class Driver {
public:
    string id, name, contact;
    double x, y;
    bool available;
    double totalRating;
    int ratingCount;

    Driver();
    Driver(const string& id, const string& name, const string& contact, double x, double y);

    void addRating(double rating);
    double getAverageRating() const;
};
