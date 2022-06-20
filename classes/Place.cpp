
#include <iostream>
#include <string>
#include "Place.h"
#include "City.h"
#include "Start.h"
#include "./includes/cdate.h"
#include "string"
#include "users/Person.h"
#include "users/Traveler.h"
#include "Reservation.h"
#include "./includes/Arraylist.h"
#include "Start.h"

using namespace std;

Place::Place(int placeId, int cityId, int hostId, int guests, int beds, float price, const string &title,
             const string &desc,
             const cdate &startDate, const cdate &endDate, const cdate &createdAt, PlaceType type) : place_id(placeId),
                                                                                                     city_id(cityId),
                                                                                                     host_id(hostId),
                                                                                                     guests(guests),
                                                                                                     beds(beds),
                                                                                                     price(price),
                                                                                                     title(title),
                                                                                                     desc(desc),
                                                                                                     start_date(
                                                                                                         startDate),
                                                                                                     end_date(endDate),
                                                                                                     created_at(
                                                                                                         createdAt),
                                                                                                     type(type)
{
}

Place::Place()
{
}

bool Place::checkValidDate(cdate placeDate, cdate userSrchDate)
{
    bool valid = false;
    /// 0 -> date greater than the place date
    if (placeDate.year > userSrchDate.year)
    { // if user year is bigger no need to continue checking
        valid = true;
    } // else if it equals it then we will check months
    else if (placeDate.year == userSrchDate.year)
    {
        if (placeDate.month > userSrchDate.month)
        { // no need to check the days
            valid = true;
        } // else if the months are equals we have to check the days
        else if (placeDate.month == userSrchDate.month)
        {
            if (placeDate.day >= userSrchDate.day)
            {
                valid = true;
            }
        }
    }
    return valid;
}
User *Place::host()
{
    Start::users.Load("users");
    return Start::users.FindUser(host_id);
}

void Place::showSearchPlaces(ArrayList<Place> places)
{
    Start::clearConsole();
    if (places.Length() == 0)
    {
        Start::clearConsole();
        cout << "No Places Found!" << endl;
        Traveler::showMenu(false);
        return;
    }
    cout << "Places List:" << endl;
    for (int i = 0; i < places.Length(); ++i)
    {
        Place plc = places.At(i);

        cout << (i + 1) << "- " << plc.title << endl;
        cout << "City Name : " << plc.getCityName() << endl;
        cout << "Price : " << plc.price << endl
             << endl;
    }
    cout
        << endl;
    cout << "Enter place number to view place details or (0) to return to menu: " << endl;
    int idx;
    // cout << "choose a number from 1 to " << places.Length() << ":" << endl;
    while (true)
    {
        cin >> idx;
        if (idx > 0 && idx <= places.Length())
            break;
        else if (idx == 0)
        {
            Traveler::showMenu();
            return;
        }
        else
            cout << "No place has this number, Try Again." << endl;
    }

    Place pe = places.At((idx - 1));
    cout << "Availability:\nfrom " << pe.start_date.toString() << " to " << pe.end_date.toString() << endl;
    cout << "Type : " << pe.placeTypeStr() << '\n';
    cout << "City : " << pe.getCityName() << '\n';
    cout << "Guests : " << pe.guests << '\n';
    cout << "Beds : " << pe.beds << '\n';
    cout << "Created At : " << pe.created_at.toString() << endl;
    cout << "Description : " << pe.desc << endl;
    User *hst = pe.host();
    cout << "host name :" << hst->full_Name << endl;
    cout << "host phone :" << hst->phone << endl;

    Reservation k;
    k.showPlaceReservations(pe.place_id);
    // cout << "To Explore enter (1) for Reservation enter (2) to menu enter (3)" << endl;

    cout << endl
         << "Enter (1) to make a reservation or (2) to return to places: " << endl;
    int rchoice;
    cin >> rchoice;
    if (rchoice == 1)
    {
        Reservation::reserve(pe);
        int in;
        while (true)
        {
            cout << "Want to search more press 1 to go to menu press 2: ";
            cin >> in;
            if (in == 1 || in == 2)
            {
                break;
            }
            else
            {
                cout << "Please choose between 1 or 2 " << endl;
            }
        }
        if (in == 1)
        {
            searchPlace();
        }
        else
        {
            Traveler::showMenu();
        }
    }
    else
        showSearchPlaces(places);
}

void Place::searchPlace()
{

    Person::places.Load("places");
    Person::reservations.Load("reservations");
    // float
    int startPrice, endPrice;
    cdate startDate, endDate;
    int city_id;
    // string cityName, float startPrice, float endPrice, cdate startDate, cdate endDate;
    string start_price, end_price;
    // we could delete some of if stats but for the sake of simplicity and tracking

    Place plc;
    plc.city_id = plc.chooseCity(true);
    cout << "Enter [-] For Blank " << endl;
    cout << "Start Price: ";
    cin >> start_price;
    cout << "End Price: ";
    cin >> end_price;
    if (start_price == "-")
        startPrice = 0;
    else
        startPrice = stoi(start_price);

    if (end_price == "-")
        endPrice = 10000000; // should be a huge number for comparsion
    else
        endPrice = stoi(end_price);

    cout << "(dd/mm/yyyy)" << endl;

    cout << "Start Date ";
    startDate.inputDate(false);

    cout << "End Date ";
    endDate.inputDate(false);
    // conflict between checking and '-'
    while (!startDate.empty && !endDate.empty && !checkValidDate(endDate, startDate))
    {
        cout << "invalid date (end date should be bigger than start date)" << endl;
        cout << "(dd/mm/yyyy)" << endl;

        cout << "Start Date ";
        startDate.inputDate(false);

        cout << "End Date ";
        endDate.inputDate(false);
    }
    Person p;
    int i;
    i = Person::places.Length() - 1;
    /// they could search by any of these (start date , end date , city ,  price range)

    ArrayList<Place> temp = ArrayList<Place>();
    Place currP;
    while (i >= 0)
    { /// to search the whole list of places
        currP = Person::places.At(i);

        if ((plc.city_id == 0 || currP.city_id == plc.city_id) && // city
            (end_price == "-" || currP.price <= endPrice) &&      // start_price
            (start_price == "-" || currP.price >= startPrice) &&  // end_price
            (startDate.empty || checkValidDate(startDate, currP.start_date)) &&
            (endDate.empty || checkValidDate(currP.end_date, endDate)) )
        {
            temp.Append(currP);
        }
        i--;
    }

    Place::showSearchPlaces(temp);
}

string Place::getCityName()
{
    City c = City::findCity(city_id);
    return c.name;
}

json Place::toJSON()
{
    json j;
    j["place_id"] = this->place_id;
    j["city_id"] = this->city_id;
    j["host_id"] = this->host_id;
    j["guests"] = this->guests;
    j["beds"] = this->beds;
    j["price"] = this->price;
    j["title"] = this->title;
    j["type"] = this->type;
    j["desc"] = this->desc;
    j["start_date"] = this->start_date.toJSON();
    j["end_date"] = this->end_date.toJSON();
    j["created_at"] = this->created_at.toJSON();
    return j;
}

Place::Place(json j)
{
    this->type = (PlaceType)j["type"].get<int>();
    this->place_id = j["place_id"].get<int>();
    this->city_id = j["city_id"].get<int>();
    this->host_id = j["host_id"].get<int>();
    this->guests = j["guests"].get<int>();
    this->beds = j["beds"].get<int>();
    this->price = j["price"].get<float>();
    this->title = j["title"].get<string>();
    this->desc = j["desc"].get<string>();
    this->start_date = cdate(j["start_date"]);
    this->end_date = cdate(j["end_date"]);
    this->created_at = cdate(j["created_at"]);
}

int Place::chooseCity(bool edt)
{

    if (City::cities.Length() == 0)
        City::cities.Load("cities");

    cout << "Choose City: " << endl
         << endl;
    int cities_length = City::cities.Length();
    for (int i = 0; i < cities_length; ++i)
    {
        cout << (i + 1) << ". " << City::cities.At(i).name << endl;
    }
    cout << "Enter City Number ";
    if (edt)
        cout << "or 0 for no input";
    cout << ": ";
    int city_choice;
    cin >> city_choice;
    if (city_choice == 0 && edt)
        return city_id;
    Start::clearConsole();

    if (city_choice <= cities_length && city_choice > 0)
        city_id = City::cities.At(city_choice - 1).city_id;
    else
    {
        chooseCity();
    }
    return city_id;
}

int Place::getID()
{
    return place_id;
}

string Place::placeTypeStr()
{
    return placesTypes[type];
}
