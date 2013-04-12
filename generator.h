#ifndef GENERATOR_H
#define GENERATOR_H
#include "rule.h"
#include "grammar.h"
#include <iostream>
#include "item.h"
#include <vector>
#include "itemset.h"
#include <queue>
#include <set>
#include <iomanip>
#include <stack>
#include "scanner.h"
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

public:
    vector<IRule> rules;
    ElementSet elements;
    int beginTokenId;
    int beginRuleId;
    int eofTokenId;
    bool inited;
    int id;
    ItemSetEx itemSetEx;
    vector <vector<Action> > action;
    vector <vector<int> > goTo;
    map<int,int> nonTermMap;
    map<int,int> termMap;
    //非终结符号表
    vector<int> nonTerm;
    //终结符号表
    vector<int> term;
    vector<int> w;

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
        id = 0;
        nonTermMap.clear();
        termMap.clear();
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
        return findIRule(temp2);
    }

    bool init(Grammar &grammar)
    {
        clear();
        Element startElement = grammar.getStart().left;
        if (!startElement.isValid())
            return false;

        elements.push_back(startElement.eof());
        eofTokenId = findToken(startElement.eof());
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
        //        cout << beginTokenId <<" " << beginRuleId << endl;
        cout << "符号集："<< endl;
        for (int i = 0;i < elements.size();i++)
            cout << elements[i].type<<" "<<elements[i] << endl;

        cout << "规则集:" << endl;
        for (int i = 0;i < rules.size();i++)
            showIRule(rules[i]);
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
                        //                        first(rule.getRight(),firstSet,canNull);
                        bool bn = true;
                        for (int k = 0;bn && k < rule.right.size();k++ )
                        {
                            first(rule.getRight(k),firstSet,bn);
                        }
                        canNull = true;
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
                cout <<"求串的First集:" ;
                for (int i = 0;i < idStr.size();i++)
                {
                    elements[idStr[i]];
                }
                cout << endl;
                for (set<int>::iterator p = firstSet.begin();p != firstSet.end();p++)
                {
                    cout << elements[*p] <<" ";
                }
                cout << endl;
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
                    str.push_back(item.forward);
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


    void showIRule(IRule rule)
    {
        cout << elements[rule.getLeft()] << "->" ;
        for (int i = 0;i < rule.getRight().size();i++)
        {
            cout << elements[rule.getRight(i)];
        }
        cout << endl;
    }

    void showItem(Item item)
    {
        IRule rule = getIRule(item);
        cout << elements[rule.getLeft()] << "->";
        for (int i = 0;i < rule.getRight().size();i++)
        {
            if (i == item.getPos())
                cout << ".";
            cout << elements[rule.getRight(i)];
        }
        cout<<"," <<elements[item.getForward()];
        cout << endl;
    }

    void showItemSet(ItemSet itemSet)
    {
        for (int i = 0;i < itemSet.size();i++)
            showItem(itemSet[i]);
    }

    void showItemSetEx()
    {
        for (int i = 0;i < itemSetEx.size();i++)
        {
            cout <<"项目集" << i << ":" << endl;
            for (int j = 0;j < itemSetEx[i].size();j++)
            {
                showItem(itemSetEx[i][j]);
            }
        }
    }

    void genItemSex()
    {
        itemSetEx.clear();

        ItemSet first(Item(beginRuleId,0,eofTokenId));
        lr1Closure(first);

//        showItemSet(first);



        itemSetEx.push_back(first);

        bool run = true;
        while(run)
        {
            run = false;
            for (int i = 0;i < itemSetEx.size();i++)
            {
                for (int j = 0;j < elements.size();j++)
                {
                    ItemSet temp = go(itemSetEx[i],j);
                    if (temp.size() > 0 )
                    {
                        int k = itemSetEx.find(temp);
                        if (k < 0)
                        {
                            //                        temp.setGotoTable(j,itemSetEx.size());
                            itemSetEx.push_back(temp);
                            itemSetEx[i].setGotoTable(j,itemSetEx.size()-1);
                            run = true;
                        }
                        else
                        {
                            itemSetEx[i].setGotoTable(j,k);
                        }
                    }

                }
            }
        }
        showItemSetEx();
    }

    void genTable()
    {




        //        //规则表
        //        vector<int> rule;
        //        map<int,int> ruleMap;
        //        termMap[eofTokenId] = 0;
        //        term.push_back(eofTokenId);


        //        for (int i = 0;i < set.size();i++)
        //        {
        //            for (int j = 0;j < set[i].size();j++)
        //            {
        //                set[i].sets
        //            }

        //        }
        for (int i = 0;i < elements.size();i++)
        {
            if(elements[i].isNonTerminator())
            {
                nonTerm.push_back(i);
                nonTermMap[i] = nonTerm.size()-1;
            }
            else if (elements[i].isTerminator())
            {
                term.push_back(i);
                termMap[i] = term.size()-1;
            }
        }


        action.resize(itemSetEx.size());
        goTo.resize(itemSetEx.size());
        for (int i = 0;i < action.size();i++)
        {
            action[i].resize(term.size());
            goTo[i].resize(nonTerm.size());
        }
        for (int i = 0;i < goTo.size();i++)
        {
            for (int j = 0;j < goTo[i].size();j++)
            {
                goTo[i][j] = -1;
            }
        }



        for (int i = 0;i < itemSetEx.size();i++)
        {
            ItemSet itemSet = itemSetEx[i];
            Action temp;
            cout <<"项目" << i <<":\n";
            for (int j = 0;j < itemSetEx[i].size();j++)
            {

                Item item = itemSetEx[i][j];
                showItem(item);


                //是否为起始项目
                if (getIRule(item.getRule()).getLeft() == beginTokenId
                        &&item.getPos() == 1
                        &&item.isValid())
                {

                    cout <<"Accept\n";
                    temp.type = Action::accept;
                    //                    temp.rule = item.getRule();
                    action[i][termMap[item.forward]] = temp;
                }
                else if (item.getPos() < getIRule(item).right.size())
                {
                    int elementId = getIRule(item).getRight(item.getPos());
                    Element element = getElement(elementId);
                    if (element.isTerminator())
                    {
                        if (itemSet.go(elementId) >= 0)
                        {
                            int  m = termMap[elementId];
                            temp = action[i][m];

                            if (temp.type == Action::error)
                            {
                                temp.type = Action::shift;
                                temp.state = itemSet.go(elementId) ;
                                action[i][termMap[elementId]] =temp;
                                cout << "shift:" << temp.state << endl;
                            }
                            else if (temp.type == Action::shift)
                            {
                                //                                cout << "移进-移进冲突！" << endl;
                            }
                        }
                    }
                    else
                    {

                    }
                }
                else
                {
                    temp = action[i][termMap[item.forward]];
                    if (temp.type == Action::error)
                    {
                        temp.type = Action::reduce;
                        temp.rule = item.getRule();
                        action[i][termMap[item.forward]] = temp;
                        cout <<"reduce:" << temp.rule << endl;
                    }
                    else if (temp.type == Action::reduce)
                    {
                        cout << "规约-规约冲突！"<< endl;
                    }
                    else
                    {
                        cout << "移进-规约冲突！" << endl;
                    }
                }
            }
            for (int k = 0;k < nonTerm.size();k++)
            {
                if (itemSet.go(nonTerm[k]) >= 0)
                {
                    goTo[i][k] = itemSet.go(nonTerm[k]);
                }
            }
        }
        setiosflags(ios::left);

        cout << "Action Table:" << endl;
        cout  << " ";
        for (int i = 0;i < term.size();i++)
        {
            cout << setw(3) << elements[term[i]];
        }
        cout << endl;
        for (int i = 0;i < action.size();i++)
        {
            cout << setw(2) << i <<" ";
            for (int j = 0;j < action[i].size();j++)
            {

                if (action[i][j].type == Action::shift)
                {
                    cout << "S" <<  action[i][j].state;
                }
                if (action[i][j].type == Action::reduce)
                {
                    cout << "r" << action[i][j].rule;
                }
                if (action[i][j].type == Action::accept)
                {
                    cout << "acc" ;
                }
                cout <<" ";
            }
            cout << endl;
        }

        cout << "Goto Table:" << endl;
        cout  << " ";
        for (int i = 0;i < nonTerm.size();i++)
        {
            cout << setw(3) << elements[nonTerm[i]];
        }
        cout << endl;
        for (int i = 0;i < goTo.size();i++)
        {
            cout << setw(2) << i <<" ";
            for (int j = 0;j < goTo[i].size();j++)
            {

                if (goTo[i][j] != -1)
                {
                    cout <<  goTo[i][j];
                }

                cout <<" ";
            }
            cout << endl;
        }

    }
    bool generator()
    {
        if (!inited)
        {
            cout << "没有初始化!";
            return false;
        }
        genItemSex();
        genTable();
        return true;
    }

    int getNext()
    {
        if (id < w.size())
        {

            return  w[id++];


        }
        return -1;
    }

    bool getTokens(vector<Token> tokens)
    {
        string name[34] = {"ELSE","IF","INT","DOUBLE","CHAR","RETURN","VOID","WHILE","FOR","<=",">=","==","!=","/*","*/","<",">","=","+","-","*","/",";",",","(",")","[","]","{","}","NUM","ID","STR","ERROR"};
        vector<int> ww;
        for (int i = 0;i < tokens.size();i++)
        {
            for (int j = 0;j < elements.size();j++)
            {
                if (elements[j].name == name[tokens[i].type-1])
                {
                    ww.push_back(j);
                    break;
                }
            }
        }
        if (ww.size() <= 0)
            return false;
        this->w = ww;
        return true;
    }

    bool parser()
    {

        for (int i = 0;i < w.size();i++)
            cout << elements[w[i]].name << endl;
        stack<int> stateStack;
        stack<int> eleStack;
        int ip = getNext();
        stateStack.push(0);
        eleStack.push(beginTokenId);
        while(1)
        {
            Action actiontemp = action[stateStack.top()][termMap[ip]] ;
            if (actiontemp.type == Action::shift)
            {
                cout << "移入：" << actiontemp.state << "  " << elements[ip].name << endl;
                stateStack.push(actiontemp.state);
                eleStack.push(ip);
                ip = getNext();
            }

            else if (actiontemp.type == Action::reduce)
            {
                cout << "规约:";
                IRule rule = getIRule(actiontemp.rule);
                showIRule(rule);
                for (int i = 0;i < rule.size();i++)
                {
                    stateStack.pop();
                    cout << "出栈!" << endl;
                    eleStack.pop();
                }

                eleStack.push(rule.left);
                int temp = stateStack.top();
                stateStack.push(goTo[temp][nonTermMap[rule.left]]);
                cout << "入栈：" << goTo[temp][nonTermMap[rule.left]] << elements[rule.left] << endl;
            }
            else if (actiontemp.type == Action::accept)
            {
                cout << "语法分析完成！" << endl;
                return true;
            }
            else
            {
                cout << "Error!";
                return false;
            }
        }
    }
};



#endif // GENERATOR_H
