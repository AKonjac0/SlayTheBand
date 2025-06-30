#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include <QWidget>

class Enemy : public Character
{
public:
    Enemy(QString _name, int _HP, QWidget* _parent);
    void show_character (int, int, int, int) override;
};

#endif // ENEMY_H
