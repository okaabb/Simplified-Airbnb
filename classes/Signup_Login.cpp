#include "Signup_Login.h"

#include <iostream>
#include <fstream>
#include <string>
#include "includes/json.hpp"
#include "users/User.h"
#include "includes/LinkedList.h"
#include "Start.h"
//#include <conio.h>

using json = nlohmann::json;

int Signup_Login::Log_in()
{
    string s_password, email;

    cout << "E-mail: ";
    cin >> email;
    cout << "Password: ";
    cin >> s_password;

    Start::users.Load("Users");

    User *loggedUser = Start::users.FindUser(email, s_password);

    if (loggedUser == NULL)
    {
        return -1;
    }
    Start::currentUser = *loggedUser;
    return loggedUser->type;

    // read json file;
    //  if(id==idj&&pass==passj&&type==typej)--> logged in successfully w nsave el id fe user_id  -->h show hosts methods in main, t-->traveler,a-->admin;
    // return 1 host
    // return 2 traveler
    // return 3 admin
    // return 0 not successfully logged in
}
bool checkmail(string mail)
{
    bool at = false, com = false;
    for (int i = 0; i < mail.size(); i++)
    {
        if (mail[i] == '@')
        {
            at = true;
            break;
        }
    }
    if (mail.size() < 5)
        return false;
    if (mail.substr(mail.size() - 4, 4) == ".com")
        com = true;
    return com && at;
}

bool Signup_Login::Sign_up()
{
    User user;
    Start::users.Load("Users");

    cout << "Type 1 For Host (OR) 2 for Traveler " << endl;
    int type;
    cin >> type;
    user.type = (USER_TYPE)type;
    if (user.type != 1 && user.type != 2)
    {
        cout << "Invalid Type" << endl;
        Start::clearConsole();
        return false;
    }
    user.id = Start::users.lastID();
    cout << "Full Name: " << endl;
    cin.ignore();
    getline(cin, user.full_Name);
    cout << "E-mail: ";
    cin >> user.email;
    while (!checkmail(user.email))
    {
        cout << "Enter a valid e-mail: ";
        cin >> user.email;
    }
    cout << "Password: ";

    cin >> user.password;
    cout << "Nationality: ";
    cin >> user.nationality;
    cout << "Age: ";
    cin >> user.age;
    cout << "Gender (m) for male and (f) for female: ";
    cin >> user.gender;
    cout << "Phone: ";
    cin >> user.phone;

    Start::users.Append(user);
    // save in json
    Start::users.Save("Users");
    Start::clearConsole();
    cout << "Signed up successfully" << endl;

    return true;
}
