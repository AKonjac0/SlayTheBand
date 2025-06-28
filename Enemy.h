#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "mainwindow.h"

class Enemy : public Character
{
public:
    Enemy(QString _name, int _HP, MainWindow* _parent);
};

#endif // ENEMY_H
