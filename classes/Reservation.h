#pragma once
#include <string>
#include <list>
#include "Place.h"
#include <map>
using namespace std;

class Reservation
{
public:
    int reservation_id, place_id, traveler_id;
    cdate start_date, end_date, created_at;

    int getID();
    Reservation();
    Reservation(json j);
    void showPlaceReservations(int place_id);
    static void reserve(Place p);
    Reservation(int reservationId, int travelerId, int placeId, const cdate &startDate, const cdate &endDate, const cdate &createdAt);
    Place *place();
    json toJSON();
};