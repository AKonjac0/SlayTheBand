#ifndef CHARACTER_H
#define CHARACTER_H
#include "Buff.h"
#include "mainwindow.h"
#include "Card.h"
#include <QLabel>

class Character
{
public:
    Character(QString _name, int _HP, MainWindow* _parent);
    virtual ~Character();
    int getHP(){return HP;}
    QString getname(){return name;}
    void show_character(int x, int y, int width, int height);
    QLabel* getAvatar(){return character_avatar;}
private:
    MainWindow* parent;
    QVector<Buff> buff;
    QVector<Card*> hand_cards;
    int HP;
    QString name;
    QLabel* character_avatar;
};

#endif // CHARACTER_H
