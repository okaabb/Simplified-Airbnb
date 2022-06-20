#pragma once
#include <iostream>
#include "users/User.h"
#include "includes/LinkedList.h"

class Start
{
public:
    static User currentUser;
    static LinkedList<User> users;

    static void start();
    static void clearConsole();
};
