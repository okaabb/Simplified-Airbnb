#pragma once
#include <iostream>
#include <string>
#include "../includes/json.hpp"
using json = nlohmann::json;
using namespace std;

enum USER_TYPE
{
    HOST = 1,
    TRAVELER = 2,
    ADMIN = 3

};
class User
{
public:
    string full_Name, password, nationality, email, phone;
    char gender;
    int age, id;
    USER_TYPE type;

    User(const string &fullName, const string &password, const string &nationality,
         const string &email, char gender, USER_TYPE type, int age, int id, const string &phoneNumber);
    User();
    json toJSON();
    User(json j);
};
