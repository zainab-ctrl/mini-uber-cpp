#pragma once
#include <string>
using namespace std;

class Rider {
public:
    string id;
    string name;
    string contact;
    double x, y;

    Rider();
    Rider(const string& id, const string& name, const string& contact, double lat, double lon) ;

};