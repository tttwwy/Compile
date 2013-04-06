#ifndef ITEM_H
#define ITEM_H

class Item
{
public:
    enum {
        invalid_ruleId = -1,
        invalid_pos     = -1,
        invalid_forward = -1
    };
    int rule;
    int pos;
    int forward;
    static Item nullItem;
    static const Item& nullItem()
    {
        return nullItem;
    }
    Item()
    {
        rule = invalid_ruleId;
        pos = invalid_pos;
        forward = invalid_forward;
    }
    Item(int rule,int pos,int forward)
    {
        this->rule = rule;
        this->pos = pos;
        this->forward = forward;
    }

    Item(const Item& other)
    {
        rule = other.rule;
        pos = other.pos;
        forward = other.forward;
    }

    int getRule()
    {
        return rule;
    }
    int getPos()
    {
        return pos;
    }
    int getForward()
    {
        return forward;
    }

    bool equal(const Item& other) const {
        return this->getRule()    == other.getRule()
                && this->getPos()     == other.getPos()
                && this->getForward() == other.getForward();
    }
    bool operator == (const Item& other) const {
        return equal(other);
    }

    bool operator <(const Item& other) const
    {
        if (other.get_rule() != this->get_rule())
            return other.get_rule() < this->get_rule();

        if (other.get_pos()!= this->get_pos())
            return other.get_pos() < this->get_pos();

        if (other.get_forward()!= this->get_forward())
            return other.get_forward() < this->get_forward();
    }


    /** 两个项目是否不相等 */
    bool operator != (const Item& other) const {
        return !equal(other);
    }
//    Item& operator = (const Item& other) {
//        if(this != &other) {
//            this->rule = other.rule;
//            this->pos = other.pos;
//            this->forward = other.forward;
//        }
//        return *this;
//    }


};

#endif // ITEM_H
