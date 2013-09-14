#ifndef QUEUE_H
#define QUEUE_H

#include<iostream>
using std::cin;
using std::cout;
using std::endl;

template<typename T>
class Queue
{
    private:
        int sz;
        node<T> *head, *tail;
        T null;

    public:
        Queue();
        Queue(Queue<T> *);
        ~Queue();

        int size();

        T& back();
        T& front();
        T& push(T);

        void clear();
        void pop();
        void print();
};

template<typename T>
Queue<T>::Queue() : head(new node<T>()), tail(NULL), sz(0), null(0)
{
    head->next = tail;
}

template<typename T>
Queue<T>::Queue(Queue<T> *q) 
    : head(new node<T>()), tail(NULL), sz(0), null(0)
{
    head->next = tail;
    node<T> *tmp = q->head;
    while(tmp->next != NULL)
    {
        push(tmp->next->val);
        tmp = tmp->next;
    }
}

template<typename T>
Queue<T>::~Queue()
{
    clear();
    delete head;
}

template<typename T>
int Queue<T>::size()
{
    return sz;
}

template<typename T>
T& Queue<T>::back()
{
    if(sz == 0)
        return null;
    return tail->val;
}

template<typename T>
T& Queue<T>::front()
{
    if(sz == 0)
        return null;
    return head->next->val;
}

template<typename T>
T& Queue<T>::push(T val)
{
    if(sz == 0)
    {
        head->next = tail = new node<T>(val);
        ++sz;
        return tail->val;
    }
    tail->next = new node<T>(val);
    tail = tail->next;
    ++sz;
    return tail->val;
}

template<typename T>
void Queue<T>::clear()
{
    while(sz)
        pop();
}

template<typename T>
void Queue<T>::pop()
{
    if(sz == 0)
        return;
    node<T> *del = head->next;
    head->next = del->next;
    --sz;
    delete del;
}

template<typename T>
void Queue<T>::print()
{
    node<T> *tmp = head->next;
    cout<<"Printing queue: ";
    while(tmp != NULL)
    {
        cout<<tmp->val<<" ";
        tmp = tmp->next;
    }
    cout<<endl;
}
#endif
