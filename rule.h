#ifndef RULE_H
#define RULE_H
#include "element.h"
#include <vector>
class Rule
{
public:
    Element left;
    vector<Element> right;
    Rule()
    {

    }

    Rule(Element left_,vector<Element> right_)
    {
        left = left_;
        right = right_;
    }

    Element getLeft()
    {
        return left;
    }
    vector<Element> getRight()
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
