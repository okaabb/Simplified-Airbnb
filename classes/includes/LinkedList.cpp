
#include "LinkedList.h"
#include <cassert>
#include <iostream>
#include <string>
#include <fstream>
#include "json.hpp"
#include "../users/User.h"

using namespace std;
using json = nlohmann::json;

template <class T>
Node<T>::Node(T val)
{
    value = val;
    next = 0;
}

template <class T>
LinkedList<T>::LinkedList(void)
{
    head = tail = 0;
    count = 0;
}

template <class T>
int LinkedList<T>::Length()
{
    return count;
}

template <class T>
void LinkedList<T>::Append(T val)
{
    Node<T> *newNode = new Node<T>(val);
    if (head == 0)
        head = tail = newNode;
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
    count++;
}

template <class T>
T LinkedList<T>::At(int pos)
{
    assert(pos >= 0 && pos < count);
    Node<T> *tmp = head;
    for (int i = 0; i < pos; i++)
        tmp = tmp->next;
    return tmp->value;
}

template <class T>
void LinkedList<T>::InsertAt(int pos, T val)
{
    assert(pos >= 0 && pos < count);
    Node<T> *tmp = head;
    Node<T> *newNode = new Node<T>(val);
    if (pos == 0)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        for (int i = 0; i < pos - 1; i++)
            tmp = tmp->next;

        newNode->next = tmp->next;
        tmp->next = newNode;
    }
    count++;
}

template <class T>
void LinkedList<T>::DeleteById(int id) {
    Node<T> *temp = head;
    Node<T> *prev = NULL;

    if (temp != NULL && temp->value.id == id) {
        head = temp->next;
        delete temp;
    } else {
        while (temp != NULL && temp->value.id != id) {
            prev = temp;
            temp = temp->next;
        }
        if (temp != NULL) {
            prev->next = temp->next;
            if (prev->next == NULL)
                tail = prev;
            delete temp;
        }
    }
    count--;
}

template <class T>
void LinkedList<T>::DeleteAt(int pos)
{
    assert(pos >= 0 && pos < count);
    Node<T> *tmp = head;
    if (pos == 0)
    {
        head = head->next;
        delete tmp;
    }
    else
    {
        for (int i = 0; i < pos - 1; i++)
            tmp = tmp->next;
        Node<T> *del = tmp->next;
        tmp->next = del->next;
        delete del;
        if (pos == count - 1)
            tail = tmp;
    }
    count--;
}

template <class T>
void LinkedList<T>::Save(string fname)
{
    json l = json::array();
    Node<T> *tmp = head;
    for (int i = 0; i < count; i++)
    {
        l.push_back(tmp->value.toJSON());
        tmp = tmp->next;
    }
    std::ofstream o("G:\\airbnb\\" + fname + ".json");
    o << std::setw(4) << l << std::endl;
}

template <class T>
void LinkedList<T>::Load(string fname)
{
    clear();
    std::ifstream i("G:\\airbnb\\" + fname + ".json");
    if (!i.is_open())
        return;
    json loaded;
    i >> loaded;
    for (int j = 0; j < loaded.size(); ++j)
        Append(T(loaded[j]));
}

template <class T>
LinkedList<T>::~LinkedList(void)
{
    clear();
}

template <class T>
int LinkedList<T>::lastID()
{
    if (count > 0)
    {
        return tail->value.id + 1;
    }
    return 1;
}

template <class T>
T *LinkedList<T>::FindUser(string email, string password)
{
    Node<T> *tmp = head;
    for (int i = 0; i < count; i++)
    {
        if (tmp->value.email == email && tmp->value.password == password)
        {
            return &(tmp->value);
        }
        tmp = tmp->next;
    }
    return NULL;
}

template <class T>
T *LinkedList<T>::FindUser(int id)
{
    Node<T> *tmp = head;
    for (int i = 0; i < count; i++)
    {
        if (tmp->value.id == id)
        {
            return &(tmp->value);
        }
        tmp = tmp->next;
    }
    return NULL;
}

template <class T>
void LinkedList<T>::clear()
{
    while (count > 0)
        DeleteAt(0);
    head = tail = 0;
}

template <class T>
void LinkedList<T>::Update(T val, int id)
{
    Node<T> *tmp = head;
    for (int i = 0; i < count; i++)
    {
        if (tmp->value.id == id)
        {
            tmp->value = val;
            return;
        }
        tmp = tmp->next;
    }
}

template class LinkedList<User>;