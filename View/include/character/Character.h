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
    int getmaxHP() const { return maxHP;}
    void HP_change(int amount);
    virtual void show_character(int, int, int, int) = 0;
    QLabel* getAvatar() const { return character_avatar; }
    HealthBar* getHealthBar() const { return healthBar; }
    QMovie* getIllustration() const { return illustration; }

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
