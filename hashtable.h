#ifndef HASHTABLE_H
#define HASHTABLE_H
#include<iostream>
using std::cout;
using std::endl;
template<typename T>
class Hashtable
{
    private:
        struct node {
            T val;
            node *next;
            node(T v = 0, node *nxt = NULL) : val(v), next(nxt) {
                
            }
            ~node()
            {
                //if(next != NULL)
                    //delete next;
            }
        };
        struct slot {
            int size;
            node *head;
            slot(int sz = 0, node *nxt = NULL) 
                : size(sz), head(new node(0, nxt)) {
                
            }
            ~slot()
            {
                if(head->next != NULL)
                {
                    node *del = head->next;
                    head->next = del->next;
                    delete del;
                }
                delete head;
            }

            bool insert(T val);
            bool remove(T val);

            node* find(T val, bool get_pre = false);
        }*slots;

        double threshold;

        int nslot;
        int sz;

        virtual int hash(T val);

    public:
        Hashtable(int slot_num = 10, double th = 0.75);
        ~Hashtable();

        int size();
        int slotSize();

        T *find(T val);

        void insert(T val);
        void print();
        void remove(T val);
        void resize(int _size);
};

template<typename T>
bool Hashtable<T>::slot::insert(T val) {
    node *target = find(val);
    if(target != NULL)
        return false;

    target = new node(val, head->next);
    head->next = target;
    ++size;
    return true;
}

template<typename T>
bool Hashtable<T>::slot::remove(T val) {
    node *pre = find(val, true);
    if(pre->next == NULL)
        return false;

    node *del = pre->next;
    pre->next = del->next;
    delete del;
    --size;
    return true;
}

template<typename T>
typename Hashtable<T>::node *Hashtable<T>::slot::find(T val, bool get_pre) {
    node *tmp = head;
    while(tmp->next != NULL && tmp->next->val != val) {
        tmp = tmp->next;
    }
    if(get_pre)
        return tmp;
    return tmp->next;
}

template<typename T>
Hashtable<T>::Hashtable(int slot_num, double th)
    : nslot(slot_num), threshold(th), sz(0)
{
    slots = new slot[nslot];
}

template<typename T>
Hashtable<T>::~Hashtable() {
    delete []slots;
}

template<typename T>
int Hashtable<T>::hash(T val) {
    return val % nslot;
}

template<typename T>
int Hashtable<T>::size() {
    return sz;
}

template<typename T>
int Hashtable<T>::slotSize() {
    return nslot;
}

template<typename T>
T *Hashtable<T>::find(T val) {
    int hash_pos = hash(val);
    node *tmp = slots[hash_pos % nslot].find(val);
    if(tmp == NULL)
        return NULL;
    return &(tmp->val);
}

template<typename T>
void Hashtable<T>::insert(T val) {
    int hash_pos = hash(val);
    if(slots[hash_pos % nslot].insert(val))
    {
        ++sz;
        if(sz*1.0/nslot >= threshold)
            resize(nslot * 2);
    }
}

template<typename T>
void Hashtable<T>::print() {
    node *tmp;
    for(int i = 0; i < nslot; i++)
        if(slots[i].size > 0)
        {
            cout<<"Slot "<<i<<":";
            tmp = slots[i].head->next;
            while(tmp != NULL)
            {
                cout<<" "<<tmp->val;
                tmp = tmp->next;
            }
            cout<<endl;
        }
}

template<typename T>
void Hashtable<T>::remove(T val) {
    int hash_pos = hash(val);
    if(slots[hash_pos % nslot].remove(val))
    {
        --sz;
        if(sz > 0 && sz/(nslot/2.0) < threshold)
            resize(nslot / 2);
        
    }
}

template<typename T>
void Hashtable<T>::resize(int _size)
{
    if(_size < 0)
        return;
    else if(_size == 0 || _size <= sz)
    {
        resize(sz + 1);
    }
    else {
        int tmp_pos, tmp_nslot = nslot;
        nslot = _size;
        slot *tmp_slots = new slot[_size];
        node *tmp_node, *tmp_node2;
        for(int i = 0; i < tmp_nslot; i++)
            if(slots[i].size > 0)
            {
                tmp_node = slots[i].head->next;
                while(tmp_node != NULL)
                {
                    tmp_pos = hash(tmp_node->val) % _size;
                    tmp_node2 = new node(tmp_node->val, 
                            tmp_slots[tmp_pos].head->next);
                    tmp_slots[tmp_pos].head->next = tmp_node2;
                    tmp_slots[tmp_pos].size++;
                    tmp_node = tmp_node->next;
                }
            }

        delete []slots;
        slots = tmp_slots;
        nslot = _size;
    }
}

#endif
