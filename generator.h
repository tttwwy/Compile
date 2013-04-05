#ifndef GENERATOR_H
#define GENERATOR_H
#include "rule.h"
#include "grammar.h"
#include <iostream>
#include "item.h"
#include "itemset.h"
#include <queue>

using namespace std;
class Generator
{
    struct Action
    {
        enum Type {
            error  = 0,
            shift  = 1,
            reduce = 2,
            accept = 3
        };
        Type type;
        int rule;
        int state;

    };

    vector<IRule> rules;
    ElementSet elements;
    int beginTokenId;
    int beginRuleId;
    int eofTokenId;
    bool inited;

    Generator()
    {
        beginTokenId = -1;
        beginRuleId = -1;
        inited = false;
    }

    IRule getIRule(int pos)
    {
        if (pos >= 0 && pos < rules.size())
            return rules[pos];
        else
        {
            cout << "getIRule error!";
        }
    }

    int getElementId(Item item,int x)
    {
        if (item.getRule() >= 0 && item.getRule() < rules.size())
        return getIRule(item.getRule()).getRight(x);
        else
            cout << "getElementId error!";
    }

    IRule getIRule(Item item)
    {
        return rules[item.getRule()];
    }

    int rulesSize()
    {
        return rules.size();
    }

    int elementsSize()
    {
        return elements.size();
    }

    void clear()
    {
        rules.clear();
        elements.clear();
        inited = false;
        beginTokenId = -1;
        beginRuleId = -1;
    }

    int findToken(Element e)
    {
        for (int i = 0;i < elements.size();i++)
            if (elements[i] == e)
                return i;
        return -1;
    }

    int findIRule(IRule e)
    {
        for (int i = 0;i < rules.size();i++)
            if (rules[i] == e)
                return i;
        return -1;
    }

    int addRule(Rule rule)
    {
        if (findToken(rule.getLeft()) < 0)
        {
            elements.push_back(rule.getLeft());
        }

        int left = findToken(rule.getLeft());
        vector<int> right;
        ElementSet temp = rule.getRight();
        for (int i = 0;i < temp.size();i++)
        {
            if (findToken(temp[i]) < 0)
            {
                elements.push_back(temp[i]);
            }
            right.push_back(findToken(temp[i]));
        }

        IRule temp2(left,right);
        if (findIRule(temp2) < 0)
            rules.push_back(temp2);
        return findIrule(temp2);
    }

    bool init(Grammar &grammar)
    {
        clear();
        const Element startElement = grammar.getStart();
        if (!startElement.isValid())
            return false;
        elements.push_back(Element::eof());
        eofTokenId = findToken(Element::eof());
        Element beginToken(Element::non_terminator,"S\'");

        vector<Rule> temp1 = grammar.getRules();
        for (int i = 0;i < temp1.size();i++)
            addRule(temp1[i]);

        //扩展文法
        ElementSet startSet;
        startSet.push_back(startElement);
        Rule startRule(beginToken,startSet);
        int bid = addRule(startRule);
        if (bid >= 0)
            beginRuleId = bid;
        else
            return false;
        beginTokenId = findToken(beginToken);
        if (beginTokenId < 0)
            return false;


        inited = true;
        return true;
    }

    void closure(ItemSet C)
    {
        //待检测项目
        queue<Item> q;
        //初始项目
        for (int i = 0;i < C.size();i++)
        {
            q.push(C[i]);
        }
        while(!q.empty())
        {
            Item item = q.front();
            q.pop();
            if (item.getPos() < getIRule(item.getRule()).size())
            {
                int elementID  = getIRule(item).getRight(item.getPos());
                for (int i = 0;i < rulesSize();i++)
                {
                    if (getIRule(i).getLeft() == elementID)
                    {
                        Item temp(i,0,Item::invalid_forward);
                        if (C.push_back(temp))
                        {
                            q.push(temp);
                        }
                    }
                }
            }

        }
    }

    ItemSet go(ItemSet &from,int x)
    {
        ItemSet to;
        for (int i = 0;i < from.size();i++)
        {
            if (getElementId(from[i],from[i].getPos()) == x
                    && from[i].getPos() < getIRule(from[i].getRule()).size())
            {
                Item item = from[i];
                item.pos++;
                to.push_back(item);
            }
        }
        return to;
    }

};

#endif // GENERATOR_H
