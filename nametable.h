#ifndef NAMETABLE_H
#define NAMETABLE_H
#include "define.h"
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;
#define tempsize 16
class Symbol
{
public:
    string name;
    string type;
    string value;
    int size;
    Symbol(string type,string name)
    {
        this->name = name;
        this->type = type;
        this->size = 0;
    }
    Symbol(string type,string name,string value)
    {
        this->name = name;
        this->type = type;
        this->value = value;
        this->size = 0;
    }
    Symbol()
    {

    }
};
class NameTable
{
public:
    bool tempused[tempsize];
    vector<Symbol> symboltable;
    NameTable()
    {
        clear();
    }

    void clear()
    {
        symboltable.clear();
        for (int i = 0;i < 16;i++)
        {
            tempused[i] = false;
            symboltable.push_back(Symbol());
        }

    }

    bool setValue(int pos,string value)
    {
        if (pos >= tempsize && pos < symboltable.size())
        {
            symboltable[pos].value = value;
            return true;
        }
        return false;
    }

    bool setSize(int pos,int size)
    {
        if (pos >= tempsize && pos < symboltable.size())
        {
            symboltable[pos].size = size;
            return true;
        }
        return false;
    }

    int newAddr(string type,string name)
    {
        if (getAddr(name) == -1)
        {
            symboltable.push_back(Symbol(type,name));
            return symboltable.size() - 1 ;
        }
        return -1;
    }

    int newAddr(string type,string name,string value)
    {
        if (getAddr(name) == -1)
        {
            symboltable.push_back(Symbol(type,name,value));
            return symboltable.size() - 1 ;
        }
        return -1;
    }



    int newTemp()
    {
        for (int i = 0;i < tempsize;i++)
        {
            if (tempused[i] == false)
            {
                tempused[i] = true;
                return i;
            }
        }
    }

    void releaseTemp(int i)
    {
        if (i >= 0 && i < tempsize)
            tempused[i] = false;
    }

    int getAddr(string name)
    {
        for (int i = tempsize;i < symboltable.size();i++)
        {
            if (symboltable[i].name == name)
                return i;
        }
        return -1;
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

    const string  operator [] (int pos) {
        if (pos >= 0 && pos < tempsize)
        {
            string temp;
            temp += "t";
            temp += convert<string>(pos);
            return temp;
        }
        else if (pos < symboltable.size())
            return symboltable[pos].name;

    }

};

#endif // NAMETABLE_H
