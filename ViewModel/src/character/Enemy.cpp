#include "Enemy.h"

Enemy::Enemy(QString _name, int _HP, QWidget* _parent)
{
    enemyMeta = new EnemyMeta(_name, _HP, _HP);
    enemyAnimation = new EnemyAnimation(enemyMeta, _parent);
}

Enemy::~Enemy()
{
    if (enemyMeta) delete enemyMeta;
    if (enemyAnimation) delete enemyAnimation;
}

void Enemy::show(int x, int y, int width, int height)
{
    enemyAnimation->show(x, y, width, height, enemyMeta->getmaxHP(), enemyMeta->getHP());
}

void Enemy::HP_change(int amount)
{
    enemyMeta->HP_change(amount);
    int tempHP = enemyMeta->getHP();
    enemyAnimation->setHealthBarAnimation(tempHP);
}