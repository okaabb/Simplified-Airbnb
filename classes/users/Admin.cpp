#include <iostream>
#include "./Admin.h"
#include "./Person.h"
#include "../Start.h"
#include "../Place.h"
#include "../City.h"
#include "../includes/ArrayList.h"

using namespace std;

Admin::Admin() = default;

void Admin::showPlaces()
{
    places.Load("places");
    City::cities.Load("cities");
    Start::clearConsole();
    cout << "Places List: " << endl
         << endl;
    if(!places.Length()){
        Start::clearConsole();
        cout << "No Places Found!";
        showMenu(false);
        return;
    }
    for (int i = 0; i < places.Length(); ++i)
    {
        Place p = places.At(i);
        cout << (i + 1) << "- " << p.title << endl;
        cout << "City Name : " << p.getCityName() << endl;
        cout << "Price : " << p.price << endl;
    }
    cout << endl;
    while (true)
    {
        cout << "enter 'c' to Choose a place or 'm' to menu: \n";
        char achoice;
        cin >> achoice;
        if (achoice == 'm')
        {
            showMenu();
            return;
        }
        cout << "Enter place number to view place details: ";
        int pid;
        cin >> pid;

        Place pe = places.At(pid - 1);
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
            cout << "Enter 'r' to remove ,' e' to edit or 'x' to menu \n";

            cin >> oper;
            if (oper == 'x')
                break;
            else if (oper == 'e')
            {

                cout
                        << "to edit the title press 1 and enter the new title \nto edit the city press 2 and enter the new city \n"
                           "to edit the price press 3 and enter the new price \nto edit the type press 4 and enter the new type \n"
                           "to edit the guests press 5 and enter the new guests \nto edit the beds press 6 and enter the new beds \n"
                           "to edit the start date press 7 and enter the new date \nto edit the end date press 8 and enter the new date \n";
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
                        pe.chooseCity(true);
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
                        cout << endl;
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
                    default:
                        cout << "invalid operation\n";
                }
                places.Update(pe, pid);
            }
            else if (oper == 'r')
            {
                deletePlaceReservation(pe.place_id);
                places.deletebyID(pe.place_id);
                places.Save("places");
                showPlaces();
                return;
            }
            else
                cout << "invalid operation\n";

            places.Save("places");
        }
    }
}

void Admin::showMenu(bool clrConsole)
{
    if (clrConsole)
        Start::clearConsole();
    cout << endl
         << "Hello " << Start::currentUser.full_Name << "," << endl
         << endl;

    cout << "Choose one of the following:" << endl;
    cout << "1. View Places" << endl;
    cout << "2. View Reservations" << endl;
    cout << "3. View Hosts" << endl;
    cout << "4. View Travelers" << endl;
    cout << "5. Logout" << endl;

    int choice;
    cin >> choice;
    switch (choice)
    {
        case 1:
            showPlaces();
            break;
        case 2:
            showReservations();
            break;
        case 3:
            showHost();
            break;
        case 4:
            showTravelers();
            break;
        case 5:
            Logout();
            break;
        default:
            showMenu();
            break;
    }
}

void Admin::showReservations()
{
    places.Load("places");
    reservations.Load("reservations");
    City::cities.Load("cities");
    Start::clearConsole();
    cout << "Reservations List: " << endl
         << endl;
    if(!reservations.Length()){
        Start::clearConsole();
        cout << "No Reservations Found!";
        showMenu(false);
        return;
    }
    for (int i = 0; i < reservations.Length(); ++i)
    {
        Reservation reservation = reservations.At(i);
        Place *rplace = reservation.place();

        if (rplace == NULL)
            continue;

        cout << (i + 1) << "-\nPlace Title: " << rplace->title << "\nPlace Price: ";
        cout << rplace->price << "\nCity Name: ";
        cout << rplace->getCityName() << "\nStart Date: ";
        cout << reservation.start_date.toString()
             << "\nEnd Date: ";
        cout << reservation.end_date.toString() << "\n";
    }
    cout << "\n\n";
    char o;
    while (true)
    {
        cout << "Enter 'c' to choose a reservation or 'm' to menu\n";
        cin >> o;
        if (o == 'm')
        {
            showMenu();
            return;
        }

        cout << "Choose a reservation id: ";
        int rid;
        cin >> rid;
        Reservation reservation = reservations.At(rid - 1);
        Place *rplace = reservation.place();
        if (rplace == nullptr)
        {
            showReservations();
            return;
        }

        cout << "Place Title: " << rplace->title << "\nPlace Price: ";
        cout << rplace->price << "\nCity Name: ";
        cout << rplace->getCityName() << "\nStart Date: ";
        cout << reservation.start_date.toString()
             << "\nEnd Date: ";
        cout << reservation.end_date.toString() << "\n";
        User *hst = rplace->host();
        cout << "host name: " << hst->full_Name << endl;
        cout << "host phone: " << hst->phone << endl
             << endl;
        while (true)
        {
            cout << "Enter '1' to edit or '2' to remove '3' to menu? \n";
            int op;
            cin >> op;
            if (op == 1)
            {
                cout << "To edit the START DATE press 1 and enter NEW START DATE \n";
                cout << "To edit the END DATE press 2 and enter NEW END DATE \n";
                cout << "To edit the CREATED AT DATE press 3 and enter NEW CREATED AT DATE \n";

                int op1;
                cin >> op1;
                switch (op1)
                {
                    case 1:
                    {
                        cout << "\nEnter new Start Date\n";
                        cdate dt = cdate();
                        dt.inputDate();
                        reservation.start_date = dt;
                        break;
                    }
                    case 2:
                    {
                        cout << "\nEnter new End Date\n";
                        cdate dt = cdate();
                        dt.inputDate();
                        reservation.end_date = dt;
                        break;
                    }
                    case 3:
                    {
                        cout << "\nEnter new Created At Date\n";
                        cdate dt = cdate();
                        dt.inputDate();
                        reservation.created_at = dt;
                        break;
                    }
                    default:
                        cout << "\nInvalid Operation\n";
                }
                Reservation finalReservation;
                finalReservation.end_date = reservation.end_date, finalReservation.start_date = reservation.start_date;
                finalReservation.place_id = reservation.place_id;
                finalReservation.reservation_id = reservation.reservation_id, finalReservation.created_at = reservation.created_at;
                reservations.Update(finalReservation, reservation.reservation_id);
            }
            else if (op == 2)
            {
                reservations.deletebyID(reservation.reservation_id);
                reservations.Save("reservations");
                showReservations();
                return;
            }
            else if (op == 3)
            {
                showMenu();
                return;
            }
            else
                cout << "Invalid Operation\n";
            reservations.Save("reservations");
        }
    }
}

void Admin::deleteReservation(int personID, bool traveler)
{
    reservations.Load("reservations");
    for (int i = 0; i < reservations.Length(); ++i)
    {
        Reservation reservation = reservations.At(i);
        Place * pl = reservation.place();
        if ((traveler && reservation.traveler_id == personID) || (!traveler && pl != NULL && pl->host_id == personID))
            reservations.deleteAt(i);
    }
    reservations.Save("reservations");
}


void Admin::deletePlace(int personID)
{
    places.Load("places");
    for (int i = 0; i < places.Length(); ++i)
    {
        Place place = places.At(i);
        if (place.host_id == personID) {
            places.deleteAt(i);
        }
    }
    places.Save("places");
}

void Admin::showHost()
{
    Start::users.Load("Users");
    Start::clearConsole();
    cout << "Hosts List: " << endl
         << endl;

    LinkedList<User> temp;
    for (int i = 0; i < Start::users.Length(); ++i)
    {
        User user = Start::users.At(i);
        if (user.type == HOST)
        {
            temp.Append(user);
            cout << temp.Length() << "- \nName: " << user.full_Name << "\nEmail: " << user.email << "\n";
        }
    }
    if(!temp.Length()){
        Start::clearConsole();
        cout << "No Hosts Found!";
        showMenu(false);
        return;
    }
    cout << "\n\n\n";
    char o;
    while (true)
    {
        cout << "\nenter 'c' to CHOOSE a Host or 'm' to menu\n";
        cin >> o;
        if (o == 'm')
        {
            showMenu();
            return;
        }
        cout << "Choose a Host: ";
        int hid;
        cin >> hid;
        User host = temp.At(hid - 1);
        cout << "Name: " << host.full_Name << "\nEmail: \n"
             << host.email << "\n";

        while (true)
        {
            cout << "\nEnter '1' to EDIT or '2' to REMOVE '3' to menu? \n";
            int op;
            cin >> op;
            if (op == 1)
            {
                cout << "to edit the NAME press 1 and enter the NEW NAME \n";
                cout << "to edit the EMAIL press 2 and enter the NEW EMAIL \n";
                int op1;
                cin >> op1;
                switch (op1)
                {
                    case 1:
                    {
                        string newName;
                        cout << "Enter New Name\n";
                        cin.ignore();
                        getline(cin, newName);
                        host.full_Name = newName;
                        break;
                    }
                    case 2:
                    {
                        string newEmail;
                        cout << "Enter New Email\n";
                        cin >> newEmail;
                        host.email = newEmail;
                        break;
                    }
                    default:
                        cout << "Invalid Operation\n";
                }
                User finalHost;
                finalHost.full_Name = host.full_Name, finalHost.email = host.email;
                finalHost.type = host.type, finalHost.phone = host.phone;
                finalHost.password = host.password, finalHost.nationality = host.nationality;
                finalHost.age = host.age, finalHost.gender = host.gender;
                finalHost.id = host.id;
                Start::users.Update(finalHost, host.id);
            }
            else if (op == 2)
            {
                deleteReservation(host.id,false);
                deletePlace(host.id);
                Start::users.DeleteById(host.id);
                Start::users.Save("Users");
                showHost();
                return;
            }
            else if (op == 3)
            {
                showMenu();
                return;
            }
            else
                cout << "Invalid Operation\n";
            Start::users.Save("Users");
        }
    }
}

void Admin::showTravelers()
{
    Start::users.Load("Users");
    Start::clearConsole();
    cout << "Travelers List: " << endl
         << endl;
    LinkedList<User> temp;
    for (int i = 0; i < Start::users.Length(); ++i)
    {
        User user = Start::users.At(i);
        if (user.type == TRAVELER)
        {
            temp.Append(user);
            cout << temp.Length() << "- \nName: " << user.full_Name << "\nEmail: " << user.email << "\n";
        }
    }
    if(!temp.Length()){
        Start::clearConsole();
        cout << "No Travelers Found!";
        showMenu(false);
        return;
    }
    cout << "\n\n\n";
    char o;
    while (true)
    {
        cout << "enter 'c' to choose a Traveler or 'm' to return to menu\n";
        cin >> o;
        if (o == 'm')
        {
            showMenu();
            return;
        }
        cout << "Choose a Traveler: ";
        int tid;
        cin >> tid;
        User traveler = temp.At(tid - 1);

        cout << "Name: " << traveler.full_Name << "\nEmail: \n"
             << traveler.email << "\n";

        while (true)
        {
            cout << "Enter '1' to EDIT or '2' to REMOVE '3' to menu? \n";
            int op;
            cin >> op;

            if (op == 1)
            {

                cout << "to edit the NAME press 1 and enter the NEW NAME \n";
                cout << "to edit the EMAIL press 2 and enter the NEW EMAIL \n";

                int op1;
                cin >> op1;
                switch (op1)
                {
                    case 1:
                    {
                        string newName;
                        cout << "Enter New Name\n";
                        cin.ignore();
                        getline(cin, newName);
                        traveler.full_Name = newName;
                        break;
                    }
                    case 2:
                    {
                        string newEmail;
                        cout << "Enter New Email\n";
                        cin >> newEmail;
                        traveler.email = newEmail;
                        break;
                    }
                    default:
                        cout << "Invalid Operation\n";
                }
                User finalTraveler;
                finalTraveler.full_Name = traveler.full_Name, finalTraveler.email = traveler.email;
                finalTraveler.type = traveler.type, finalTraveler.phone = traveler.phone;
                finalTraveler.password = traveler.password, finalTraveler.nationality = traveler.nationality;
                finalTraveler.age = traveler.age, finalTraveler.gender = traveler.gender;
                finalTraveler.id = traveler.id;
                Start::users.Update(finalTraveler, traveler.id);
            }
            else if (op == 2)
            {
                deleteReservation(traveler.id);
                Start::users.DeleteById(traveler.id);
                Start::users.Save("Users");
                showTravelers();
                return;

            }
            else if (op == 3)
            {
                showMenu();
                return;
            }
            else
                cout << "Invalid Operation\n";

            Start::users.Save("Users");
        }
    }
}
