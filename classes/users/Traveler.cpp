#include <iostream>
#include "./Traveler.h"
#include "./Person.h"
#include "../Start.h"
#include "../Place.h"
#include "../City.h"
#include "../includes/ArrayList.h"

using namespace std;

Traveler::Traveler() {}

void Traveler::showMenu(bool clrConsole)
{
    if (clrConsole)
        Start::clearConsole();
    cout << endl
         << "Hello " << Start::currentUser.full_Name << "," << endl
         << endl;

    cout << "Choose one of the following:" << endl;
    cout << "1. Search Places" << endl;
    cout << "2. View Reservations" << endl;
    cout << "3. Logout" << endl;

    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        Place::searchPlace();
        break;
    case 2:
        viewReservations();
        break;
    case 3:
        Logout();
        break;
    default:
        showMenu();
        break;
    }
}

void Traveler::viewReservations()
{
    reservations.Load("reservations");
    places.Load("places");
    City::cities.Load("cities");
    Start::clearConsole();
    ArrayList<Reservation> trav;
    int cnt = 0;
    cout << "Reservations List : " << endl
         << endl;
    for (int i = 0; i < reservations.Length(); ++i)
    {
        Reservation reservation = reservations.At(i);
        Place *rplace = reservation.place();
        if (rplace == nullptr)
            continue;
        if (reservation.traveler_id == Start::currentUser.id)
        {
            cnt++;
            cout << (cnt) << "- " << rplace->title << endl;
            cout << "Start Date : " << reservation.start_date.toString() << endl;
            cout << "End Date : " << reservation.end_date.toString() << endl;
            trav.Append(reservation);
            cout << endl;
        }
    }
    if (cnt == 0)
    {
        Start::clearConsole();
        cout << "You Don't have Reservations Yet." << endl;
        showMenu(false);
        return;
    }
    cout << endl
         << endl;
    cout << "Select the number of the reservation to show its place in detail: " << endl;
    int size = trav.Length();
    int idx;
    while (true)
    {
        cin >> idx;
        if (idx > 0 && idx <= size)
            break;
        else
            cout << "No reservation has this number, Try Again." << endl;
    }
    Reservation reservation = trav.At((idx - 1));
    Place *rplace = reservation.place();

    cout << "City Name : " << rplace->getCityName() << endl;
    cout << "Place Name : " << rplace->title << endl;
    cout << "Price : " << rplace->price << endl;
    cout << "Start Date : " << rplace->start_date.toString() << endl;
    cout << "End Date : " << rplace->end_date.toString() << endl;
    cout << "Creation date : " << rplace->created_at.toString() << endl;
    cout << "Number of Beds : " << rplace->beds << endl;
    cout << "Number of Guests : " << rplace->guests << endl;
    cout << "Type of The Room : " << rplace->type << endl;
    cout << "description : " << rplace->desc << endl;
    User *hst = rplace->host();
    cout << "host name: " << hst->full_Name << endl;
    cout << "host phone: " << hst->phone << endl
         << endl;
    int tchoice;
    cout << "Enter 1 to return to menu OR 2 to return to reservations: ";
    cin >> tchoice;
    if (tchoice == 1)
    {
        showMenu();
    }
    else
    {
        viewReservations();
    }
}
