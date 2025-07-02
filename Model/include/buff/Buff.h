#ifndef BUFF_H
#define BUFF_H
enum BuffType {No, Weak, Vulnerable};

class Buff{
public:
    Buff(BuffType, int, bool isAll = false);
private:
    BuffType type;
    int level;
    bool isAll;
};

#endif // BUFF_H
