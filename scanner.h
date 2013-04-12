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
    NUM,ID,STR,ERROR
} Types;

typedef enum
{
    START = 1,DFANUM,DFAID,SYM,DFACHAR,DFASTR,DONE,DFAERROR
} DFAState;

struct Token
{
    Types type;
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
