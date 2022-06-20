
#include <iostream>
#include "./Host.h"
#include "./Person.h"
#include "../Start.h"
#include "../Place.h"
#include "../City.h"
#include "../includes/ArrayList.h"

using namespace std;

Host::Host() {}

void Host::showMenu(bool clrConsole)
{
    if (clrConsole)
        Start::clearConsole();
    cout << endl
         << "Hello " << Start::currentUser.full_Name << "," << endl
         << endl;

    cout << "Choose one of the following:" << endl;
    cout << "1. Add Place" << endl;
    cout << "2. View Places" << endl;
    cout << "3. View Reservations" << endl;
    cout << "4. Logout" << endl;

    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        addPlace();
        break;
    case 2:
        viewPlaces();
        break;
    case 3:
        viewReservations();
        break;
    case 4:
        Logout();
        break;
    default:
        showMenu();
        break;
    }
}

void Host::addPlace()
{
    places.Load("places");
    Start::clearConsole();
    Place place = Place();
    place.chooseCity();
    cout << "Enter Title: " << endl;
    cin.ignore();
    getline(cin, place.title);
    cout << "Enter number of guests: ";
    cin >> place.guests;
    cout << "Enter Description:" << endl;
    cin.ignore();
    getline(cin, place.desc);
    cout << "Enter number of beds: ";
    cin >> place.beds;
    cout << "Enter price: ";
    cin >> place.price;
    int plType;
    cout << endl;
    cout << "Place Types: \n1. Apartment\n"
         << "2. House\n"
         << "3. Secondary Unit\n"
         << "4. Unique Space\n"
         << "5. Bed and Breakfast\n"
         << "6. Boutique Hotel\n\n"
         << "Choose Place Type: ";
    cin >> plType;
    place.type = (PlaceType)plType;
    cdate dt = cdate();
    cout << "Place Availability: " << endl;

    cout << "Enter Start Date ";
    place.start_date.inputDate();
    cout << "Enter End Date ";
    place.end_date.inputDate();
    while (!Place::checkValidDate(place.end_date, place.start_date))
    {
        cout << "Invalid date (end date should be bigger than start date)" << endl;
        cout << "(dd/mm/yyyy)" << endl;

        cout << "Start Date ";
        place.start_date.inputDate();

        cout << "End Date: ";
        place.end_date.inputDate();
    }
    dt.currentDate();
    place.created_at = dt;

    place.host_id = Start::currentUser.id;
    place.place_id = places.lastID();
    places.Append(place);

    places.Save("places");

    Start::clearConsole();
    cout << "Place Added Successfully!" << endl
         << endl;
    showMenu(false);
}

void Host::viewPlaces()
{
    places.Load("places");
    City::cities.Load("cities");
    Start::clearConsole();
    ArrayList<Place> p;
    int cnt = 0;
    cout << "Places List:" << endl;
    for (int i = 0; i < places.Length(); ++i)
    {
        Place hostp = places.At(i);
        if (hostp.host_id == Start::currentUser.id)
        {
            cnt++;
            cout << cnt << "- " << hostp.title << endl;
            cout << "City Name : " << hostp.getCityName() << endl;
            cout << "Price : " << hostp.price << endl;
            p.Append(hostp);
            cout << endl;
        }
    }
    if (cnt == 0)
    {
        Start::clearConsole();
        cout << "You Don't have Places Yet." << endl;
        showMenu(false);
        return;
    }
    cout << endl;
    int size = p.Length();

    cout << "Enter place number to view place details or (0) to return to menu: " << endl;
    int idx;
    while (true)
    {
        cin >> idx;
        if (idx > 0 && idx <= p.Length())
            break;
        else if (idx == 0)
        {
            showMenu();
            return;
        }
        else
            cout << "No place has this number, Try Again." << endl;
    }
    Place pe = p.At((idx - 1));
    cout << "Availability: \n from " << pe.start_date.toString() << " to " << pe.end_date.toString() << endl;
    cout << "City : " << pe.getCityName() << '\n';
    cout << "type : " << pe.placeTypeStr() << '\n';
    cout << "guests : " << pe.guests << '\n';
    cout << "beds : " << pe.beds << '\n';
    cout << "created at : " << pe.created_at.toString() << endl;
    cout << "description : " << pe.desc << endl;

    char oper;
    while (true)
    {
        cout << endl
             << endl
             << "Enter 'e' to edit , 'r' to remove or 'm' to menu  ? \n";
        cin >> oper;
        if (oper == 'e')
        {
            cout
                << "to edit the place name press 1 and enter the new title \nto edit the city press 2 and enter the new city \n"
                   "to edit the price press 3 and enter the new price \nto edit the type press 4 and enter the new type \n"
                   "to edit the guests press 5 and enter the new guests \nto edit the beds press 6 and enter the new beds \n"
                   "to edit the start date press 7 and enter the new date \nto edit the end date press 8 and enter the new date \n"
                   "to edit the description press 9 and enter the new description \n";
            int op;
            cin >> op;

            switch (op)
            {
            case 1:
            {
                string t;
                cin >> t;
                pe.title = t;
                break;
            }
            case 2:
            {
                pe.city_id = pe.chooseCity(true);
                break;
            }
            case 3:
            {
                float pr;
                cin >> pr;
                pe.price = pr;
                break;
            }
            case 4:
            {
                int plType;
                cout << "Place Types: \n1. Apartment\n"
                     << "2. House\n"
                     << "3. Secondary Unit\n"
                     << "4. Unique Space\n"
                     << "5. Bed and Breakfast\n"
                     << "6. Boutique Hotel\n\n"
                     << "Choose Place Type: ";
                cin >> plType;
                pe.type = (PlaceType)plType;
                break;
            }
            case 5:
            {
                int gu;
                cin >> gu;
                pe.guests = gu;
                break;
            }
            case 6:
            {
                int bed;
                cin >> bed;
                pe.beds = bed;
                break;
            }
            case 7:
            {
                cout << "Enter start date ";
                cdate dt = cdate();
                dt.inputDate();
                pe.start_date = dt;
                break;
            }
            case 8:
            {
                cout << "Enter end date ";
                cdate dt = cdate();
                dt.inputDate();
                pe.end_date = dt;
                break;
            }
            case 9:
            {
                cout << "Enter description ";
                cin.ignore();
                getline(cin, pe.desc);
                break;
            }
            default:
                cout << "invalid operation\n";
            }
            places.Update(pe, pe.place_id);
            cout << endl
                 << "The Updated Data : " << endl
                 << endl;
            cout << "Place Name : " << pe.title << endl;
            cout << "City Name : " << pe.getCityName() << endl;
            cout << "Price : " << pe.price << endl;
            cout << "type : " << pe.placeTypeStr() << endl;
            cout << "guests : " << pe.guests << endl;
            cout << "beds : " << pe.beds << endl;
            cout << "description : " << pe.desc << endl;
            cout << "created at : " << pe.created_at.toString() << endl;
            cout << "Availability :  from " << pe.start_date.toString() << " to " << pe.end_date.toString() << endl;
            cout << endl;
        }
        else if (oper == 'r')
        {
            deletePlaceReservation(pe.place_id);
            places.deletebyID(pe.place_id);
            places.Save("places");
            viewPlaces();
            return;
        }
        else if (oper == 'm')
        {
            showMenu();
            return;
        }
        else
            cout << "invalid operation\n";

        places.Save("places");
    }
}

void Host::viewReservations()
{
    reservations.Load("reservations");
    places.Load("places");
    City::cities.Load("cities");
    Start::clearConsole();
    cout << "Reservations List : " << endl
         << endl;
    ArrayList<Reservation> hostRes;
    int cnt = 0;
    for (int i = 0; i < reservations.Length(); ++i)
    {
        Reservation reservation = reservations.At(i);
        Place *rplace = reservation.place();
        if (rplace == nullptr)
            continue;
        if (rplace->host_id == Start::currentUser.id)
        {
            cnt++;
            cout << cnt << "- " << rplace->title << endl;
            cout << "Start Date : " << rplace->start_date.toString() << endl;
            cout << "End Date : " << rplace->end_date.toString() << endl;
            hostRes.Append(reservation);
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
    int size = hostRes.Length();
    int idx;
    while (true)
    {
        cin >> idx;
        if (idx > 0 && idx <= size)
            break;
        else
            cout << "No reservation has this number, Try Again." << endl;
    }

    Reservation reservation = hostRes.At((idx - 1));
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
    int rchoice;
    cout << "Enter 1 to return to menu OR 2 to return to reservations: ";
    cin >> rchoice;
    if (rchoice == 1)
    {
        showMenu();
    }
    else
    {
        viewReservations();
    }
}
