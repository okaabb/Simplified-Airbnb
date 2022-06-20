#pragma once
#include <string>
#include <list>
#include "./includes/cdate.h"
#include "./includes/json.hpp"
#include "./includes/Arraylist.h"
#include "./users/User.h"

using json = nlohmann::json;

using namespace std;

enum PlaceType
{
    APARTMENT = 0,
    HOUSE = 1,
    SECONDARY_UNIT = 2,
    UNIQUE_SPACE = 3,
    BED_BREAKFAST = 4,
    BOUTIQUE_HOTEL = 5
};

const string placesTypes[] = {
    "Apartment",
    "House",
    "Secondary Unit",
    "Unique Space",
    "Bed & Breakfast",
    "Boutique Hotel"};
class Place
{
public:
    int place_id, city_id, host_id, guests, beds;
    float price;
    string title, desc;
    cdate start_date, end_date, created_at;
    PlaceType type;

    string placeTypeStr();
    int getID();
    Place(int placeId, int cityId, int guests, int host_id, int beds, float price, const string &title, const string &desc,
          const cdate &startDate, const cdate &endDate, const cdate &createdAt, PlaceType type);

    Place();
    // void
    int chooseCity(bool edt = false);
    User *host();
    static void searchPlace();
    static void showSearchPlaces(ArrayList<Place> p);
    static bool checkValidDate(cdate placeDate, cdate userSrchDate);
    string getCityName();
    json toJSON();
    Place(json j);
};