#ifndef FOUR_H
#define FOUR_H
#include <string>
using namespace std;
class Four
{
public:
    string op;
    string a;
    string b;
    string addr;
    Four(string op,string a,string b,string addr)
    {
        this->op = op;
        this->a = a;
        this->b = b;
        this->addr = addr;
    }
//    friend ostream& operator << (ostream& os, const Four& four) {
//        os << "(" << four.op << "," << four.a << "," << four.b << "," << four.c << ")";
//        return os;
//    }
};
#endif // FOUR_H
