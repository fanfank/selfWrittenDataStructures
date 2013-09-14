#ifndef LIST_H
#define LIST_H

#include "node.h"
#include<iostream>
using std::cin;
using std::cout;
using std::endl;
template<typename T>
class List
{
    private:
        int sz;
        node<T> *head;
        T null;

    public:
        List();
        List(List<T> *);
        ~List();
        int erase(int);
        int insert(T, int);
        int push_front(T);
        int size();

        T& front();
        T& operator[](int);

        void clear();
        void print();
};

template<typename T>
List<T>::List() : sz(0), head(new node<T>()), null(0) {
    
}

template<typename T>
List<T>::List(List<T> *l) : sz(0), head(new node<T>()), null(0){
    if(l->size() == 0)
        return;

    node<T>* tmp = l->head;
    node<T>* cur = head;
    while(tmp->next != NULL)
    {
        cur->next = new node<T>(tmp->next->val);
        tmp = tmp->next;
        cur = cur->next;
        ++sz;
    }
}

template<typename T>
List<T>::~List() {
    clear();
    delete head;
}

template<typename T>
int List<T>::size()
{
    return sz;
}

template<typename T>
void List<T>::print()
{
    node<T> *tmp = head;
    cout<<"Printing list: ";
    while(tmp->next != NULL)
    {
        cout<<tmp->next->val<<" ";
        tmp = tmp->next;
    }
    cout<<endl;
}

template<typename T>
int List<T>::push_front(T val)
{
    head->next = new node<T>(val, head->next);
    sz++;
    return 0;
}

template<typename T>
int List<T>::insert(T val, int pos)
{
    if(pos < 0 || pos > sz)
        return -1;

    node<T> *p = head;
    while(pos--)
        p = p->next;
    p->next = new node<T>(val, p->next);
    sz++;
    return 0;
}

template<typename T>
int List<T>::erase(int pos)
{
    if(pos < 0 || pos >= sz)
        return -1;
    node<T> *p = head;
    while(pos--)
        p = p->next;
    node<T> *del = p->next;
    p->next = del->next;
    delete del;
    sz--;
    return 0;
}

template<typename T>
T& List<T>::front()
{
    if(sz == 0)
        return null;
    return head->next->val;
}

template<typename T>
T& List<T>::operator[](int pos)
{
    if(pos < 0 || pos >= sz)
    {
        cout<<"Boundary error"<<endl;
        exit(-1);
    }
    node<T> *tmp = head;
    while(pos--)
        tmp = tmp->next;
    return tmp->next->val;
}

template<typename T>
void List<T>::clear()
{
    while(sz)
        erase(0);
}

#endif
