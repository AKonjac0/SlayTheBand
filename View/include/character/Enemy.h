#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "mainwindow.h"

class Enemy : public Character
{
public:
    Enemy(QString _name, int _HP, MainWindow* _parent);
    void show_character (int, int, int, int) override;
};

#endif // ENEMY_H
