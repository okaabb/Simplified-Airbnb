#include "./User.h"
#include <cassert>
#include <iostream>
#include <string>
#include <fstream>
#include "../includes/json.hpp"

using namespace std;
using json = nlohmann::json;

User::User(const string &fullName, const string &password, const string &nationality,
           const string &email, char gender, USER_TYPE type, int age, int id, const string &phoneNumber) : full_Name(fullName), password(password),
                                                                                                           nationality(
                                                                                                               nationality),
                                                                                                           email(email),
                                                                                                           gender(gender),
                                                                                                           type(type),
                                                                                                           age(age),
                                                                                                           id(id),
                                                                                                           phone(phoneNumber) {}
User::User() {}
json User::toJSON()
{
    json j;
    j["full_Name"] = this->full_Name;
    j["type"] = this->type;
    j["email"] = this->email;
    j["password"] = this->password;
    j["nationality"] = this->nationality;
    j["gender"] = this->gender;
    j["age"] = this->age;
    j["id"] = this->id;
    j["phone"] = this->phone;
    return j;
}

User::User(json j)
{
    this->type = j["type"];
    this->full_Name = j["full_Name"].get<string>();
    this->email = j["email"].get<string>();
    this->password = j["password"].get<string>();
    this->nationality = j["nationality"].get<string>();
    this->gender = j["gender"].get<char>();
    this->age = j["age"].get<int>();
    this->id = j["id"].get<int>();
    this->phone = j["phone"].get<string>();
}
