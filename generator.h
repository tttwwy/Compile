#ifndef GENERATOR_H
#define GENERATOR_H
#include "rule.h"
#include "grammar.h"
#include <iostream>
#include "item.h"
#include "itemset.h"
#include <queue>
#include <set>
using namespace std;
class Generator
{
    class Action
    {
    public:
        enum Type {
            error  = 0,
            shift  = 1,
            reduce = 2,
            accept = 3
        };
        Type type;
        int rule;
        int state;
        Action()
        {
            type = error;
            rule = -1;
        }
        Action(Type type,int rule)
        {
            this->type = type;
            this->rule = rule;
        }

    };

    vector<IRule> rules;
    ElementSet elements;
    int beginTokenId;
    int beginRuleId;
    int eofTokenId;
    bool inited;
    ItemSetEx set;
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
            cout << "getIRule error!" << endl;
        }
    }

    int getElementId(Item item,int x)
    {
        if (item.getRule() >= 0 && item.getRule() < rules.size())
            return getIRule(item.getRule()).getRight(x);
        else
            cout << "getElementId error!" << endl;
    }

    Element getElement(int id)
    {
        if (id >= 0 && id < elements.size())
            return elements[id];
        else
            cout << "getElement error!" << endl;
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

    //单个元素的First集
    void first(int id,set<int> &firstSet,bool &canNull )
    {

        if (id == Item::invalid_forward || getElement(id).isTerminator())
        {
            firstSet.insert(id);
        }
        else
        {
            for (int i = 0;i < rulesSize();i++)
            {
                IRule rule = rules[i];
                if (rule.getLeft() == id)
                {
                    if (rule.right.size() == 0)
                        canNull = true;
                    else
                    {
                        first(rule.getRight(),firstSet,canNull);
                        //                        bool bn = true;
                        //                        for (int k = 0;bn && k < rule.right.size();k++ )
                        //                        {
                        //                            first(rule.getRight(k),firstSet,bn);
                        //                        }
                        //                        canNull = true;
                    }
                }
            }
        }
    }

    //串的First集
    void first(vector<int> &idStr,set<int> &firstSet,bool &canNull)
    {
        bool bn = true;
        for (int i = 0;bn && i < idStr.size();i++)
        {
            bn = false;
            first(idStr[i],firstSet,bn);
        }
        canNull = bn;
    }

    void lr1Closure(ItemSet & C)
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
            IRule rule =  getIRule(item.getRule());
            if (item.getPos() < rule.size())
            {
                int elementID  = rule.getRight(item.getPos());
                if (getElement(elementID).isNonTerminator())
                {
                    //计算First集
                    vector<int> str;
                    set<int> firstSet;
                    for (int i = item.getPos()+1;i < rule.size();i++)
                    {
                        str.push_back(rule.getRight(i));
                    }
                    bool bn = false;
                    first(str,firstSet,bn);


                    for (int i = 0;i < rulesSize();i++)
                    {
                        if (getIRule(i).getLeft() == elementID)
                        {
                            for (set<int>::iterator p = firstSet.begin();p!=firstSet.end();p++)
                            {
                                Item temp(i,0,*p);
                                if (C.push_back(temp))
                                {
                                    q.push(temp);
                                }

                            }

                        }
                    }
                }

            }
        }
    }


    void go(ItemSet &from,int x,ItemSet &to)
    {
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

        lr1Closure(to);
        return to;
    }

    void genItemSex()
    {
        set.clear();

        ItemSet first(Item(beginRuleId,0,eofTokenId));
        lr1Closure(first);

        set.push_back(first);

        bool go = true;
        while(go)
        {
            go = false;
            for (int i = 0;i < set.size();i++)
            {
                for (int j = 0;j < elements.size();j++)
                {
                    ItemSet temp = go(set[i],j);
                    if (temp.size() > 0 && !set.isExisted(temp))
                    {
                        set.push_back(temp);
                        go = true;
                    }

                }
            }
        }
    }

    void genTable()
    {
        vector <vector <Action> >action(set.size(),vector <int> (elements.size()));
        vector <vector <Action> >goTo(set.size(),vector <int> (elements.size()));

        for (int i = 0;i < set.size();i++)
        {

        }
    }
};



#endif // GENERATOR_H
