#ifndef COMBAT_H
#define COMBAT_H
#include <QObject>
#include "Card_Meta.h"
#include "Card_Manager.h"
#include "Player.h"
#include "Enemy.h"
#include "Buff.h"
#include "RoleManager.h"

class Combat : public QObject
{
    Q_OBJECT
public:
    Combat(RoleManager *role);
    ~Combat() = default;
    // void setCard(Card_Meta *card);
    void setEnemy();
    void setPlayer();
    bool playACard();
    void endOfRound();
    void new_combat();
    Card_Manager *get_card_manager();
    Card_Meta *get_played();

signals:
    void onPlayed();
private:
    void applyBuff(Buff &buff);
    bool check();
    Card_Manager *card_manager;
    Card_Meta *played;
    EnemyMeta *enemy;
    RoleManager *role;
};
#endif //COMBAT_H
