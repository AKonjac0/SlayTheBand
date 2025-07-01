#ifndef PLAYER_H
#define PLAYER_H
#include <QWidget>
#include "PlayerMeta.h"
#include "PlayerAnimation.h"
// #include "Card_Manager.h"
// #include "CardView.h"

class Player
{
public:
    Player(QString _name, int _HP, QWidget* _parent, int _MP);
    ~Player();
    void MP_change(int amount);
    void HP_change(int amount);
    void show(int x, int y, int width, int height);
    QSize getSize() const { return playerAnimation->getSize(); }
private:
    PlayerMeta* playerMeta;
    PlayerAnimation* playerAnimation;

    // TBD: encapsule card logic into player
    // Card_Manager* cardManager;
    // CardView* cardView;

};

#endif // PLAYER_H
