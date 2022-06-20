cmake_minimum_required(VERSION 3.21.1)
project(airbnb)

set(CMAKE_CXX_STANDARD 14)

add_executable(airbnb main.cpp classes/Signup_Login.cpp classes/Signup_Login.h classes/Start.cpp classes/Start.h classes/includes/LinkedList.cpp classes/includes/LinkedList.h classes/City.cpp classes/City.h classes/Place.cpp classes/Place.h classes/includes/cdate.cpp classes/includes/cdate.h classes/Reservation.cpp classes/Reservation.h classes/users/Person.h classes/users/Person.cpp classes/users/Traveler.h classes/users/Traveler.cpp classes/users/Host.h classes/users/Host.cpp classes/users/Admin.h classes/users/Admin.cpp classes/users/User.cpp classes/users/User.h classes/includes/ArrayList.cpp classes/includes/ArrayList.h)
