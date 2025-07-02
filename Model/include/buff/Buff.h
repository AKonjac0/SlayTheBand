#ifndef BUFF_H
#define BUFF_H
enum BuffType {No, Damage, Block, Drawcard, Discard, Weak, Vulnerable, Strength, Dexterity, Addcard, Exhaust, Ethereal};

class Buff{
public:
    Buff(BuffType, int, bool isAll = false);
    ~Buff() = default;
private:
    BuffType type;
    int level;
    bool isAll;
};

#endif // BUFF_H
