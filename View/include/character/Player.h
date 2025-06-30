#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <QWidget>
#include "Manabar.h"

class Player : public Character
{
public:
    Player(QString _name, int _HP, QWidget* _parent, int _MP);
    int getMP() const {return MP;}
    int getMaxMP() const {return maxMP;}
    void MP_change(int amount);
    void show_character (int, int, int, int) override;
    ManaBar* getManaBar(){ return manaBar;}
private:
    int MP;
    int maxMP;
    QMovie* illustration;
    ManaBar* manaBar;
};

#endif // PLAYER_H
