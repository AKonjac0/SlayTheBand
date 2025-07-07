#ifndef ENEMYANIMATION_H
#define ENEMYANIMATION_H

#include "CharacterAnimation.h"
#include "Buff.h"
#include <QObject>

class EnemyAnimation: public CharacterAnimation {
    Q_OBJECT
public:
    EnemyAnimation(QWidget* _parent);
    ~EnemyAnimation();
    void init();
    void show(int, int, int, int, int, int);
    // set current HP
    void setHealthBarAnimation(int HP);
    // set max HP
    void setMaxHealthBarAnimation(int maxHP);

    void setIntent(Buff intent);
signals:
    void getName();
private:
    QPushButton *intention;
};

#endif
