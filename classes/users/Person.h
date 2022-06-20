#pragma once

#include <iostream>
#include "../Place.h"
#include "../includes/ArrayList.h"
#include "../Reservation.h"

using namespace std;

class Person
{
public:
    static ArrayList<Place> places;
    static ArrayList<Reservation> reservations;
    Person();
    static void Logout();
    static void deletePlaceReservation(int placeid);
};