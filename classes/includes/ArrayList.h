#pragma once
#include <iostream>
using namespace std;
#ifndef AIRBNB_ARRAYLIST_H
#define AIRBNB_ARRAYLIST_H

template <class T>
class ArrayList
{
    T *arr;
    int size, count;

public:
    ArrayList();
    void clear();
    int lastID();
    int Length();
    void Append(T);
    void Expand();
    T At(int);
    void insertAt(int, T);
    void deleteAt(int);
    void deletebyID(int);
    void Save(string fname);
    void Load(string fname);
    void Update(T val, int id);
    T *find(int id);
    ~ArrayList(void);
};

#endif
