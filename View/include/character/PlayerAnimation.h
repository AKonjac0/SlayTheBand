#ifndef PLAYERANIMATION_H
#define PLAYERANIMATION_H

#include "CharacterAnimation.h"
#include "Manabar.h"
#include <QObject>


class PlayerAnimation: public CharacterAnimation {
    Q_OBJECT
public:
    PlayerAnimation(QWidget* _parent);
    ~PlayerAnimation();
    void show(int, int, int, int, int, int, int, int);
    ManaBar* getManaBar(){ return manaBar;}

    // set current MP, HP
    void setManaBarAnimation(int MP);
    void setHealthBarAnimation(int HP);

    // set max MP, HP
    void setMaxManaBarAnimation(int maxMP);
    void setMaxHealthBarAnimation(int maxHP);
    void init();
signals:
    void getName();
private:
    ManaBar* manaBar;
};

#endif
