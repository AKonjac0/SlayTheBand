#ifndef ENEMY_H
#define ENEMY_H

#include <QWidget>
#include "EnemyMeta.h"
#include "EnemyAnimation.h"

class Enemy
{
public:
    Enemy(QString _name, int _HP, QWidget* _parent);
    ~Enemy();

    // Same as Player, basically
    void HP_change(int amount);
    void setHP(int hp);
    void maxHP_change(int amount);
    void setMaxHP(int maxhp);

    // get meta
    int getHP() const { return enemyMeta->getHP(); }
    int getMaxHP() const { return enemyMeta->getmaxHP(); }
    QString getName() const { return enemyMeta->getname(); }
    QVector<Buff> getBuff() const { return enemyMeta->getBuff(); }
    QSize getSize() const { return enemyAnimation->getSize(); }
    void addBuff(Buff &buff) { enemyMeta->addBuff(buff);}
    QLabel *getAvatar() { return enemyAnimation->getAvatar(); }
    QPushButton *getButton() { return enemyAnimation->getButton(); }
    void clearBuff() { enemyMeta->clearBuff(); }

    void show(int x, int y, int width, int height);
private:
    // Model
    EnemyMeta* enemyMeta;
    // View
    EnemyAnimation* enemyAnimation;

};

#endif // ENEMY_H
