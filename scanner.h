#ifndef SCANNER_H
#define SCANNER_H
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
    NUM,ID,STR,ERROR,ADDR,PLUSPLUS,MINUSMINUS,PRINTF,SCANF,MAIN,ARRAY
} Types;

typedef enum
{
    START = 1,DFANUM,DFAID,SYM,DFACHAR,DFASTR,DONE,DFAERROR
} DFAState;

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

class Scanner
{
public:
    Scanner();

    bool getCode(string path);
    bool deleteComment();
    char getNext();
    void getBack();
    vector<Token> getToken();
    DFAState getstate(char c);
    Types getType(string str);
    bool scan();
    string code;
    vector<Token> tokens;
    vector<Token> id;
    void print();
    unsigned int index;

};

#endif
