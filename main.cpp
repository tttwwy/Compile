#include <iostream>
#include <scanner.h>
#include <string>
#include "element.h"
#include "grammar.h"
#include "rule.h"
using namespace std;


int main()
{
//    Scanner a;
//    string b;
//    cin >> b;
//    if(a.getCode(b))
//    {
//        if(a.scan())
//            a.print();
//    }
    Grammar  grammar;
    Element  e_prog(Element::non_terminator, "program");
    Element  e_expr(Element::non_terminator, "expression");
    Element  e_expr_unary(Element::non_terminator, "unary_expression");
    Element  e_expr_pow(Element::non_terminator, "power_expression");
    Element  e_expr_mul(Element::non_terminator, "mul_expression");
    Element  e_expr_add(Element::non_terminator, "add_expression");
    Element  e_expr_assign(Element::non_terminator, "assign_expresion");
    Element  e_expr_var(Element::non_terminator, "var_expression");
    Element  e_expr_func_call(Element::non_terminator, "function_call_expression");
    Element  e_param_list(Element::non_terminator, "parament_list");

    Element  ID(Element::terminator, "ID");
    Element  NUM(Element::terminator, "NUM");
    Element  ASSIGN(Element::terminator, "\"=\"");
    Element  ADD(Element::terminator, "\"+\"");
    Element  SUB(Element::terminator, "\"-\"");
    Element  MUL(Element::terminator, "\"*\"");
    Element  DIV(Element::terminator, "\"/\"");
    Element  MOD(Element::terminator, "\"%\"");
    Element  IDIV(Element::terminator, "\"\\\"");
    Element  POW(Element::terminator, "\"^\"");
    Element  LB(Element::terminator, "\"(\"");
    Element  RB(Element::terminator, "\")\"");
    Element  LSB(Element::terminator, "\"[\"");
    Element  RSB(Element::terminator, "\"]\"");
    Element  COMMA(Element::terminator, "\",\"");


    grammar.add(Rule(e_prog, e_expr+e_expr));
    grammar.add(Rule(e_expr, e_expr_assign));
//    grammar.add(Rule(e_expr_assign, e_expr_var + ASSIGN + e_expr_assign));
//    grammar.add(Rule(e_expr_assign, e_expr_add));
//    grammar.add(Rule(e_expr_add, e_expr_add + ADD + e_expr_mul));
//    grammar.add(Rule(e_expr_add, e_expr_add + SUB + e_expr_mul));
//    grammar.add(Rule(e_expr_add, e_expr_mul));
//    grammar.add(Rule(e_expr_mul, e_expr_mul + MUL + e_expr_pow));
//    grammar.add(Rule(e_expr_mul, e_expr_mul + DIV + e_expr_pow));
//    grammar.add(Rule(e_expr_mul, e_expr_mul + MOD + e_expr_pow));
//    grammar.add(Rule(e_expr_mul, e_expr_mul + IDIV + e_expr_pow));
//    grammar.add(Rule(e_expr_mul, e_expr_pow));
//    grammar.add(Rule(e_expr_pow, e_expr_unary + POW + e_expr_pow));
//    grammar.add(Rule(e_expr_pow, e_expr_unary));
//    grammar.add(Rule(e_expr_unary, LB + e_expr + RB));
//    grammar.add(Rule(e_expr_unary, ADD + e_expr_unary));
//    grammar.add(Rule(e_expr_unary, SUB + e_expr_unary));
//    grammar.add(Rule(e_expr_unary, NUM));
//    grammar.add(Rule(e_expr_unary, e_expr_var));
//    grammar.add(Rule(e_expr_unary, e_expr_func_call));
//    grammar.add(Rule(e_expr_var, ID));
//    grammar.add(Rule(e_expr_var, e_expr_var + LSB + e_expr + RSB));
//    grammar.add(Rule(e_expr_func_call, e_expr_var + LB + e_param_list + RB));
//    grammar.add(Rule(e_param_list));
//    grammar.add(Rule(e_param_list, e_expr));
//    grammar.add(Rule(e_param_list, e_param_list + COMMA + e_expr));
//    grammar.setStart(e_prog);


}

