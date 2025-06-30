#ifndef CHARACTERANIMATION_H
#define CHARACTERANIMATION_H

#include "Enemy.h"
#include "Player.h"
#include <QPair>


// Maybe more animations here...
class CharacterAnimation {
public:
    CharacterAnimation(QPair<Player*, Enemy*>*);
    ~CharacterAnimation();
    void show();

private:
    QPair<Player*, Enemy*>* combatants;
};

#endif // CHARACTERANIMATION_H
