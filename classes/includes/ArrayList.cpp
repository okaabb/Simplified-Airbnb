#include "ArrayList.h"
#include "../Reservation.h"
#include "../Place.h"
#include "../City.h"
#include <assert.h>
#include <fstream>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

template <class T>
ArrayList<T>::ArrayList()
{
    size = 100;
    arr = new T[size];
    count = 0;
}

template <class T>
int ArrayList<T>::Length()
{
    return count;
}

template <class T>
void ArrayList<T>::Append(T val)
{
    if (count == size)
        Expand();
    arr[count] = val;
    count++;
}

template <class T>
void ArrayList<T>::Expand()
{
    size *= 2; // define new capacity
    T *tmp = new T[size];
    for (int i = 0; i < count; i++)
        tmp[i] = arr[i];
    delete arr; // release old space
    arr = tmp;
}

template <class T>
T ArrayList<T>::At(int pos)
{
    assert(pos < count);
    return arr[pos];
}

template <class T>
void ArrayList<T>::insertAt(int pos, T val)
{
    assert(pos < count);
    if (count == size)
        Expand();
    // shift elements to the right
    for (int i = count; i > pos; i--)
        arr[i] = arr[i - 1];
    // insert value at required position
    arr[pos] = val;
    count++;
}

template <class T>
void ArrayList<T>::Update(T val, int id)
{
    for (int i = 0; i < count; i++)
        if (arr[i].getID() == id)
        {
            arr[i] = val;
            return;
        }
}

template <class T>
void ArrayList<T>::deleteAt(int pos)
{
    assert(pos < count);
    // shift elements to the left
    for (int i = pos; i < count - 1; i++)
        arr[i] = arr[i + 1];
    count--;
}

template <class T>
void ArrayList<T>::deletebyID(int id)
{
    bool found = false;
    for (int i = 0; i < count; i++)
    {
        if (arr[i].getID() == id) found = true;
        if(found) arr[i] = arr[i + 1];
    }
    count--;
}

template <class T>
void ArrayList<T>::Save(string fname)
{
    json l = json::array();

    for (int i = 0; i < count; i++)
    {
        l.push_back(arr[i].toJSON());
    }
    std::ofstream o("G:\\airbnb\\" + fname + ".json");
    o << std::setw(4) << l << std::endl;
}

template <class T>
T *ArrayList<T>::find(int id)
{
    //    assert(pos<count);
    for (int i = 0; i < count; i++)
        if (arr[i].getID() == id)
            return &arr[i];

    return NULL;
}

template <class T>
int ArrayList<T>::lastID()
{
    if (count > 0)
    {
        return At(count - 1).getID() + 1;
    }
    return 1;
}

template <class T>
void ArrayList<T>::Load(string fname)
{
    std::ifstream i("G:\\airbnb\\" + fname + ".json");
    if (!i.is_open())
        return;
    clear();
    json loaded;
    i >> loaded;
    for (int j = 0; j < loaded.size(); ++j)
        Append(T(loaded[j]));
}

template <class T>
void ArrayList<T>::clear()
{
    size = 100;
    delete[] arr;
    arr = new T[size];
    count = 0;
}

template <class T>
ArrayList<T>::~ArrayList(void)
{
    delete[] arr;
}

template class ArrayList<Reservation>;
template class ArrayList<Place>;
template class ArrayList<City>;
