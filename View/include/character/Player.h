#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <QWidget>
#include "Manabar.h"
// #include "Card_Manager.h"
// #include "CardView.h"

class Player : public Character
{
public:
    Player(QString _name, int _HP, QWidget* _parent, int _MP);
    int getMP() const {return MP;}
    int getMaxMP() const {return maxMP;}
    void MP_change(int amount);
    void show_character (int, int, int, int) override;
    ManaBar* getManaBar(){ return manaBar;}
private:
    int MP;
    int maxMP;
    ManaBar* manaBar;

    // TBD: encapsule card logic into player
    // Card_Manager* cardManager;
    // CardView* cardView;

};

#endif // PLAYER_H
