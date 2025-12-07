#ifndef DATE_H
#define DATE_H

#include <string>
#include <iostream>
using namespace std;

struct date {
    int day{};
    int month{};
    int year{};

    string stringDate() const {
        return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    }
};

#endif