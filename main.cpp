#include <iostream>
#include "scanner.h"
#include <string>
#include "element.h"
#include "grammar.h"
#include "generator.h"
#include "rule.h"
#include <fstream>
#include "masm.h"
using namespace std;


int main()
{
    streambuf* coutBuf = cout.rdbuf();
    ofstream of("out.txt");
    // 获取文件out.txt流缓冲区指针
    streambuf* fileBuf = of.rdbuf();

    // 设置cout流缓冲区指针为out.txt的流缓冲区指针
    cout.rdbuf(fileBuf);
//    cout.rdbuf(coutBuf);

    Grammar  grammar;
    grammar.getFileElement("element.txt");
    grammar.getFileRule("cfg.txt");



    grammar.setStart(Element(Element::non_terminator,"S"));


    Generator generator;
    if(!generator.init(grammar)) {
        cout << "error input grammar." << std::endl;
        return 1;
    }

    if(!generator.generator()) {
        cout << "error generator LALR table." << std::endl;
        return 1;
    }

    Scanner scanner;
    string fileName("1.cpp");
    while(1)
    {
    if(scanner.getCode(fileName))
    {
        if(!scanner.scan())
        {
            cout << "语法分析扫描失败！" << endl;
            return 1;
        }
        scanner.print();
    }

    if (!generator.getTokens(scanner.getToken()))
    {
        cout << "获取Token表失败！" << endl;
        return 1;
    }
    generator.parser();
    Masm32 masm;
    masm.getNameTable(generator.getNameTables());
    masm.translate();

    cout.rdbuf(coutBuf);
    cout << "文件翻译完成！按任意键，继续翻译。。" << endl;
    string aa;
    cin >> aa;
    cout.rdbuf(fileBuf);
    }
    return 0;
}

