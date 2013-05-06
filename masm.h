#ifndef MASM_H
#define MASM_H
#include "four.h"
#include "define.h"
#include "nametable.h"
#include <fstream>
#include <iostream>
using namespace std;
class Masm32
{
public:
    vector<NameTable> nametables;
    void getNameTable(vector<NameTable> nametables)
    {
        this->nametables = nametables;
        for (int i = 0;i < nametables.size();i++)
        {
            if (nametables[i].functionname == "main" && i < nametables.size() - 1)
            {
                NameTable temp = nametables[i];
                nametables[i]=  nametables[nametables.size() -1]  ;
                nametables[nametables.size() -1] = temp;
            }
        }
    }

    void translate()
    {
        ofstream of("test\\CONSOLE.asm");
        // 获取文件out.txt流缓冲区指针
        streambuf* fileBuf = of.rdbuf();
        streambuf* coutBuf = cout.rdbuf();

        // 设置cout流缓冲区指针为out.txt的流缓冲区指针
        cout.rdbuf(fileBuf);


        cout << ".386" << endl;
        cout << ".model flat,stdcall" << endl;
        cout << "option casemap :none" << endl;
        cout << "include windows.inc" << endl;
        cout << "include user32.inc" << endl;
        cout << "include msvcrt.inc" << endl;
        cout << "include kernel32.inc" << endl;
        cout << "include masm32.inc" << endl;
        cout << "include gdi32.inc" << endl;
        cout << "includelib gdi32.lib" << endl;
        cout << "includelib user32.lib" << endl;
        cout << "includelib kernel32.lib" << endl;
        cout << "includelib masm32.lib" << endl;
        cout << "includelib msvcrt.lib" << endl;
        cout << "include macro.asm" << endl;
        cout << ".data" << endl;
        cout << "buffer	db MAX_PATH dup(?)" << endl;
        cout << ".code" << endl;
        for (int i = 0;i < nametables.size();i++)
        {
            translateFunction(nametables[i]);
            cout << endl << endl;
        }
        cout.rdbuf(coutBuf);
    }
    void translateFunction(NameTable nametable)
    {
        cout << nametable.functionname << " " << "proc " ;
        for (int i = 0;i < nametable.functionlist.size();i++)
        {
            if (i == 0)
                cout << nametable.functionlist[i].name;
            else
                cout << "," << nametable.functionlist[i].name;
        }
        cout << endl;


        for (int i = tempsize+nametable.functionlist.size();i < nametable.symboltable.size();i++)
        {
            cout << "local " <<  nametable.symboltable[i].name;
            if (nametable.symboltable[i].size > 0)
                cout << "[" << nametable.symboltable[i].size << "]";
            cout << ":";
            if (nametable.getTypeSize(i) == 1)
                cout << "BYTE";
            else if (nametable.getTypeSize(i) == 4)
                cout << "DWORD";
            cout << endl;
        }
        if (nametable.functionname != "main")
        {
            cout << "push ebx" << endl;
            cout << "push ecx" << endl;
            cout << "push edx" << endl;
            //            cout << "pushad" << endl;
        }
        int count = 0;
        map<int,string> jmp;
        vector<Four> four = nametable.four;
        for (int i = 0;i< four.size();i++)
        {
            if (four[i].op == "jmp" || four[i].op == ">="|| four[i].op == "<=" ||four[i].op == "<" || four[i].op == ">" ||four[i].op == "=="||four[i].op == "!=")
            {
                int t = convert<int>(four[i].addr);
                if (t >= four.size())
                    four.push_back(Four("ret","","",""));
                if (jmp[t].size() == 0)
                {
                    jmp[t] = "jmp" + convert<string>(count);
                    count++;
                }
                four[i].addr = jmp[t];
            }
        }

        for (int i = 0;i < four.size();i++)
        {
            Four one = four[i];
            if (jmp[i].size() > 0)
                cout << jmp[i] << ":";

            if (one.op == "mov" || one.op == "lea")
            {
                cout << one.op<<" " <<  one.addr << "," <<  one.a << endl;
            }
            else if (one.op == "jmp")
            {

                cout << "jmp " << one.addr << endl;
            }

            else if (one.op == "+" || one.op  == "-"|| one.op  == "*"|| one.op  == "/"|| one.op == "%")
            {
                cout << "mov " << "eax," << one.a << endl;
                if (one.op  == "+")
                    cout << "add " << "eax," << one.b << endl;
                if (one.op  == "-")
                    cout << "sub " << "eax," << one.b << endl;
                if (one.op  == "*")
                {
                    cout << "mov edx," << one.b << endl;
                    cout << "imul edx" << endl;
                }
                if (one.op  == "/")
                {
                    cout << "cdq"  << endl;
                    cout << "mov ebx," << one.b << endl;
                    cout << "idiv ebx"  << endl;
                }
                cout << "mov " << one.addr  << ",eax" << endl;
                if (one.op == "%")
                {
                    cout << "idiv "  << one.b << endl;
                    cout << "mov " << one.addr << ",edx"  << endl;
                }
            }

            else if (one.op == ">="|| one.op == "<=" ||one.op == "<" || one.op == ">" ||one.op == "==" || one.op == "!=")
            {
                cout << "mov eax," << one.a << endl;
                cout << "cmp eax," <<one.b << endl;
                if (one.op == ">=")
                    cout << "jge " << one.addr << endl;
                else if (one.op == "<=")
                    cout << "jle " << one.addr << endl;
                else if (one.op == "<")
                    cout << "jl " << one.addr << endl;
                else if (one.op == ">")
                    cout << "jg " << one.addr << endl;
                else if (one.op == "==")
                    cout << "je " << one.addr << endl;
                else if (one.op == "!=")
                   cout << "jne " << one.addr << endl;
            }
            else if (one.op == "call")
            {
//                if (one.addr != "crt_printf" && one.addr != "crt_scanf")
                    cout << "call " << one.addr << endl;
//                else
//                {
//                    cout << "invoke " << one.addr;
//                    if (one.a.size() > 0)
//                        cout <<"," << one.a ;
//                    cout << endl;
//                }
            }

            else if (one.op == "ret")
            {
                if (nametable.functionname == "main")
                {
                    cout << "invoke StdIn,addr buffer,sizeof buffer" << endl;
                    cout << "invoke ExitProcess,0" << endl;
                }
                if (nametable.functionname != "main")
                {
                    cout << "pop edx" << endl;
                    cout << "pop ecx" << endl;
                    cout << "pop ebx" << endl;
                }
                cout << "ret" << endl;
            }
            else if (one.op == "push")
            {
                cout << "push " << one.addr << endl;
            }
        }



        cout << nametable.functionname <<" endp" << endl;
        if (nametable.functionname == "main")
            cout << "end main" << endl;

    }





};

#endif // MASM_H
