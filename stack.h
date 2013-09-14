#ifndef STACK_H
#define STACK_H

#include<iostream>
using std::cin;
using std::cout;
using std::endl;

template<typename T>
class Stack
{
    private:
        int sz;
        node<T> *head;
        T null;

    public:
        Stack();
        Stack(Stack<T> *);
        ~Stack();

        int size();

        T& push(T);
        T& top();

        void clear();
        void pop();
        void print();
};

template<typename T>
Stack<T>::Stack() : head(new node<T>()), sz(0), null(0) {
    
}

template<typename T>
Stack<T>::Stack(Stack<T> *s) : head(new node<T>()), sz(0), null(0) {
    if(s->size() == 0)
        return;

    node<T> *tmp = s->head;
    node<T> *cur = head;
    while(tmp->next != NULL)
    {
        cur->next = new node<T>(tmp->next->val);
        cur = cur->next;
        tmp = tmp->next;
        ++sz;
    }
}

template<typename T>
Stack<T>::~Stack()
{
    clear();
    delete head;
}

template<typename T>
int Stack<T>::size() {
    return sz;
}

template<typename T>
void Stack<T>::clear() {
    while(sz)
        pop();
}

template<typename T>
T& Stack<T>::top() {
    if(sz == 0)
        return null;
    return head->next->val;
}

template<typename T>
T& Stack<T>::push(T val) {
    head->next = new node<T>(val, head->next);
    ++sz;
    return head->next->val;
}

template<typename T>
void Stack<T>::pop() {
    if(head->next == NULL)
        return;
    node<T> *del = head->next;
    head->next = del->next;
    delete del;
    --sz;
}

template<typename T>
void Stack<T>::print() {
    node<T> *tmp = head->next;
    cout<<"Printing stack: ";
    while(tmp != NULL)
    {
        cout<<tmp->val<<" ";
        tmp = tmp->next;
    }
    cout<<endl;
}
#endif

