#include "scanner.h"

Scanner::Scanner()
{

}

bool Scanner::getCode(string path)
{
    ifstream file;
    ostringstream buf;
    char ch;

    file.open(path.c_str());
    if (!file)
    {
        cout << "文件打开失败！"<< endl;
        return false;
    }
    while(buf && file.get(ch))
        buf.put(ch);
    code = buf.str();
    file.close();
    return true;
}

bool Scanner::deleteComment()
{
    index = 0;
    char ch;
    string newcode;
    int state = 1;
    bool success = false;
    while(1)
    {
        ch = getNext();
        if (ch == '\0')
            break;
        if (state == 1)
        {
            if (ch == '/')
                state = 2;
            else
                newcode += ch;
        }

        else if (state == 2)
        {
            if (ch != '*')
            {
                state = 1;
                newcode += "/";
                newcode += ch;
            }
            else
            {
                state = 3;
                success = false;
            }
        }

        else if (state == 3)
        {
            if (ch == '*')
            {
                state  = 4;
            }
        }
        else if (state  == 4)
        {
            if (ch == '/')
                state = 5;
            else if (ch != '*')
                state = 3;

        }
        else if (state == 5)
        {
            success = true;
            state = 1;
        }
    }
    if (success)
        code = newcode;
    return success;

}

char Scanner::getNext()
{
    char ch;
    if (index < code.length())
    {
        index++;
        ch = code[index-1];
        return ch;
    }
    else
        return '\0';
}

void Scanner::getBack()
{
    if (index > 0)
        index--;
}

vector<Token> Scanner::getToken()
{
    return tokens;
}

DFAState Scanner::getstate(char c)
{

    if (c == ' ' || c == '\n' || c == '\r' || c == '\t')
        return START;
    else if ((c >= '0' && c <= '9')||c == '-')
        return DFANUM;
    else if ((c >= 'A' && c <= 'Z')|| (c >= 'a' && c <= 'z')|| c == '_')
        return DFAID;
    else if (c == '>' || c == '<' || c =='=' || c == '!'|| c == '+' || c == '-')
        return SYM;
    else if (c == '\'')
        return DFACHAR;
    else if (c == '\"')
        return DFASTR;
    else
        return DONE;
}

Types Scanner::getType(string str)
{
    if (str == "else")
        return ELSE;
    //    if (str == "main")
    //        return MAIN;
    if (str == "printf")
        return PRINTF;
    if (str == "scanf")
        return SCANF;
    if (str == "if")
        return IF;
    if (str == "int")
        return INT;
    if (str == "double")
        return DOUBLE;
    if (str == "char")
        return CHAR;
    if (str == "return")
        return RETURN;
    if (str == "void")
        return VOID;
    if (str == "while")
        return WHILE;
    if (str == "for")
        return FOR;
    if (str == "%")
        return MOD;
    if (str == "+")
        return PLUS;
    if (str == "-")
        return MINUS;
    if (str == "*")
        return MULTI;
    if (str == "/")
        return RDIV;
    if (str == "<")
        return LT;
    if (str == "<=")
        return LE;
    if (str == ">")
        return GT;
    if (str == ">=")
        return GE;
    if (str == "==")
        return EQ;
    if (str == "!=")
        return NEQ;
    if (str == "=")
        return ASSIGN;
    if (str == ";")
        return SEMI;
    if (str == ",")
        return COMMA;
    if (str == "(")
        return LPAREN;
    if (str == ")")
        return RPAREN;
    if (str == "[")
        return LMBRACKET;
    if (str == "]")
        return RMBRACKET;
    if (str == "{")
        return LBBRACKET;
    if (str == "}")
        return RBBRACKET;
    if (str == "/*")
        return LCOMMENT;
    if (str == "*/")
        return RCOMMENT;
    if (str == "&")
        return ADDR;
    if (str == "++")
        return PLUSPLUS;
    if (str == "--")
        return MINUSMINUS;



    for (int i = 0;i < str.length();i++)
    {
        int type = getstate(str[i]);
        if (i == 0)
        {
            if (type != DFAID)
                break;
        }
        else if (type != DFAID && type != DFANUM )
            break;
        if (i == (str.length()-1))
            return ID;
    }

    return ERROR;
}

bool Scanner::scan()
{
    deleteComment();
    tokens.clear();
    int line = 1;
    bool success = true;
    index = 0;
    Types type;
    string str;
    DFAState state = START;
    char ch;

    while(1)
    {

        if (state == START)//初始状态，空格
        {
            str = "";
            ch = getNext();
            if (ch == '\0')
                break;
            if (ch == '\n')
                line++;
            state = getstate(ch);
            if (state != START && (state != DFACHAR) && (state != DFASTR))
                str += ch;
        }
        else if(state == DFANUM)
        {
            if (ch == '-')
            {
                ch = getNext();
                if (ch < '0' || ch > '9')
                {
                    state = DONE;
                    getBack();
                      state = SYM;
                }
                else
                {
                    getBack();

                }
            }
            else
            {
                bool isdouble = false;
                while(1)
                {
                    ch = getNext();
                    if (ch == '\0')
                        return false;
                    state = getstate(ch);
                    if (state != DFANUM)
                    {
                        if (ch == '.'&& !isdouble)
                        {
                            isdouble = true;
                            str += ch;
                        }
                        else
                        {
                            if (state == DFAID)
                            {
                                type = ERROR;
                                str += ch;
                                break;
                            }
                            getBack();
                            state = DONE;
                            type = NUM;
                            break;
                        }
                    }
                    else
                        str += ch;
                }
            }
        }
        else if (state == DFACHAR)
        {
            bool isstr = false;
            while(!isstr)
            {
                ch = getNext();
                if (ch != '\'')
                {
                    if (ch == '\n')
                    {
                        cout <<line<<":"<<"缺少单引号！"<< endl;
                        success = false;
                        getBack();
                        state = START;
                        break;
                    }
                    if (ch == '\0')
                    {
                        cout <<line<<":"<<"缺少单引号！"<< endl;
                        return false;
                    }
                    str+=ch;
                }
                else
                {
                    if (str.length() > 1)
                    {
                        cout <<line<<":"<<"Char长度非法！"<< endl;
                        success = false;
                        state = START;
                        break;
                    }
                    isstr = true;
                    type = STR;
                    state = DONE;
                }
            }
        }
        else if (state == DFASTR)
        {
            bool isstr = false;
            while(!isstr)
            {
                ch = getNext();
                if (ch != '\"')
                {
                    if (ch == '\n')
                    {
                        cout <<line<<":"<<"缺少双引号！"<< endl;
                        success = false;
                        getBack();
                        state = START;
                        break;
                    }
                    if (ch == '\0')
                    {
                        cout <<line<<":"<<"缺少双引号！"<< endl;
                        return false;
                    }
                    char temp = getNext();
                    if (ch == '\\' && temp == 'n')
                        str += 10;
                    else
                    {
                        getBack();
                        str+=ch;
                    }
                }
                else
                {
                    isstr = true;
                    type = STR;
                    state = DONE;
                }
            }
        }
        else if (state == DFAID)
        {
            while(1)
            {
                ch = getNext();
                if (ch == '\0')
                    return false;
                state = getstate(ch);
                if (state != DFAID && state != DFANUM || ch == '-')
                {
                    getBack();
                    state = DONE;
                    break;
                }
                else
                    str += ch;
            }
        }
        else if (state == SYM)
        {
            char temp = ch;
            ch = getNext();
            if (ch == '\0')
                return false;
            else if (ch == '=')
                str += ch;
            else if ((ch == '+' && temp == '+')||(ch == '-' && temp == '-'))
                str += ch;
            else
                getBack();
            state = DONE;
        }
        else if (state == DONE)
        {
            Token temp;
            if (type == ERROR)
            {
                cout <<line<<":"<< "非法变量！"<< endl;
                success =false;
            }
            else if (type == NUM||type == STR)
            {
                temp.type = type;
                temp.value = str;
                temp.linenode = line;
                tokens.push_back(temp);
            }
            else
            {
                temp.type = getType(str);
                if (temp.type == ERROR)
                {
                    cout <<line<<":"<< "字符无法识别！"<< endl;
                    success = false;
                }
                else
                {
                    if (temp.type == ID)
                        temp.value = str;
                    temp.linenode = line;
                    tokens.push_back(temp);
                }
            }
            state = START;
            type = ELSE;

        }
    }
    //    this->success = success;

    for (int i = 0;i < tokens.size();i++)
    {
        if (tokens[i].type == ID && i + 1 < tokens.size() && tokens[i+1].type == LMBRACKET)
        {
            tokens[i].type = ARRAY;
        }

    }
    return success;
}

void Scanner::print()
{
    string name[] = {"ELSE","IF","INT","DOUBLE","CHAR","RETURN","VOID","WHILE","FOR","LE","GE","EQ","NEQ","LCOMMENT","RCOMMENT","LT","GT","ASSIGN","PLUS","MINUS","MULTI","RDIV","SEMI","COMMA","LPAREN","RPAREN","LMBRACKET","RMBRACKET","LBBRACKET","RBBRACKET","NUM","ID","STR","ERROR","ADDR","PLUSPLUS","MINUSMINUS","PRINTF","SCANF","MAIN","ARRAY","MOD"};

    for (int i = 0;i < tokens.size();i++)
    {
        cout  << "("<<name[tokens[i].type-1] <<",";
        if (tokens[i].type == ID || tokens[i].type == NUM || tokens[i].type == STR)
            cout <<" "<< tokens[i].value;
        cout <<")"<< endl;
    }
}
