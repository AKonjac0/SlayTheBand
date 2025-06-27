#ifndef BUFF_H
#define BUFF_H
enum BuffType {No, Defence, Vulnerability};

class Buff{
public:
    Buff(BuffType, int);
private:
    BuffType type;
    int level;
};

#endif // BUFF_H
