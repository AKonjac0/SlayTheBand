#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "mainwindow.h"

class Player : public Character
{
public:
    Player(QString _name, int _HP, MainWindow* _parent, int _MP);
    int getMP(){return MP;}
    int getMaxMP(){return maxMP;}
    void MP_change(int amount);
private:
    int MP;
    int maxMP;
};

#endif // PLAYER_H
