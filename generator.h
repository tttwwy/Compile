#ifndef GENERATOR_H
#define GENERATOR_H
#include "rule.h"
#include "grammar.h"
#include <iostream>
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
    vector<Element> elems;
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
        elems.clear();
        inited = false;
        beginTokenId = -1;
        beginRuleId = -1;
    }

    int findToken(Element e)
    {
        for (int i = 0;i < elems.size();i++)
            if (elems[i] == e)
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
            elems.push_back(rule.getLeft());
        }

        int left = findToken(rule.getLeft());
        vector<int> right;
        vector<Element> temp = rule.getRight();
        for (int i = 0;i < temp.size();i++)
        {
            if (findToken(temp[i]) < 0)
            {
                elems.push_back(temp[i]);
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
        const Element e = grammar.getStart();
        if (!e.isValid())
            return false;
        elems.push_back(Element::eof());
        eofTokenId = findToken(Element::eof());
        Element beginToken(Element::non_terminator,"S\'");

        vector<Rule> temp1 = grammar.getRules();
        for (int i = 0;i < temp1.size();i++)
            addRule(temp1[i]);

        //À©Õ¹ÎÄ·¨
        vector<Element> begin;
        begin.push_back(e);
        Rule beginRule(beginToken,begin);
        int bid = addRule(beginRule);
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
};

#endif // GENERATOR_H
