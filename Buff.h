#ifndef BUFF_H
#define BUFF_H
enum BuffType {No, Weak, Vulnerable};

class Buff{
public:
    Buff(BuffType, int);
private:
    BuffType type;
    int level;
};

#endif // BUFF_H
