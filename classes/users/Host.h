#pragma once

#include <iostream>
#include "../Place.h"
#include "./Person.h"
#include "../includes/ArrayList.h"
#include "../Reservation.h"

using namespace std;

class Host : Person
{
public:
    Host();

    static void showMenu(bool clrConsole = true);

    static void addPlace();

    static void viewPlaces();

    static void viewReservations();
};
