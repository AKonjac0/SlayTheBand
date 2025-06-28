#ifndef CHARACTER_H
#define CHARACTER_H

#include "Buff.h"
#include "mainwindow.h"
#include "Card.h"
#include <QLabel>
#include "healthbar.h"

class Character
{
public:
    Character(QString _name, int _HP, MainWindow* _parent);
    virtual ~Character();

    int getHP() const { return HP; }
    QString getname() const { return name; }
    void setHP(int newHP);

    void show_character(int, int, int, int);
    QLabel* getAvatar() { return character_avatar; }

private:
    MainWindow* parent;
    QVector<Buff> buff;
    QVector<Card*> hand_cards;
    int HP;
    int maxHP;
    QString name;
    QLabel* character_avatar;
    HealthBar* healthBar;  // 血条控件
};

#endif // CHARACTER_H
