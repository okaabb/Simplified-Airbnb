#pragma once

#include "./json.hpp"
#include <iostream>
using json = nlohmann::json;
using namespace std;
#ifndef AIRBNB_CDATE_H
#define AIRBNB_CDATE_H

class cdate
{
public:

    int day, month, year;
    bool empty = true;
    json toJSON();

    cdate();
    cdate(int d, int m, int y);
    cdate(json j);

    void inputDate(bool required = true);

    void currentDate();
    string toString();
};

#endif
