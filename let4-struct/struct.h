#pragma once

#include <iostream>

struct MobilePhone {
    double weight;
    bool is_broken;
    double price;
};

void printMobilePhone(std::istream &, std::ostream &);
