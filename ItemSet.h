#ifndef ITEMSET_H
#define ITEMSET_H
#include <vector>
#include "item.h"
#include <map>
#include <algorithm>
using namespace std;


class ItemSet
{
public:
    vector<Item> items;

    ItemSet(Item item)
    {
        push_back(item);
    }

    void clear()
    {
        items.clear();
    }

    int size()
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
        for (int i = 0;i < items.size();i++)
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

    //    ItemSet& operator = (const ItemSet& other) {
    //        if(this != &other) {
    //            this->clear();
    //            add(other);
    //        }
    //        return *this;
    //    }
};

class ItemSetEx{
public:
    vector<ItemSet> sets;
    int id;
    setId(int id)
    {
        this->id = id;
    }

    void clear()
    {
        id = 0;
        sets.clear();
    }

    bool isExisted(ItemSet &set)
    {
        for (int i = 0;i < sets.size();i++)
        {
            if (sets[i] == set)
                return true;
        }
        return false;
    }

    int size()
    {
        return sets.size();
    }

    int  push_back(ItemSet &set)
    {
        for (int i = 0;i < sets.size();i++)
        {
            if (sets[i] == set)
                return i;
        }
        sets.push_back(set);
        return sets.size()-1;
    }

    int push_back(Item &set)
    {
       return push_back(ItemSet(set));
    }

};

class ItemSetCluster{
public:
    vector<ItemSetEx*> sets;

    push_back(ItemSetEx & set)
    {
        for (int i = 0;i < sets.size();i++)
        {

        }
    }
};

#endif // ITEMSET_H
