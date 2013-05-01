#ifndef DEFINE_H
#define DEFINE_H
#include <string>
#include <iostream>
using namespace std;
class Base
{
public:
    enum Flag {
        error = -1,
        id  = 0,
        num  = 1
    };
    int type;
    string value;
    int addr;
    Flag flag;
    int quad;

    Base(int type,string value)
    {
        this->type = type;
        this->value = value;
        flag = error;
        quad = 0;
    }
    Base(int type)
    {
        this->type = type;
        flag = id;
    }

    Base()
    {

    }
};

class Token
{
public:
    int type;
    string value;
    int linenode;
    Token (int type)
    {
        this->type = type;
    }
    Token(int type,string value)
    {
        this->type = type;
        this->value = value;
    }
    Token()
    {
        type = -1;
        linenode = -1;
    }
};
#endif // DEFINE_H
