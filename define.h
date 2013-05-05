#ifndef DEFINE_H
#define DEFINE_H
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
template<class out_type,class in_value>
out_type convert(const in_value & t)

{
stringstream stream;
stream<<t;//向流中传值
out_type result;//这里存储转换结果
stream>>result;//向result中写入值
return result;
}

class Base
{
public:
    enum Flag {
        error = -1,
        id  = 0,
        num  = 1,
        temp = 2,
        array = 3
    };
    int type;
    string value;
    int addr;
    Flag flag;


    Base(int type,string value)
    {
        this->type = type;
        this->value = value;
        flag = error;
        addr = -1;

    }
    Base(int type)
    {
        this->type = type;
        flag = id;
        addr = -1;
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
