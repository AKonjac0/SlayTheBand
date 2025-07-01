#ifndef CARDREWARDPAGE_H
#define CARDREWARDPAGE_H
#include <QWidget>
#include <Card.h>
#include "CardReward.h"


class CardRewardPage : public QWidget{
public:
    CardRewardPage(Card_Manager *manager, QWidget *parent);
    void newReward();
private:
    QWidget *parent;
    Card_Manager *manager;
    CardReward *reward = nullptr;
};

#endif //CARDREWARDPAGE_H
