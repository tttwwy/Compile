#ifndef ITEMSET_H
#define ITEMSET_H
#include <vector>
#include "item.h"
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;


class ItemSet
{
public:
    vector<Item> items;
    map<int,int> gotoTable;
    ItemSet()
    {

    }

    void setGotoTable(int x,int to)
    {
        gotoTable[x] = to;
//        map<int,int>::iterator p = gotoTable.find(x);
//        if (p == gotoTable.end())
//            gotoTable[x] = to;
//        else
//            return gotoTable[x];
    }

    int go(int x)
    {
        map<int,int>::iterator p = gotoTable.find(x);
        if (p == gotoTable.end())
            return -1;
        else
            return gotoTable[x];

    }

    ItemSet(Item item)
    {
        push_back(item);
    }

    void clear()
    {
        items.clear();
    }

    int size() const
    {
        return items.size();
    }

    bool empty()
    {
        return items.empty();
    }

    bool equal(const ItemSet& other) const {
        if(this->size() != other.size()) {
            return false;
        }

        for(int i = 0; i < size(); i++) {
            if(this->items[i] != other.items[i]) {
                return false;
            }
        }

        return true;
    }
    bool operator == (const ItemSet& other) const {
        return equal(other);
    }

    bool operator != (const ItemSet& other) const {
        return !equal(other);
    }

    bool push_back(Item &item)
    {
        for (unsigned int i = 0;i < items.size();i++)
        {
            if (items[i] == item)
                return false;
        }
        items.push_back(item);
        sort(items.begin(),items.end());
        return true;
    }
    const Item& operator [] (int pos) const {
        return items.at(pos);
    }
    Item&  operator [] (int pos) {
        return items.at(pos);
    }



};

class ItemSetEx{
public:
    vector<ItemSet> sets;

    int id;
    void setId(int id)
    {
        this->id = id;
    }


    void clear()
    {
        id = 0;
        sets.clear();
    }

    int find(ItemSet &set)
    {
        for (unsigned int i = 0;i < sets.size();i++)
        {
            if (sets[i] == set)
                return i;
        }
        return -1;
    }

    int size()
    {
        return sets.size();
    }

    int push_back(ItemSet &set)
    {
        for (unsigned int i = 0;i < sets.size();i++)
        {
            if (sets[i] == set)
                return i;
        }
        sets.push_back(set);
        return sets.size()-1;
    }

    int push_back(Item &set)
    {
        ItemSet temp(set);
        return push_back(temp);
    }

    const ItemSet& operator [] (unsigned int pos) const {
        if (pos < sets.size())
        return sets.at(pos);
        cout << "数组越界!" << endl;
    }
    ItemSet&  operator [] (unsigned int pos) {
        if (pos < sets.size())
        return sets.at(pos);
        cout << "数组越界!" << endl;
    }
};



#endif // ITEMSET_H
