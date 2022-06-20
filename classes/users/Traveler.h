#pragma once

#include <iostream>
#include "../Place.h"
#include "./Person.h"
#include "../includes/ArrayList.h"
#include "../Reservation.h"
using namespace std;

class Traveler : Person
{
public:
    Traveler();

    static void showMenu(bool clrConsole = true);

    static void viewReservations();
};
