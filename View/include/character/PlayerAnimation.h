#ifndef PLAYERANIMATION_H
#define PLAYERANIMATION_H

#include "CharacterAnimation.h"
#include "Manabar.h"
#include "PlayerMeta.h"

class PlayerAnimation: public CharacterAnimation{
public:
    PlayerAnimation(PlayerMeta* _playerMeta, QWidget* _parent);
    ~PlayerAnimation();
    void show(int, int, int, int, int, int, int, int);
    ManaBar* getManaBar(){ return manaBar;}
    void setManaBarAnimation(int MP);
    void setHealthBarAnimation(int HP);

private:
    ManaBar* manaBar;
};

#endif
