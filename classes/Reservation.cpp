//
// Created by ahmed kassem on 20/04/2022.
//
#include "Reservation.h"
#include "Place.h"
#include "./includes/cdate.h"
#include "./users/Person.h"
#include "Start.h"

Reservation::Reservation() {}

Reservation::Reservation(int reservationId, int travelerId, int placeId, const cdate &startDate, const cdate &endDate, const cdate &createdAt) // ReservationStatus status
    : reservation_id(reservationId), traveler_id(travelerId), place_id(placeId), start_date(startDate), end_date(endDate),
      created_at(createdAt)
{
}

json Reservation::toJSON()
{
    // //make reservation file
    json j;
    j["reservation_id"] = this->reservation_id;
    j["traveler_id"] = this->traveler_id;
    j["place_id"] = this->place_id;
    j["start_date"] = this->start_date.toJSON();
    j["end_date"] = this->end_date.toJSON();
    j["created_at"] = this->created_at.toJSON();
    return j;
}

Reservation::Reservation(json j)
{
    this->reservation_id = j["reservation_id"].get<int>();
    this->traveler_id = j["traveler_id"].get<int>();
    this->place_id = j["place_id"].get<int>();
    this->start_date = cdate(j["start_date"]);
    this->end_date = cdate(j["end_date"]);
    this->created_at = cdate(j["created_at"]);
}

void Reservation::showPlaceReservations(int place_id)
{
    bool found = 0;
    ArrayList<Reservation> temp;
    for (int i = 0; i < Person::reservations.Length(); i++)
    {
        Reservation resr = Person::reservations.At(i);
        if (resr.place_id == place_id)
        {
            if (!found)
                cout << endl
                     << "This place is reserved at: " << endl;
            found = 1;
            cdate x, y;
            x.day = resr.start_date.day;
            x.month = resr.start_date.month;
            x.year = resr.start_date.year;
            y.day = resr.end_date.day;
            y.month = resr.end_date.month;
            y.year = resr.end_date.year;
            cout << "    "
                 << "from :" << x.day << '/' << x.month << '/' << x.year << ' ' << "to :" << y.day << '/' << y.month << '/'
                 << y.year << endl;
        }
    }
}

void Reservation::reserve(Place p)
{
    Start::clearConsole();

    cout << "Enter start date and end date of reservation:" << endl;
    cdate sdate, edate;
    string s_date, e_date;
    cout << "Start Date ";
    sdate.inputDate();
    cout << "End Date ";
    edate.inputDate();
    Place h;

    while (!Place::checkValidDate(sdate, p.start_date) || Place::checkValidDate(edate, p.end_date) || !h.checkValidDate(edate, sdate))
    {
        cout << "invalid date (start and end date should be within the place availability and end date should be bigger than start date)" << endl;
        cout << "(dd/mm/yyyy)" << endl;

        cout << "Start Date ";
        sdate.inputDate(false);

        cout << "End Date ";
        edate.inputDate(false);
    }
    bool valid = true;
    if (Person::reservations.Length() == 0)
    {
        cdate created_at;
        created_at.currentDate();

        Person::reservations.Append(
            Reservation(Person::reservations.lastID(), Start::currentUser.id, p.place_id, sdate, edate,
                        created_at));
        Person::reservations.Save("reservations");
        cout << "Reservation successfully placed!" << endl;
    }
    else
    {
        for (int i = 0; i < Person::reservations.Length(); i++)
        {
            if (Person::reservations.At(i).place_id == p.place_id)
            {
                Place x;
                Reservation r = Person::reservations.At(i);
                if (!(x.checkValidDate(sdate, p.start_date) && x.checkValidDate(p.end_date, edate)))
                { // to check if it's in the host determined range
                    valid = false;
                    break;
                }
                if (!(((x.checkValidDate(r.start_date, sdate) && x.checkValidDate(r.start_date, edate))) || (x.checkValidDate(sdate, r.end_date) && x.checkValidDate(edate, r.end_date))))
                {
                    valid = false;
                    break;
                }
            }
        }
        if (valid)
        {
            cdate created_at;
            created_at.currentDate();
            Person::reservations.Append(
                Reservation(Person::reservations.lastID(), Start::currentUser.id, p.place_id, sdate, edate,
                            created_at));
            Person::reservations.Save("reservations");
            Start::clearConsole();
            cout << "Reservation successfully placed!" << endl;
        }
        else
        {
            cout << "Place is not available in this duration " << endl
                 << endl
                 << "To re-input dates enter (1): ";
            int retr;
            cin >> retr;
            if (retr == 1)
                return reserve(p);
        }
    }
}

int Reservation::getID()
{
    return reservation_id;
}

Place *Reservation::place()
{
    return Person::places.find(place_id);
}
