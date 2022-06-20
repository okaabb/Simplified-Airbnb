#include <string>
#include <list>
#include "./includes/json.hpp"
#include "./includes/ArrayList.h"

using json = nlohmann::json;

using namespace std;

class City
{
public:
    City();

    int city_id;
    string name;
    int getID();
    City(int city_id, const string &name);
    static ArrayList<City> cities;
    static City findCity(int id);

    json toJSON();
    City(json j);
};