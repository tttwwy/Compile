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


    Grammar  grammar;
    grammar.getFileElement("element.txt");
    grammar.getFileRule("cfg.txt");


    grammar.setStart(Element(Element::non_terminator,"S"));


    Generator generator;
    if(!generator.init(grammar)) {
        cout << "文法读取失败！" << std::endl;
        return 1;
    }
    cout.rdbuf(coutBuf);
    cout << "开始LR1分析表生成..." << endl;
    cout.rdbuf(fileBuf);
    if(!generator.generator()) {
        cout << "error generator LALR table." << std::endl;
        return 1;
    }
    cout.rdbuf(coutBuf);
    cout << "LR1分析表生成成功！" << endl;
    cout.rdbuf(fileBuf);
    Scanner scanner;
    string fileName("1.cpp");
    while(1)
    {
        if(scanner.getCode(fileName))
        {
            if(!scanner.scan())
            {
                cout << "词法分析扫描失败！" << endl;
                return 1;
            }
            scanner.print();
        }
        cout.rdbuf(coutBuf);
        cout << "词法分析扫描成功！" << endl;
        cout.rdbuf(fileBuf);

        if (!generator.getTokens(scanner.getToken()))
        {
            cout << "获取Token表失败！" << endl;
            return 1;
        }
        if (!generator.parser())
        {
            cout.rdbuf(coutBuf);
            cout << "语法分析失败！" << endl;
            cout.rdbuf(fileBuf);
            return 1;
        }
        cout.rdbuf(coutBuf);
        cout << "语法分析成功！" << endl;
        cout.rdbuf(fileBuf);
        Masm32 masm;
        masm.getNameTable(generator.getNameTables());
        masm.translate();

        cout.rdbuf(coutBuf);
        cout << "文件翻译完成！按任意键，重新编译!" << endl;
        getchar();
        //        string aa;
        //        cin >> aa;
        cout.rdbuf(fileBuf);
    }
    return 0;
}

