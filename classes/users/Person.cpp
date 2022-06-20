
#include <iostream>
#include "./Person.h"
#include "../Start.h"
#include "../Place.h"
#include "../City.h"
#include "../includes/ArrayList.h"

using namespace std;

ArrayList<Place> Person::places = ArrayList<Place>();
ArrayList<Reservation> Person::reservations = ArrayList<Reservation>();

Person::Person() {}

void Person::Logout()
{
    Start::currentUser = User();
    Start::clearConsole();
    Start::start();
}

void Person::deletePlaceReservation(int placeid)
{
    reservations.Load("reservations");
    for (int i = 0; i < reservations.Length(); ++i)
    {
        Reservation reservation = reservations.At(i);
        if (reservation.place_id == placeid) reservations.deleteAt(i);
    }
    reservations.Save("reservations");
}