#ifndef GRAMMAR_H
#define GRAMMAR_H
#include "rule.h"
#include "element.h"
#include "elementset.h"
#include "fstream"
#include <iostream>
#include <sstream>
using namespace std;
class Grammar
{
public:
    vector<Rule> rules;
    Rule start;
    ElementSet elements;
    void add(Rule rule)
    {
        rules.push_back(rule);
    }
    void setStart(Rule rule)
    {
        start = rule;
    }
    Rule getStart()
    {
        return start;
    }

    vector<Rule> getRules()
    {
        return rules;
    }

    void getFileElement(string filename)
    {
        int nonTerminator,terminator;

        fstream file;
        file.open(filename.c_str(),ios::in);
        file >> nonTerminator;
        string name;
        for (int i = 0;i < nonTerminator;i++)
        {
            file >> name;
            //            cout << name;
            if (name.size() > 0)
                elements.push_back(Element(Element::non_terminator,name));
        }
        file >> terminator;
        for (int i = 0;i < terminator;i++)
        {
            file >> name;
            if (name.size() > 0)
                elements.push_back(Element(Element::terminator,name));
        }
//                for (int i = 0;i < elements.size();i++)
//                    cout << elements[i] << endl;
        file.close();
    }

    void getFileRule(string filename)
    {
        fstream file;
        string line,leftstr,temp,rightstr;
        file.open(filename.c_str(),ios::in);
        for (int i = 0;i < elements.size();i++)
        {
            cout << i << ":" << elements[i] << endl;
        }
        while(file)
        {
            getline(file,line);
            //            cout << line;
            stringstream stream(line);
            if (!(stream >> leftstr))
                break;

            Element left;
            ElementSet right;
            for (int i = 0;i < elements.size();i++)
            {
                if (elements[i].name == leftstr)
                {
                    left = elements[i];
                    break;
                }
                if (i == elements.size()-1)
                {
                    cout << "未知元素：" << left << endl;
                }
            }
            while(stream >> rightstr)
            {
                for (int i = 0;i < elements.size();i++)
                {
                    if (elements[i].name == rightstr)
                    {
                        right.push_back(elements[i]);
                        break;
                    }
                    if (i == elements.size() - 1)
                        cout << "未知元素：" << rightstr << endl;
                }
            }
            add(Rule(left,right));
                        cout << Rule(left,right) << endl;
        }
        file.close();
    }

    void showRules()
    {
        for (unsigned int i = 0;i < rules.size();i++)
            cout << rules[i] << endl;
    }
};

#endif // GRAMMAR_H
