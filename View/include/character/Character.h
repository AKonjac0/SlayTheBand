#ifndef CHARACTER_H
#define CHARACTER_H

#include "QWidget"
#include <QLabel>
#include <QString>
#include <QMovie>
#include "healthbar.h"

class Character
{
public:
    Character(QString _name, int _HP, QWidget* _parent);
    virtual ~Character();

    int getHP() const { return HP; }
    QString getname() const { return name; }
    void setHP(int newHP);

    void show_character(int, int, int, int);
    QLabel* getAvatar() { return character_avatar; }

private:
    QWidget* parent;
    int HP;
    int maxHP;
    QString name;
    QLabel* character_avatar;
    QMovie* illustration;
    HealthBar* healthBar;  // 血条控件
};

#endif // CHARACTER_H
