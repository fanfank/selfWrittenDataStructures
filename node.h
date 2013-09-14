#ifndef NODE_H
#define NODE_H
#include <stdlib.h>
template<typename T>
struct node
{
    node<T> *next;
    T val;
    node(T v = 0, node<T>* nxt = NULL) : val(v), next(nxt){}
};
#endif
