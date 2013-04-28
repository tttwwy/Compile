#ifndef RULE_H
#define RULE_H
#include "element.h"
#include "elementset.h"
#include <sstream>
#include <iostream>
class Rule
{
public:
    Element left;
    ElementSet right;
    int index;
    Rule()
    {

    }

    Rule(Element left_,ElementSet right_)
    {
        left = left_;
        right = right_;
        index = -1;
    }
    Rule(int index,Element left_,ElementSet right_)
    {
        left = left_;
        right = right_;
        this->index = index;
    }

    Rule(Element left)
    {
        this->left = left;
    }

    Element getLeft()
    {
        return left;
    }
    ElementSet getRight()
    {
        return right;
    }

    int getIndex()
    {
        return index;
    }

    friend ostream& operator << (ostream& os, const Rule& rule) {
        if (rule.index > -1)
            os << "index:" << rule.index << " ";
        os << rule.left << "->";
        for (int i = 0;i < rule.right.size();i++)
        {
            os << rule.right[i] <<" ";
        }

        return os;
    }
    int size()
    {
        return right.size();
    }


};

class IRule
{
public:
    int left;
    vector<int> right;
    int index;
    IRule()
    {

    }

    IRule(int left_,vector<int> right_)
    {
        left = left_;
        right = right_;
        index = -1;
    }
    IRule(int index,int left_,vector<int> right_)
    {
        left = left_;
        right = right_;
        this->index = index;
    }
    bool equal(const IRule&  rule) const {
        return this->left == rule.left && this->right == rule.right;
    }

    int getRight(int pos)
    {
        return right[pos];
    }

    int getIndex()
    {
        return index;
    }

    vector<int> getRight()
    {
        return right;
    }

    int getLeft()
    {
        return left;
    }


    /** 判断两个规则是否相等 */
    bool operator == (const IRule&  rule) const {
        return equal(rule);
    }
    bool operator != (const IRule&  right) const {
        return !equal(right);
    }
    int size()
    {
        return right.size();
    }

};

#endif // RULE_H
