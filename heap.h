#ifndef HEAP_H
#define HEAP_H
#include<iostream>
using std::cout;
using std::endl;

//Heap's index starts from 1
template<typename T>
class Heap
{
    private:
        int cap;
        int sz;
        
        T *arr;

        void bottomUp(int index);
        void topDown(int index);

    public:
        Heap();
        Heap(const Heap<T> *);
        Heap(T array[], int len);
        ~Heap();

        int capacity();
        int size();
        const int size() const;

        T push(T val);
        T top();
        
        Heap<T>& operator=(const Heap<T> &);
        void assign(T array[], int len);
        void clear();
        void pop();
        void print();
        void resize(int _size = 0);
};

//Remember that: the sequence of initialization of member variables
//relies on the sequence that these variables are defined, not
//on the sequence in initializing lists of the constructor

template<typename T>
Heap<T>::Heap() : cap(5), arr(new T[cap]), sz(0) {
    
}

template<typename T>
Heap<T>::Heap(const Heap<T> *copy) : cap(5), arr(new T[cap]), sz(0) {
    if(copy == NULL || copy->size() < 1)
        return;
    *this = *copy;
}

template<typename T>
Heap<T>::Heap(T array[], int len) : cap(5), arr(new T[cap]), sz(0) {
    if(array == NULL || len < 1)
        return;
    assign(array, len);
}

template<typename T>
Heap<T>::~Heap() {
    if(arr != NULL)
        delete []arr;
}

template<typename T>
int Heap<T>::capacity() {
    return cap - 1;
}

template<typename T>
int Heap<T>::size() {
    return sz;
}

template<typename T>
const int Heap<T>::size() const {
    return sz;
}
template<typename T>
T Heap<T>::push(T val) {
    if(sz + 1 >= cap)
        resize((cap<<1) - 1);
    arr[++sz] = val;
    bottomUp(sz);
}

template<typename T>
T Heap<T>::top() {
    if(sz > 0)
        return arr[1];
    else
        return 0;
}

template<typename T>
Heap<T>& Heap<T>::operator=(const Heap<T> &copy) {
    clear();
    resize(copy.size());
    for(int i = 1; i <= copy.sz; i++)
        arr[++sz] = copy.arr[i];
    return *this;
}

template<typename T>
void Heap<T>::assign(T array[], int len) {
    if(array == NULL || len < 1)
        return;
    resize(len);
    for(int i = 0; i < len; i++)
        arr[i+1] = array[i];
    sz = len;

    int index = len / 2;
    T tmp;
    while(index > 0)
    {
        topDown(index);
        --index;
    }
}

template<typename T>
void Heap<T>::bottomUp(int index) {
    if(index <=1 || index > sz)
        return;
    T tmp;
    while(index/2 > 0 && arr[index] < arr[index/2])
    {
        tmp = arr[index];
        arr[index] = arr[index/2];
        arr[index/2] = tmp;
        topDown(index);
        index /= 2;
    }
}

template<typename T>
void Heap<T>::clear() {
    sz = 0;
    resize(4);
}

template<typename T>
void Heap<T>::pop() {
    if(sz < 1)
        return;
    arr[1] = arr[sz--];
    if(sz > 0)
        topDown(1);
}

template<typename T>
void Heap<T>::print() {
    cout<<"Printing:";
    Heap<T> *tmp = new Heap<T>(this);

    while(tmp->size() > 0)
    {
        cout<<" "<<tmp->top();
        tmp->pop();
    }
    cout<<endl;
    delete tmp;
}

template<typename T>
void Heap<T>::resize(int _size) {
    if(_size < 0)
        return;
    else if(_size == 0)
        resize(sz);
    else if(_size < sz)
    {
        //cout<<"_size < sz"<<endl;
        if(sz < capacity())
            resize(sz);
        return;
    }
    else {
        T *tmp = new T[sz + 1];
        for(int i = 1; i <= sz; i++)
            tmp[i] = arr[i];
        delete []arr;

        arr = new T[_size + 1];
        for(int i = 1; i <= sz; i++)
            arr[i] = tmp[i];
        delete []tmp;
        cap = _size + 1;
    }
}

template<typename T>
void Heap<T>::topDown(int index) {
    if(index < 1 || index >= sz)
        return;
    int smallest;
    T tmp;
    while(index < sz)
    {
        smallest = index;
        if((index * 2 <= sz) && (arr[index*2] < arr[index]))
            smallest = index * 2;
        if((index * 2 + 1) <= sz && arr[index*2+1] < arr[smallest])
            smallest = index * 2 + 1;
        if(smallest == index)
            break;

        tmp = arr[index];
        arr[index] = arr[smallest];
        arr[smallest] = tmp;
        index = smallest;
    }
}

#endif
