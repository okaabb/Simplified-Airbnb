#pragma once

#include <iostream>
#include "../Place.h"
#include "./Person.h"
#include "../includes/ArrayList.h"
#include "../Reservation.h"
using namespace std;

class Admin : Person
{
public:
    Admin();

    static void deletePlace(int PersonID);

    static void deleteReservation(int personID, bool traveler=true);

    static void showMenu(bool clrConsole = true);

    static void showPlaces();

    static void showReservations();

    static void showHost();

    static void showTravelers();
};
