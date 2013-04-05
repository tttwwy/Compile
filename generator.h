#ifndef GENERATOR_H
#define GENERATOR_H
#include "rule.h"
#include "grammar.h"
#include <iostream>
#include "item.h"
#include <set>
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

        //À©Õ¹ÎÄ·¨
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

    void closure(set<Item> &itemSet)
    {
        queue<Item> q;
        for
    }

};

#endif // GENERATOR_H
