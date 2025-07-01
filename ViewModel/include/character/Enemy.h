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
    void HP_change(int amount);
    void show(int x, int y, int width, int height);
    QSize getSize() const { return enemyAnimation->getSize(); }
private:
    // Model
    EnemyMeta* enemyMeta;
    // View
    EnemyAnimation* enemyAnimation;
};

#endif // ENEMY_H
