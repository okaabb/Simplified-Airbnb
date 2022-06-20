#pragma once
#include <iostream>
#include <string>
#include "json.hpp"
#include <cassert>
#include <fstream>
#include "../users/User.h"

using json = nlohmann::json;
using namespace std;

template <class T>
class Node
{
public:
    Node<T> *next;
    T value;

    Node();
    Node(T val);
};

template <class T>
class LinkedList
{
    int count;
    Node<T> *head;
    Node<T> *tail;

public:
    LinkedList();
    int lastID();
    void clear();
    int Length();
    T At(int);
    void InsertAt(int, T);
    void Append(T);
    void DeleteAt(int);
    void DeleteById(int);
    void Save(string fname);
    void Load(string fname);
    void Update(T val, int id);
    T *FindUser(string email, string password);
    T *FindUser(int id);
    ~LinkedList(void);
};
