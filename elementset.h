#ifndef ELEMENTSET_H
#define ELEMENTSET_H
#include "element.h"
#include <vector>
class ElementSet{
public:
    vector<Element> elements;
    ElementSet()
    {

    }
    ElementSet(const Element &element)
    {
        push_back(element);
    }
    ElementSet(const Element& e1, const Element& e2) {
        push_back(e1);
        push_back(e2);
    }
    ElementSet& operator = (const ElementSet& element) {
        if(this != &element) {
            clear();
            for (int i = 0;i < element.elements.size();i++)
            {
                push_back(element.elements[i]);
            }
        }
        return *this;
    }

    void clear()
    {
        elements.clear();
    }

    ElementSet& operator + (const Element& element) {
        push_back(element);
        return *this;
    }
    friend ElementSet operator + (const Element& left, const Element& right) {
        return ElementSet(left, right);
    }


    void push_back(const Element& element)  {
        elements.push_back(element);
    }

    int size() const
    {
        return elements.size();
    }

    bool equal(const ElementSet& element) const {
        if (element.size() != this->size())
            return false;
        for (int i = 0;i < element.size();i++)
        {
            if (element.elements[i] != this->elements[i])
                return false;
        }
        return true;
    }

    bool operator == (const ElementSet& element) const {
        return equal(element);
    }
    bool operator != (const ElementSet& element) const {
        return !this->equal(element);
    }
    const Element& operator [] (int pos) const {
        return elements.at(pos);
    }
    Element&  operator [] (int pos) {
        return elements.at(pos);
    }

};

ElementSet Element::operator + (const Element & left) {
    return ElementSet(const this, left);
}

#endif // ELEMENTSET_H
