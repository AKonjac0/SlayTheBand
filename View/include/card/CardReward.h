#ifndef CARDREWARD_H
#define CARDREWARD_H
#include <QWidget>
#include "Card.h"
#include "Card_Manager.h"


class CardReward{

public:
    CardReward(Card_Manager *manager, QWidget *parent = nullptr);
    ~CardReward();
private:
    QWidget *parent;
    Card_Manager *manager;
    Card *card1, *card2, *card3;
};
#endif // CARDREWARD_H
