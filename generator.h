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
#include <string>
#include "scanner.h"
#include "nametable.h"
#include <sstream>
#include "four.h"

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





private:
    stack<int> stateStack;
    stack<Base> eleStack;
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

    //token表
    vector<Token> token;
    vector<Four> four;
    NameTable nametable;
    vector<vector<Four> > tempfour;
    int nextquad;



    Base left;
    vector<Base> pop;
    vector<NameTable> nametables;

    Generator()
    {
        beginTokenId = -1;
        beginRuleId = -1;
        inited = false;
    }

    IRule getIRule(unsigned int pos)
    {
        if ( pos < rules.size())
            return rules[pos];
        else
        {
            cout << "getIRule error!" << endl;
        }
    }

    int getElementId(Item item,unsigned int x)
    {
        if ( item.getRule() < rules.size())
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
        nametable.clear();
        nextquad = 0;

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
        for (unsigned int i = 0;i < rules.size();i++)
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

        IRule temp2(rule.getIndex(),left,right);
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
        for (unsigned int i = 0;i < temp1.size();i++)
        {
            addRule(temp1[i]);
        }

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
            cout << i << ":" << elements[i].type<<" "<<elements[i] << endl;

        cout << "规则集:" << endl;
        for (unsigned int i = 0;i < rules.size();i++)
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

    //    void follow(int id,set<int> &follow)
    //    {
    //        if (id == beginTokenId)
    //        {
    //            follow.insert(eofTokenId);
    //            return;
    //        }
    //        for (int i = 0;i < rules.size();i++)
    //        {
    //            IRule rule = getIRule(i);
    //            for (int j = 0;j < rule.size();j++)
    //            {
    //                if (id == rule.getRight(j) && j+ 1 < rule.size())
    //                {
    //                    first()
    //                }
    //            }
    //        }
    //    }

    //单个元素的First集
    void first(int id,set<int> &firstSet,bool &canNull )
    {

        //        cout << "求First集：" << elements[id].name << endl;
        if ( getElement(id).isTerminator())
        {
            firstSet.insert(id);
            canNull = false;
        }
        else if (getElement(id).isNonTerminator())
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
                        for (unsigned int k = 0;bn && k < rule.right.size();k++ )
                        {
                            set<int>  temp;
                            if (rule.getRight(k) != id)
                            {

                                first(rule.getRight(k),temp,bn);
                                for (set<int>::iterator p = temp.begin();p != temp.end();p++)
                                    firstSet.insert(*p);
                            }
                        }
                        canNull = bn;
                    }
                }
            }
        }
        //        for (set<int>::iterator p = firstSet.begin();p != firstSet.end();p++)
        //            cout << elements[*p];
        //        cout << endl;
    }

    //串的First集
    void first(vector<int> &idStr,set<int> &firstSet,bool &canNull)
    {
        bool bn = true;
        for (unsigned int i = 0;bn && i < idStr.size();i++)
        {
            bn = false;
            first(idStr[i],firstSet,bn);
        }
        canNull = bn;
        //                cout <<"求串的First集:" ;
        //                for (int i = 0;i < idStr.size();i++)
        //                {
        //                    elements[idStr[i]];
        //                }
        //                cout << endl;
        //                for (set<int>::iterator p = firstSet.begin();p != firstSet.end();p++)
        //                {
        //                    cout << elements[*p] <<" ";
        //                }
        //                cout << endl;
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
                                int rule = i;
                                int pos = 0;
                                int forward = *p;
                                Item temp(rule,pos,forward);
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
        if (rule.getIndex() > - 1)
            cout << "index:" << rule.getIndex() << " ";
        cout << elements[rule.getLeft()] << "->" ;
        for (unsigned int i = 0;i < rule.getRight().size();i++)
        {
            cout << elements[rule.getRight(i)];
        }
        cout << endl;
    }

    void showItem(Item item)
    {
        IRule rule = getIRule(item);
        cout << elements[rule.getLeft()] << "->";
        for (unsigned int i = 0;i < rule.getRight().size();i++)
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
                            //                            cout << itemSetEx.size()-1 << ":" << endl;
                            //                            showItemSet(temp);
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
        for (unsigned int i = 0;i < action.size();i++)
        {
            action[i].resize(term.size());
            goTo[i].resize(nonTerm.size());
        }
        for (unsigned int i = 0;i < goTo.size();i++)
        {
            for (unsigned int j = 0;j < goTo[i].size();j++)
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
            cout << setw(8) << elements[term[i]];
        }
        cout << endl;
        for (int i = 0;i < action.size();i++)
        {
            cout << setw(2) << i <<" ";
            for (int j = 0;j < action[i].size();j++)
            {

                if (action[i][j].type == Action::shift)
                {
                    cout << "S" << setw(7) << action[i][j].state;
                }
                if (action[i][j].type == Action::reduce)
                {
                    cout << "r" <<setw(7) << action[i][j].rule;
                }
                if (action[i][j].type == Action::accept)
                {
                    cout << setw(8) << "acc" ;
                }
                if (action[i][j].type == Action::error)
                {
                    cout << setw(8) << "error";
                }

            }
            cout << endl;
        }

        cout << "Goto Table:" << endl;
        cout  << " ";
        for (int i = 0;i < nonTerm.size();i++)
        {
            cout << setw(13) << elements[nonTerm[i]];
        }
        cout << endl;
        for (int i = 0;i < goTo.size();i++)
        {
            cout << setw(2) << i <<" ";
            for (int j = 0;j < goTo[i].size();j++)
            {

                //                if (goTo[i][j] != -1)
                //                {
                cout <<  setw(13) << goTo[i][j];
                //                }

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

    Token getNext()
    {
        if (id < token.size())
        {
            return  token[id++];
        }
        Token temp;
        temp.type = -1;
        return temp;
    }

    bool getTokens(vector<Token> tokens)
    {
        string name[] = {"else","if","int","double","char","return","void","while","for","<=",">=","==","!=","/*","*/","<",">","=","+","-","*","/",";",",","(",")","[","]","{","}","num","id","string","ERROR","&","++","--","printf","scanf","main","array","%"};

        for (int i = 0;i < tokens.size();i++)
        {
            for (int j = 0;j < elements.size();j++)
            {
                if (elements[j].name == name[tokens[i].type-1])
                {
                    Token temp = tokens[i];
                    temp.type = j;
                    token.push_back(temp);
                    break;
                }
            }
        }

        return true;
    }

    bool select(int ruleid)
    {
        bool success = true;
        if (ruleid > -1)
        {
            switch (ruleid)
            {
            case 1:
                success = function1();
                break;
            case 2:
                success = function2();
                break;
            case 3:
                success = function3();
                break;
            case 4:
                success = function4();
                break;
            case 5:
                success = function5();
                break;
            case 6:
                success = function6();
                break;
            case 7:
                success = function7();
                break;
            case 8:
                success = function8();
                break;
            case 9:
                success = function9();
                break;

            case 10:
                success = function10();
                break;
            case 11:
                success = function11();
                break;
            case 12:
                success = function12();
                break;
            case 13:
                success = function13();
                break;
            case 14:
                success = function14();
                break;
            case 15:
                success = function15();
                break;
            case 16:
                success = function16();
                break;
            case 17:
                success = function17();
                break;
            case 18:
                success = function18();
                break;
            case 19:
                success = function19();
                break;
            case 20:
                success = function20();
                break;
            case 21:
                success = function21();
                break;
            case 22:
                success = function22();
                break;
            case 23:
                success = function23();
                break;
            case 24:
                success = function24();
                break;
            case 25:
                success = function25();
                break;
            case 26:
                success = function26();
                break;
            case 27:
                success = function27();
                break;
            case 28:
                success = function28();
                break;
            case 29:
                success = function29();
                break;
            case 30:
                success = function30();
                break;
            case 31:
                success = function31();
                break;
            case 32:
                success = function32();
                break;



            }
            return success;
        }
        return false;
    }

    template<class out_type,class in_value>
    out_type convert(const in_value & t)

    {

        stringstream stream;

        stream<<t;//向流中传值

        out_type result;//这里存储转换结果

        stream>>result;//向result中写入值

        return result;

    }

    int send(string op,string a,string b,int result)
    {
        four.push_back(Four(op,a,b,nametable[result]));
        nextquad++;
        return four.size();
    }

    int send(string op,string a,string b,string result)
    {
        four.push_back(Four(op,a,b,result));
        nextquad++;
        return four.size();
    }



    //define type id_name
    bool function1()
    {

        int i = nametable.newAddr(pop[0].value,pop[1].value);

        if (i == -1)
        {
            cout << "变量" << pop[1].value << "重复定义！" << endl;
            return false;
        }
        return true;
    }

    //F num
    bool function2()
    {
        if (elements[pop[0].type].name == "num")
        {
            left.value = pop[0].value;
            left.flag = Base::num;
        }
        else
        {
            if (pop[0].value.size() > 1)
            {
                cout << "类型转换非法！" << endl;
                return false;
            }
            int temp = pop[0].value[0];
            left.value = convert<string>(temp);
            left.flag = Base::num;
        }
        return true;

    }

    //F id
    bool function3()
    {
        int i = nametable.getAddr(pop[0].value);
        if (i == -1)
        {
            cout << "变量" << pop[0].value << "未定义！" << endl;
            return false;
        }
        if (pop.size() == 1)
        {
            left.flag = Base::id;
            left.addr = i;
        }
        else if (pop.size() == 4)
        {
            left.flag = Base::temp;
            int j = nametable.newTemp();
            if (pop[2].flag == Base::num)
            {
                send("*",pop[2].value,convert<string>(nametable.getTypeSize(i)),j);
                send("mov",pop[0].value + "+" + "[" + nametable[j] + "]","",j);
                left.addr = j;
            }
            else if (pop[2].flag == Base::id)
            {
                send("*",nametable[pop[2].addr],convert<string>(nametable.getTypeSize(i)),j);
                send("mov",pop[0].value + "+" + "[" + nametable[j] + "]","",j);
                left.addr = j;
                nametable.releaseTemp(pop[2].addr);
            }

        }
        else if (pop.size() == 3)
        {
            left.flag = Base::array;
            left.addr = i;
        }
        return true;
    }

    bool function4()
    {
        if (pop.size() == 1)
        {
            if (pop[0].flag == Base::id)
            {
                left.value = nametable[pop[0].addr];
            }
            if (pop[0].flag == Base::temp)
                left.value = nametable[pop[0].addr];
            if (pop[0].flag == Base::num)
                left.value = pop[0].value;
        }
        //        if (pop.size() == 2)
        //        {
        //            int i = nametable.getAddr(pop[1].value);
        //            if (i == -1)
        //            {
        //                cout << "未定义的变量！" << endl;
        //                return false;
        //            }
        //            left.value = "addr" + string(" ") + pop[1].value;
        //        }
        //        if (pop.size() == 3)
        //        {
        //            int i = nametable.getAddr(pop[1].value);
        //            if (i == -1)
        //            {
        //                cout << "未定义的变量！" << endl;
        //                return false;
        //            }
        //            if (nametable.getSize(i) <= 0)
        //            {
        //                cout << "非法操作！" << endl;
        //                return false;
        //            }
        //            int k = convert<int>(pop[2].value) * nametable.getTypeSize(i);
        //            left.value = "addr" + string(" ") + pop[0].value + "+" + convert<string>(k);
        //        }
        return true;
    }

    bool function5()
    {
        int i = nametable.newTemp();
        send("mov",nametable[0],"",i);
        left.addr = i;
        left.flag = Base::temp;
        return true;
    }

    string cal(string a,string op,string c)
    {
        int A = convert<int>(a);
        int B = convert<int>(c);
        int C = 0;

        if (op == "+")
            C =  A + B;
        else if (op == "-")
            C = A - B;
        else if (op == "*")
            C = A * B;
        else if (op == "/")
            C = A / B;
        else if (op == "%")
            c = A % B;
        return convert<string>(C);

    }

    //E E +-*/ T
    bool function6()
    {
        Base a = pop[0];
        string op = elements[pop[1].type].name;
        Base c = pop[2];

        if (a.flag == Base::num && c.flag == Base::num)
        {
            left.value = cal(a.value,op,c.value);
            left.flag = Base::num;
        }
        else if (a.flag == Base::id && c.flag == Base::id)
        {
            int addr = nametable.newTemp();
            left.addr = addr;
            left.flag = Base::temp;

            send("mov",nametable[a.addr],"",addr);
            send(op,nametable[addr],nametable[c.addr],addr);
        }
        else
        {
            int addr = nametable.newTemp();
            left.addr = addr;
            left.flag = Base::temp;
            if (a.flag == Base::id||a.flag == Base::temp)
            {
                a.value = nametable[a.addr];
                nametable.releaseTemp(a.addr);
            }
            if (c.flag == Base::id||c.flag == Base::temp)
            {
                c.value = nametable[c.addr];
                nametable.releaseTemp(c.addr);
            }
            send(op,a.value,c.value,addr);

        }
        return true;

    }

    bool function7()
    {

        left.addr = pop[0].addr;
        if (pop[0].value.size() == 0)
            left.value = elements[pop[0].type].name;
        else
            left.value = pop[0].value;
        left.flag = pop[0].flag;
        return true;
    }

    bool function8()
    {

        left.addr = pop[1].addr;
        left.value = pop[1].value;
        left.flag = pop[1].flag;
        return true;

    }

    bool function9()
    {
        int i = nametable.getAddr(pop[0].value);
        if (i == -1)
        {
            cout << "变量" << pop[0].value << "未定义！" << endl;
            return false;
        }

        string a;
        if (pop.size() == 3)
        {

            if (pop[2].flag == Base::num)
                a = pop[2].value;
            else if (pop[2].flag == Base::id || pop[2].flag == Base::temp)
            {
                a = nametable[pop[2].addr];
                nametable.releaseTemp(pop[2].addr);
            }
            send("mov",a,"",pop[0].value);
            return true;
        }

        if (pop.size() == 6)
        {
            int j = nametable.newTemp();
            if (pop[5].flag == Base::num)
                a = pop[5].value;
            else if (pop[5].flag == Base::id|| pop[5].flag == Base::temp)
            {
                a = nametable[pop[5].addr];
                nametable.releaseTemp(pop[5].addr);
            }


            if (pop[2].flag == Base::num)
            {
                send("*",pop[2].value,convert<string>(nametable.getTypeSize(i)),j);
                send("mov",a,"",pop[0].value + "+" + "[" + nametable[j] + "]");

            }
            else if (pop[2].flag == Base::id|| pop[2].flag == Base::temp)
            {
                send("*",nametable[pop[2].addr],convert<string>(nametable.getTypeSize(i)),j);
                send("mov",a,"",pop[0].value + "+" + "[" + nametable[j] + "]");
                nametable.releaseTemp(pop[2].addr);
            }
            nametable.releaseTemp(j);

        }


        return true;

    }

    bool function10()
    {
        int i = nametable.newAddr(pop[0].value,pop[1].value);
        if (i == -1)
        {
            cout << "变量" << pop[1].value << "重复定义！" << endl;
            return false;
        }
        string a;
        if (pop[3].flag == Base::num)
            a = pop[3].value;
        else if (pop[3].flag == Base::id || pop[3].flag == Base::temp)
            a = nametable[pop[3].addr];
        send("mov",a,"",i);
        nametable.releaseTemp(pop[3].addr);
        return true;
    }

    bool function11()
    {
        left.addr = nextquad;
        return true;
    }

    bool function12()
    {
        left.addr = pop[1].addr;
        return true;
    }
    bool function13()
    {
        string a;
        if (pop[0].flag == Base::id)
            a = nametable[pop[0].addr];
        if (pop[0].flag == Base::num)
            a = pop[0].value;
        if (pop[0].flag == Base::temp)
        {
            a = nametable[pop[0].addr];
            nametable.releaseTemp(pop[0].addr);
        }
        string b;
        if (pop[2].flag == Base::num)
        {
            b =  pop[2].value;
        }
        if (pop[2].flag == Base::id)
        {
            b = nametable[pop[2].addr];
        }
        if (pop[2].flag == Base::temp)
        {
            b = nametable[pop[2].addr];
            nametable.releaseTemp(pop[2].addr);
        }

        send(pop[1].value,a,b,convert<string>(nextquad+2));
        send("jmp","","","0");
        left.addr = nextquad;
        return true;
    }
    bool function14()
    {
        string a;
        if (pop[0].flag == Base::num)
            a = pop[0].value;
        if (pop[0].flag == Base::id)
        {
            a = nametable[pop[0].addr];
        }

        if (pop[0].flag == Base::temp)
        {
            a = nametable[pop[0].addr];
            nametable.releaseTemp(pop[0].addr);
        }
        send("-",a,"0",convert<string>(nextquad+2));
        send("jmp","","","0");
        left.addr = nextquad;
        return true;
    }

    bool function15()
    {
        Base bool_expression = pop[2];
        four[bool_expression.addr-1].addr = convert<string>(nextquad);
        return true;
    }

    bool function16()
    {
        send("jmp","","","0");
        left.addr = nextquad;
        return true;
    }

    bool function17()
    {
        Base bool_expression = pop[2];
        Base ifsentence = pop[4];
        Base sentence = pop[6];
        four[bool_expression.addr-1].addr = convert<string>(ifsentence.addr);
        four[ifsentence.addr-1].addr = convert<string>(sentence.addr);
        return true;
    }



    bool function18()
    {
        left.value = elements[pop[1].type].name;
        int addr = nametable.getAddr(pop[0].value);
        if (addr == -1)
        {
            cout << "未定义的变量！" << endl;
            return false;
        }
        if (elements[pop[1].type].name == "++")
            send("+",nametable[addr],"1",addr);
        if (elements[pop[1].type].name == "--")
            send("-",nametable[addr],"1",addr);
        return true;
    }


    bool function19()
    {
        Base bool_expression = pop[2];
        Base whilesentence = pop[4];
        Base while1 = pop[0];
        four[bool_expression.addr-1].addr = convert<string>(whilesentence.addr);
        four[whilesentence.addr-1].addr = convert<string>(while1.addr);
        return true;
    }
    bool function20()
    {
        Base for_set_value = pop[2];
        Four temp = four[for_set_value.addr+2];
        deleteFour(for_set_value.addr+2);
        four.push_back(temp);
        send("jmp","","",convert<string>(for_set_value.addr));
        four[for_set_value.addr + 1].addr = convert<string>(nextquad);
        return true;
    }
    bool function21()
    {
        left.value = pop[0].value + "," +pop[2].value;
        return true;
    }
    bool function22()
    {
        Base nums;
        int count = 1;

        if (pop.size() == 10)
        {
            nums = pop[7];
            for (int i = 0;i < nums.value.size();i++)
            {
                if (nums.value[i] == ',')
                    count++;
            }
            if (count != convert<int>(pop[3].value))
            {
                cout << "数组" << pop[1].value << "定义非法！" << endl;
                return false;
            }
        }
        if (pop.size() == 9)
        {
            for (int i = 0;i < nums.value.size();i++)
            {
                if (nums.value[i] == ',')
                    count++;
            }
            nums = pop[6];
        }
        if (pop.size() == 7)
            count =  convert<int>(pop[3].value);

        int i = nametable.newAddr(pop[0].value,pop[1].value);
        if (i == -1)
        {
            cout << "变量" << pop[1].value << "重复定义！" << endl;
            return false;
        }
        if (pop.size() == 10 || pop.size() == 9)
        {
            if (nums.value.size() > 0)
            {
                string temp;
                int j = 0;
                int type = getTypeSize(pop[0].value);
                for (int i = 0;i < nums.value.size();i++)
                {
                    if (nums.value[i] != ',')
                        temp += nums.value[i];
                    else
                    {
                        send("mov",temp,"",pop[1].value + "+" + convert<string>(type * j));
                        j++;
                        temp.clear();
                    }
                }
                send("mov",temp,"",pop[1].value + "+" + convert<string>(type * j));
            }
            nametable.setValue(i,nums.value);
        }
        nametable.setSize(i,count);
        return true;
    }
    int getTypeSize(string type)
    {
        if (type == "int")
            return 4;
        if (type == "char")
            return 1;
        if (type == "double")
            return 4;
        if (type == "string")
            return 1;

    }

    bool function23()
    {
        int i = nametable.newAddr("char",pop[1].value);
        if (i == -1)
        {
            cout << "变量" << pop[1].value << "重复定义！" << endl;
            return false;
        }
        for (int j = 0;j < pop[6].value.size();j++)
        {
            string temp;
            if (pop[6].value[j] == '\n')
                temp = "10";
            else
            {
                temp = "\'";
                temp += pop[6].value[j];
                temp += "\'";
            }
            send("mov",temp,"",pop[1].value+"+"+convert<string>(j));
        }
        send("mov","0","",pop[1].value + "+"+convert<string>(pop[6].value.size()));

        nametable.setSize(i,pop[6].value.size()+1);
        return true;
    }
    bool function24()
    {
        if (pop.size() == 2)
        {
            nametable.addlist(pop[0].value,pop[1].value);
            nametable.newAddr(pop[0].value,pop[1].value);
        }
        if (pop.size() == 4)
        {
            nametable.addlist(pop[2].value,pop[3].value);
            nametable.newAddr(pop[2].value,pop[3].value);
        }
        return true;
    }

    bool function25()
    {
        string name = pop[1].value;
        for (int i = 0;i < nametables.size();i++)
        {
            if (nametables[i].getFunctionName() == name)
            {
                cout << "函数" << name << "重复定义！" << endl;
                return false;
            }
        }
        nametable.setFunctionName(name);
        nametable.setReturnType(pop[0].value);
        nametable.setFour(four);
        nametables.push_back(nametable);
        four.clear();
        nametable.clear();
        nextquad = 0;
        return true;

    }
    bool function26()
    {
        if (pop[1].flag == Base::num)
            send("mov",pop[1].value,"",0);
        if (pop[1].flag == Base::temp || pop[1].flag == Base::id)
            send("mov",nametable[pop[1].addr],"",0);
        send("ret","","","");
        left.addr = nextquad;
        return true;
    }
    //    bool function27()
    //    {

    //        left.value = pop[0].value;
    //        if (pop.size() == 3)
    //        {
    //            left.value += "," + pop[2].value;
    //        }
    //        return true;
    //    }

    bool function27()
    {
        Base list;
        if (pop.size() == 3)
        {
            list = pop[0];
            left.addr = pop[2].addr + 1;
        }
        if (pop.size() == 1)
        {
            list = pop[0];
            left.addr = 1;
        }
        //        if (list.flag == Base::num)
        //            send("push","","",list.value);
        //        if (list.flag == Base::id)
        //        {
        send("push","","",list.value);
        //        }

        //        if (list.flag == Base::temp)
        //        {
        //            send("push","","",list.value);
        //        }

        //        left.value = pop[0].value;
        //        if (pop.size() == 3)
        //        {
        //            left.value += "," + pop[2].value;
        //        }
        return true;
    }
    bool function28()
    {
        //        if (pop.size() == 4)
        //        {
        //            int begin = nextquad - pop[2].addr;
        //            int end = nextquad - 1;
        //            if (begin > end)
        //                return false;
        //            while(begin < end)
        //            {
        //                Four temp = four[begin];
        //                four[begin++] = four[end];
        //                four[end--] = temp;
        //            }
        //        }
        send("call","","",pop[0].value);
        //        if (pop.size() == 3)
        //        {
        //            send("call","","",pop[0].value);
        //        }
        //        if (pop.size() == 4)
        //        {
        //            if (pop[2].value.find("eax") != string::npos)
        //                nametable.releaseTemp(0);
        //            if (pop[2].value.find("ebx") !=  string::npos)
        //                nametable.releaseTemp(1);
        //            if (pop[2].value.find("ecx") !=  string::npos)
        //                nametable.releaseTemp(2);
        //            if (pop[2].value.find("edx") !=  string::npos)
        //                nametable.releaseTemp(3);
        //            if (pop[2].value.find("eex") !=  string::npos)
        //                nametable.releaseTemp(4);

        //            send("call",pop[2].value,"",pop[0].value);
        //        }
        return true;
    }

    bool function29()
    {
        string id;
        if (pop.size() == 1)
            id = pop[0].value;
        if (pop.size() == 2)
            id = pop[1].value;
        int i = nametable.getAddr(id);
        if (i == -1)
        {
            cout << "变量" << id << "未定义" << endl;
            return false;
        }
        if (nametable.getSize(i) > 0 || pop.size() == 2)
        {
            send("lea",id,"","eax");
            send("push","","","eax");
        }
        else
            send("push","","",id);
        return true;

    }

    bool function30()
    {

    }

    bool function31()
    {

        string name = "string"+convert<string>(nametable.count++);
        int i = nametable.newAddr("string",name);
        nametable.setSize(i,pop[2].value.size()+1);
        for (int j = 0;j < pop[2].value.size();j++)
        {
            string temp;
            if (pop[2].value[j] == '\n')
                temp = "10";
            else
            {
                temp = "\'";
                temp += pop[2].value[j];
                temp += "\'";
            }

            send("mov",temp,"",name+"+"+convert<string>(j));
        }
        send("mov","0","",name + "+"+convert<string>(pop[2].value.size()));

        send("lea",name,"","eax");
        send("push","","","eax");
        send("call","","","crt_printf");
        return true;


    }

    bool function32()
    {
        string name = "string"+convert<string>(nametable.count++);
        int i = nametable.newAddr("string",name);
        nametable.setSize(i,pop[2].value.size()+1);
        for (int j = 0;j < pop[2].value.size();j++)
        {
            string temp;
            if (pop[2].value[j] == '\n')
                temp = "10";
            else
            {
                temp = "\'";
                temp += pop[2].value[j];
                temp += "\'";
            }

            send("mov",temp,"",name+"+"+convert<string>(j));
        }
        send("mov","0","",name + "+"+convert<string>(pop[2].value.size()));

        send("lea",name,"","eax");
        send("push","","","eax");
        send("call","","","crt_scanf");
        return true;
    }

    void printQuad()
    {

        for (int j = 0;j < nametables.size();j++)
        {
            nametables[j].print();

            for (int i = 0;i < nametables[j].four.size();i++)
            {
                cout << i << ":" << "(" << nametables[j].four[i].op << "," << nametables[j].four[i].a << "," << nametables[j].four[i].b << "," ;
                cout << nametables[j].four[i].addr;
                cout << ")" << endl;
            }
        }
    }

    void deleteFour(int pos)
    {
        for (int i = pos + 1;i < four.size();i++)
        {
            if (four[i].op == "jmp" || four[i].op == ">="|| four[i].op == "<=" ||four[i].op == "<" || four[i].op == ">" ||four[i].op == "==")
            {
                four[i].addr = convert<string>(convert<int>(four[i].addr)-1);
            }
        }
        four.erase(four.begin()+pos,four.begin()+pos+1);
    }

    bool parser()
    {
        while(!stateStack.empty())
            stateStack.pop();
        while(!eleStack.empty())
            eleStack.pop();

        Token ip = getNext();
        stateStack.push(0);
        eleStack.push(Base(beginTokenId));

        int sentence = 0;
        nextquad = 0;

        for (int i = 0;i < elements.size();i++)
        {
            if (elements[i].name == "sentence")
            {
                sentence = i;
                cout << "find sentence!" << endl;
                break;
            }

        }
        while(1)
        {
            //            cout << stateStack.top() << "  " << termMap[ip] << endl;
            if (ip.type != -1)
                cout << "token:" << elements[ip.type] << endl;
            Action actiontemp = action[stateStack.top()][termMap[ip.type]] ;
            if (actiontemp.type == Action::shift)
            {
                //                cout << "移入：" << actiontemp.state << "  " << elements[ip].name << endl;
                stateStack.push(actiontemp.state);
                eleStack.push(Base(ip.type,ip.value));
                ip = getNext();
            }

            else if (actiontemp.type == Action::reduce)
            {
                cout << "规约:";
                IRule rule = getIRule(actiontemp.rule);
                showIRule(rule);
                pop.clear();


                for (int i = 0;i < rule.size();i++)
                {
                    stateStack.pop();
                    pop.push_back(eleStack.top());
                    //                    cout << "出栈!" << endl;
                    eleStack.pop();
                }
                int k = pop.size();
                for (int i = 0;i < k/2;i++)
                {
                    Base temp = pop[i];
                    pop[i] =  pop[k  - i-1];
                    pop[k  - i-1] = temp;
                }

                left.type = rule.left;
                if (rule.index > 0)
                {
                    bool success = select(rule.index);
                    if (success == false)
                    {
                        return false;
                    }
                }

                eleStack.push(left);
                int temp = stateStack.top();
                stateStack.push(goTo[temp][nonTermMap[rule.left]]);
                //                cout << "入栈：" << goTo[temp][nonTermMap[rule.left]] << elements[rule.left] << endl;
            }
            else if (actiontemp.type == Action::accept)
            {
                cout << "语法分析完成！" << endl;
                printQuad();
                return true;
            }
            else
            {
                cout << ip.linenode - 1 << ":在" << elements[ip.type] <<"附近出现语法错误!" << endl;
                return false;
                //                vector<int> p;
                //                for (int i = 0;i < elements.size();i++)
                //                {
                //                    if (elements[i].name == "{")
                //                    {
                //                        p.push_back(i);
                //                    }
                //                    if (elements[i].name == "return")
                //                    {
                //                        p.push_back(i);
                //                    }
                //                    if (elements[i].name == "(")
                //                    {
                //                        p.push_back(i);
                //                    }
                //                    if (elements[i].name == "num")
                //                    {
                //                        p.push_back(i);
                //                    }
                //                    if (elements[i].name == "id")
                //                    {
                //                        p.push_back(i);
                //                    }
                //                    if (elements[i].name == "for")
                //                    {
                //                        p.push_back(i);
                //                    }
                //                }

                //                while(goTo[stateStack.top()][nonTermMap[sentence]] < 0 && !stateStack.empty() && !eleStack.empty())
                //                {
                //                    stateStack.pop();
                //                    eleStack.pop();
                //                }

                //                if (stateStack.empty() && eleStack.empty())
                //                    return false;
                //                int count = 0;
                //                while(1)
                //                {

                //                    if (ip == -1)
                //                        return false;

                //                    bool find = false;
                //                    for (int i = 0;i < p.size();i++)
                //                    {
                //                        if (ip == p[i])
                //                        {
                //                            int temp = stateStack.top();
                //                            stateStack.push(goTo[temp][nonTermMap[sentence]]);
                //                            eleStack.push(nonTermMap[p[i]]);
                //                            find = true;
                //                        }
                //                    }

                //                    if (find == true)
                //                        break;
                //                    else
                //                        ip = getNext();

                //                }

            }
        }
    }
    vector<NameTable> getNameTables()
    {
        return nametables;
    }
};



#endif // GENERATOR_H
