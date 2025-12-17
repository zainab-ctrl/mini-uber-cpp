#include "Rider.h"
#include "Pattern.h"
#include<string>
#include<iostream>
using namespace std;

Rider:: Rider(const string& id, const string& name, const string& contact, double lat, double lon) 
        : id(id), name(name), x(lat), y(lon) 
        {
            if (!(regex_match(contact, Pattern::pattern))){
                cout << "Rider " << name << " have Invalid contact." << endl;
                this->contact = "";
            }
		     else{
                this->contact = contact; 
             }   
        }

void Rider::setContact(const string &contact){
        this->contact = contact;
}
