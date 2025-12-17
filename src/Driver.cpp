#include "Driver.h"
#include "Pattern.h"
#include<string>
#include<iostream>
using namespace std;

Driver::Driver(const string &id, const string &name, const string &contact, double lat, double lon)  
        : id(id), name(name), x(lat), y(lon), available(true), totalRating(0), countRating(0) 
        {
            if (!(regex_match(contact, Pattern::pattern))){
                cout << "Driver " << name << " have Invalid contact." << endl;
                this->contact = "";
            }
		     else{
                this->contact = contact; 
             }   
        }

void Driver::setContact(const string &contact){
        this->contact = contact;
}

