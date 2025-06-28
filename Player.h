#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "mainwindow.h"

class Player : public Character
{
public:
    Player(QString _name, int _HP, MainWindow* _parent, int _MP);
    int getMP(){return MP;}
private:
    int MP;
};

#endif // PLAYER_H
