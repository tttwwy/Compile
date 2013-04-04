#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;
typedef enum
{
    ELSE = 1,IF,INT,DOUBLE,CHAR,RETURN,VOID,WHILE,FOR,
    LE,GE,EQ,NEQ,LCOMMENT,RCOMMENT,LT,GT,ASSIGN,
    PLUS,MINUS,MULTI,RDIV,SEMI,COMMA,LPAREN,RPAREN,LMBRACKET,RMBRACKET,LBBRACKET,RBBRACKET,
    NUM,ID,STR,ERROR
} Type;

typedef enum
{
    START = 1,DFANUM,DFAID,SYM,DFACHAR,DFASTR,DONE,DFAERROR
} DFAState;

struct token
{
    Type type;
    string value;
    int linenode;
};

class Scanner
{
public:
    Scanner();

    bool getCode(string path);
    bool deleteComment();
    char getNext();
    void getBack();
    DFAState getstate(char c);
    Type getType(string str);
    bool scan();
    string code;
    vector<token> tokens;
    vector<token> id;
    void print();
    unsigned int index;

};

