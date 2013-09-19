#include "heap.h"
#include "list.h"
#include "queue.h"
#include "stack.h"
#include <iostream>
#include <stdio.h>
using namespace std;
double array[5] = {2.2, 1.38, 2.89, 1.11, 9.56};
void pp(){int stop; cin>>stop;}
int main()
{
    printf("-------- Testing List --------\n");
    List<double> l;
    l.erase(4);
    l.print();
    for(int i = 0; i < 5; i++)
    {
        l.insert(array[i], l.size());
        l.print();
    }

    List<double> l2(&l);
    l2.print();

    l2.erase(0);
    l2.erase(4);
    l2.erase(100);
    l2.erase(l2.size() - 1);
    l2.print();

    cout<<"l2[2].val = "<<l2[2]<<endl;
    cout<<"l2[0].val = "<<l2[0]<<endl;
    cout<<"l2.front() = "<<l2.front()<<endl;
    //cout<<"l2[3].val = "<<l2[3].val<<endl; //boundary error
    for(int i = 0; i < l.size(); i++)
        l2.push_front(l[i]);
    l2.print();

    printf("-------- Testing Stack --------\n");
    Stack<double> sta;
    sta.pop();
    sta.print();
    for(int i = 0; i < 5; ++i)
    {
        sta.push(array[i]);
        sta.print();
    }

    Stack<double> sta2(&sta);
    sta2.print();
    while(sta2.size())
    {
        cout<<"sta2.top() = "<<sta2.top()<<" size: "<<sta2.size();
        cout<<" ====> pop"<<endl;
        sta2.pop();
    }

    printf("-------- Testing Queue --------\n");
    Queue<double> q;
    q.pop();
    q.print();
    for(int i = 0; i < 5; ++i)
    {
        q.push(array[i]);
        q.print();
    }

    Queue<double> q2(&q);
    q2.print();
    while(q2.size())
    {
        cout<<endl;
        q2.print();
        cout<<"q2.front() = "<<q2.front()<<" q2.back() = "<<q2.back();
        cout<<" q2.size() = "<<q2.size()<<endl;
        q2.pop();
    }

    Queue<double> q3(&q);
    q3.clear();
    q3.print();

    printf("-------- Testing Heap --------\n");
    Heap<double> h(array, 5);
    h.print();
    while(h.size())
    {
        cout<<"Capacity: "<<h.capacity()<<" size: "<<h.size()<<endl;
        h.print();
        h.pop();
    }
    h.print();
    //pp();
    for(int i = 4; i >= 0; i--)
    {
        cout<<"Capacity: "<<h.capacity()<<" size: "<<h.size()<<endl;
        h.push(array[i]);
        h.print();
    }

    Heap<double> h2(&h);
    cout<<"**** h2 ****: ";
    h2.print();
    cout<<"Capacity: "<<h2.capacity()<<" size: "<<h2.size()<<endl;
    for(int i = 10; i < 15; i++)
        h2.push(double(i));
    h2.print();
    
    cout<<endl;
    h2.resize(5); 
    cout<<"Capacity: "<<h2.capacity()<<" size: "<<h2.size()<<endl;
    h2.print();

    cout<<endl;
    h2.resize(30);
    cout<<"Capacity: "<<h2.capacity()<<" size: "<<h2.size()<<endl;
    cout<<"Top: "<<h2.top()<<endl;

    h2.clear();
    cout<<"Capacity: "<<h2.capacity()<<" size: "<<h2.size()<<endl;
    h2.assign(array, 5);
    cout<<"Capacity: "<<h2.capacity()<<" size: "<<h2.size()<<endl;
    h2.print();

    Heap<double> h3;
    h3.print();
    cout<<"Capacity: "<<h3.capacity()<<" size: "<<h3.size()<<endl;
    h3.pop();
    h3.pop();
    h3.pop();
    h3.pop();
    cout<<"Capacity: "<<h3.capacity()<<" size: "<<h3.size()<<endl;
    h3.resize(10);
    cout<<"Capacity: "<<h3.capacity()<<" size: "<<h3.size()<<endl;
    h3.assign(array, 5);
    cout<<"Capacity: "<<h3.capacity()<<" size: "<<h3.size()<<endl;
    h3.print();

    double arr2[] = {0,0,1,0,-1};

    h2.assign(arr2, 5);
    h3 = h2;
    h3.print();
}
