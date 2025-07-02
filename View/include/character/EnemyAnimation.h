#ifndef ENEMYANIMATION_H
#define ENEMYANIMATION_H

#include "CharacterAnimation.h"
#include "EnemyMeta.h"

class EnemyAnimation: public CharacterAnimation{
public:
    EnemyAnimation(EnemyMeta* _enemyMeta, QWidget* _parent);
    ~EnemyAnimation();
    void show(int, int, int, int, int, int);


    // set current HP
    void setHealthBarAnimation(int HP);
    // set max HP
    void setMaxHealthBarAnimation(int maxHP);

private:
    
};

#endif
