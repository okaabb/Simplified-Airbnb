#include "City.h"

City::City(int city_id, const string &name) : city_id(city_id), name(name) {}

ArrayList<City> City::cities = ArrayList<City>();

City City::findCity(int city_id)
{
    for (int i = 0; i < cities.Length(); i++)
    {
        if (cities.At(i).city_id == city_id)
        {
            return cities.At(i);
        }
    }
}

json City::toJSON()
{
    json j;
    j["id"] = this->city_id;
    j["name"] = this->name;
    return j;
}

City::City(json j)
{
    this->city_id = j["id"].get<int>();
    this->name = j["name"].get<string>();
}

City::City()
{
}

int City::getID()
{
    return city_id;
}
