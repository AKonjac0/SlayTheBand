#ifndef ENEMYANIMATION_H
#define ENEMYANIMATION_H

#include "CharacterAnimation.h"
#include "EnemyMeta.h"

class EnemyAnimation: public CharacterAnimation{
public:
    EnemyAnimation(EnemyMeta* _enemyMeta, QWidget* _parent);
    ~EnemyAnimation();
    void show(int, int, int, int, int, int);

    void setHealthBarAnimation(int HP);

private:
    
};

#endif
