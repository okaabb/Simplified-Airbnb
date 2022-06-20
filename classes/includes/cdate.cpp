#pragma once

#include "./cdate.h"
#include <iostream>
#include <string>
#include "./json.hpp"
#include <ctime>

using json = nlohmann::json;
using namespace std;

json cdate::toJSON()
{
    json j;
    j["day"] = day;
    j["month"] = month;
    j["year"] = year;
    return j;
}

cdate::cdate(int d, int m, int y)
{
    this->day = d;
    this->month = m;
    this->year = y;
    empty = false;
}

cdate::cdate() {}

cdate::cdate(json j)
{
    day = j["day"].get<int>();
    month = j["month"].get<int>();
    year = j["year"].get<int>();
    empty = false;
}

void cdate::inputDate(bool required)
{
    int monthDays[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    char fill = '/';
    string entered_date;
    int m;
    int y;
    int d;

    cout << "(dd/mm/yyyy): " << endl;
    cin >> entered_date;
    if (entered_date == "-" && !required)
        return;
    if (entered_date.length() != 10)
    {
        cout << "Invalid Date!" << endl;
        inputDate();
        return;
    }
    d = stoi(entered_date.substr(0, 2));
    m = stoi(entered_date.substr(3, 2));
    y = stoi(entered_date.substr(6));

    if (d > 0 && d <= 31 && m > 0 && m <= 12 && y > 0 && d <= monthDays[m-1])
    {
        this->day = d;
        this->month = m;
        this->year = y;
        empty = false;
    }
    else
    {
        cout << "Invalid Date!" << endl;
    }
    bool valid = true;
    cdate x;
    x.currentDate();
    if (y < x.year)
    {
        valid = false;
    }
    else if (y == x.year)
    {
        if (m < x.month)
        {
            valid = false;
        }
        else if (m == x.month)
        {
            if (d < x.day)
            {
                valid = false;
            }
        }
    }
    if (!valid)
    {
        cout << "Invalid date (enter future dates)" << endl;
        inputDate();
    }
}

void cdate::currentDate()
{
    time_t t = time(0);
    tm *now = localtime(&t);
    day = now->tm_mday;
    month = now->tm_mon + 1;
    year = now->tm_year + 1900;
    empty = false;
}

string cdate::toString()
{
    return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
}
