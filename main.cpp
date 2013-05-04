#include <iostream>
#include "scanner.h"
#include <string>
#include "element.h"
#include "grammar.h"
#include "generator.h"
#include "rule.h"
#include <fstream>
using namespace std;


int main()
{
//    streambuf* coutBuf = cout.rdbuf();
    ofstream of("out.txt");
    // 获取文件out.txt流缓冲区指针
    streambuf* fileBuf = of.rdbuf();

    // 设置cout流缓冲区指针为out.txt的流缓冲区指针
    cout.rdbuf(fileBuf);

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
//    cin >> fileName;
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
    return 0;
}

