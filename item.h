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
//    static Item nullItem;
//    static const Item& nullItem()
//    {
//        return nullItem;
//    }
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

    bool isValid()
    {
        return! (forward == invalid_forward || pos == invalid_pos
                || rule == invalid_ruleId);
    }

    Item(const Item& other)
    {
        rule = other.rule;
        pos = other.pos;
        forward = other.forward;
    }

    int getRule() const
    {
        return rule;
    }
    int getPos() const
    {
        return pos;
    }
    int getForward() const
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
        if (other.getRule() != this->getRule())
            return other.getRule() < this->getRule();

        if (other.getPos()!= this->getPos())
            return other.getPos() < this->getPos();

        if (other.getForward()!= this->getForward())
            return other.getForward() < this->getForward();
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
