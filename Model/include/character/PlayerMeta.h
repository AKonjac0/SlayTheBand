#ifndef PLAYERMETA_H
#define PLAYERMETA_H
#include "CharacterMeta.h"

class PlayerMeta : public CharacterMeta
{
public:
    PlayerMeta(QString _name, int _HP, int _maxHP, int _MP);
    ~PlayerMeta() override = default;
    int getMP() const
    {
        return MP;
    }
    int getmaxMP() const
    {
        return maxMP;
    }
    void MP_change(int);
private:
    // Player Only
    int MP = 0;
    int maxMP = 0;
};


#endif // PLAYERMETA_H
