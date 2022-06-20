#include "Start.h"
#include <iostream>
#include <fstream>
#include <string>
// source
#include "Signup_Login.h"
#include "./users/Person.h"
#include "./users/Admin.h"
#include "./users/Host.h"
#include "./users/Traveler.h"


using namespace std;

User Start::currentUser = User();
LinkedList<User> Start::users = LinkedList<User>();

void Start::start()
{
    Signup_Login slg;
    cout << "hello to airbnb" << endl;
    cout << "press 1: Sign up" << endl
         << "press 2: Login" << endl;
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        slg.Sign_up();
        Start::start();
        break;
    case 2:
        int user_type = slg.Log_in();

        clearConsole();
        if (user_type == -1)
        {
            cout << "Invalid E-Mail or Password" << endl;
            Start::start();
            return;
        }
        cout << "logged in successfully" << endl;

        if (user_type == HOST)
        {
            Host::showMenu(false);
        }
        if (user_type == TRAVELER)
        {
            Traveler::showMenu(false);
        }
        if (user_type == ADMIN)
        {
            Admin::showMenu(false);
        }
        break;
    }
}

void Start::clearConsole()
{
#if defined _WIN32
    system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    // std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined(__APPLE__)
    system("clear");
#endif
};
