#include "Rider.h"
#include "Pattern.h"
#include <string>
#include <iostream>
using namespace std;

Rider:: Rider() 
        : id(""), name(""), contact(""), x(0), y(0) {}

Rider::Rider(const string& id, const string& name, const string& contact, double lat, double lon) 
        : id(id), name(name), x(lat), y(lon)
{
    // Validate contact using regex
    if (!regex_match(contact, Pattern::pattern)) {
        cout << "Warning: Invalid contact number for rider " << name << endl;
        this->contact = "Invalid";  // leave empty if invalid
    } else {
        this->contact = contact;
    }
}
