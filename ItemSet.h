#ifndef ITEMSET_H
#define ITEMSET_H
#include <vector>
#include "item.h"
using namespace std;


class ItemSet
{
public:
    vector<Item> items;

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

    bool push_back(Item &item)
    {
        for (int i = 0;i < items.size();i++)
        {
            if (items[i] == item)
                return false;
        }
        items.push_back(item);
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

#endif // ITEMSET_H
