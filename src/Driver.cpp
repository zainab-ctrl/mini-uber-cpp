#include "Driver.h"
#include "Pattern.h"
#include <string>
#include <iostream>

Driver::Driver()
    : id(""), name(""), contact(""), x(0.0), y(0.0), available(true), totalRating(0.0), ratingCount(0) {}

Driver::Driver(const string& id, const string& name, const string& contact, double x, double y)
    : id(id), name(name), x(x), y(y), available(true), totalRating(0.0), ratingCount(0)
{
        // Regex validation for contact
    if (regex_match(contact, Pattern::pattern))
        this->contact = contact;
    else {
        this->contact = "Invalid";
        cout << "Warning: Invalid contact number for driver " << name << endl;
    }
}

void Driver::addRating(double rating) {
    if (rating >= 0.0 && rating <= 5.0) {   // 0 - 5 range
        totalRating += rating;
        ratingCount++;
    }
}

double Driver::getAverageRating() const {
    return (ratingCount == 0) ? 0.0 : totalRating / ratingCount;
}

