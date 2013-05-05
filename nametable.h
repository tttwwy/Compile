#ifndef NAMETABLE_H
#define NAMETABLE_H
#include "define.h"
#include "four.h"
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
    string functionname;
    string returntype;
    vector<Symbol> functionlist;
    vector<Four> four;
    NameTable()
    {
        clear();
    }

    void clear()
    {
        four.clear();
        functionlist.clear();
        returntype.clear();
        functionname.clear();
        symboltable.clear();
        for (int i = 0;i < 16;i++)
        {
            tempused[i] = false;
            symboltable.push_back(Symbol());
        }
        tempused[0] = true;

    }
    string getFunctionName()
    {
        return functionname;
    }

    void setFour(vector<Four> four)
    {
        this->four = four;
    }

    int getTypeSize(int pos)
    {
        if (pos >= tempsize && pos < symboltable.size())
        {
        string type = symboltable[pos].type;
        if (type == "int")
            return 4;
        if (type == "char")
            return 1;
        if (type == "double")
            return 4;
        if (type == "string")
            return 1;
        }

        return -1;
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

    int getSize(int pos)
    {
        if (pos >= tempsize && pos < symboltable.size())
        {
            return symboltable[pos].size;

        }
        return -1;
    }
    int getSize(string name)
    {
        int pos = getAddr(name);
        if ( pos == -1)
        {
           return -1;
        }
        return symboltable[pos].size;
    }

    int addlist(string type,string name)
    {
        functionlist.push_back(Symbol(type,name));
    }

    void setFunctionName(string name)
    {
        functionname = name;
    }

    void setReturnType(string type)
    {
        this->returntype = type;
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
                cout << " 申请临时变量" << i << endl;
                return i;
            }
        }
    }

    void releaseTemp(int i)
    {
        if (i >= 0 && i < tempsize)
            tempused[i] = false;
          cout << " 释放临时变量" << i << endl;
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
