#ifndef ELEMENT_H
#define ELEMENT_H
#include "define.h"
class ElementSet;
class Element
{
public:
    typedef enum{
        none,            /***  无效的符号 */
        terminator,      /***  终结符     */
        non_terminator  /***  非终结符   */
    }Type;
    Type type;
    string name;
    static Element  null;  /*** 空符号 */

    Element(Type type,string name)
    {
        this->type = type;
        this->name = name;
    }
    Element()
    {

    }

    bool isTerminator()
    {
        return type == terminator;
    }

    bool isNonTerminator()
    {
        return type == non_terminator;
    }

    bool isValid() {
        return type == terminator || type == non_terminator;
    }

    Element eof()
    {
        return Element(terminator,"#");
    }

    bool equal (const Element& right) const {
        return this->type == right.type
                && this->name == right.name;
    }

    bool operator == (const Element& right) const {
        return  equal(right);
    }
    bool operator != (const Element& right) const {
        return  !equal(right);
    }

    friend ostream& operator << (ostream& os, const Element& element) {
        os << element.name;
        return os;
    }
public:
    ElementSet operator + (const Element  & left);


};

#endif
