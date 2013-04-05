#ifndef RULE_H
#define RULE_H
#include "element.h"
#include "elementset.h"

class Rule
{
public:
    Element left;
    ElementSet right;
    Rule()
    {

    }

    Rule(Element left_,ElementSet right_)
    {
        left = left_;
        right = right_;
    }

    Element getLeft()
    {
        return left;
    }
    ElementSet getRight()
    {
        return right;
    }

};

class IRule
{
public:
    int left;
    vector<int> right;
    IRule(int left_,vector<int> right_)
    {
        left = left_;
        right = right_;
    }


    /** 判断两个规则是否相等 */
    bool operator == (const IRule&  rule) const {
        return this->left == rule.left && this->right == rule.right;
    }
};

#endif // RULE_H
