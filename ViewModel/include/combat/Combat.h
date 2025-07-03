#ifndef COMBAT_H
#define COMBAT_H
#include <QObject>
#include "Card_Meta.h"
#include "CardView.h"
#include "Player.h"
#include "Enemy.h"
#include "Buff.h"

class Combat : public QObject
{
public:
    Combat(QObject *parent, CardView *cardView, Player *player);
    ~Combat() = default;
    // void setCard(Card_Meta *card);
    void setEnemy(Enemy *enemy);
    bool playACard();
    void endOfRound();
    void new_combat();
private:
    void applyBuff(Buff &buff);
    bool check();
    CardView *cardView;
    Card_Meta *cardMeta;
    Enemy *enemy;
    Player *player;
};
#endif //COMBAT_H
