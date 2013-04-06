#ifndef ELEMENT_H
#define ELEMENT_H
#include "define.h"
class ElementSet;
class Element
{
public:
    typedef enum{
        none,            /***  ÎÞÐ§µÄ·ûºÅ */
        terminator,      /***  ÖÕ½á·û     */
        non_terminator  /***  ·ÇÖÕ½á·û   */
    }Type;
    Type type;
    string name;
    static Element  eof_;   /*** ½áÎ²·ûºÅ */
    static Element  null;  /*** ¿Õ·ûºÅ */

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

    static const Element &eof()
    {
        return eof_;
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

public:
    ElementSet operator + (const Element  & left);


};

#endif
