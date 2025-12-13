#pragma once
#include <string>

class Rider {
public:
    std::string id;
    std::string name;

    Rider() : id(""), name("") {}
    Rider(const std::string& id, const std::string& name)
        : id(id), name(name) {}
};