#ifndef CARDREWARDPAGE_H
#define CARDREWARDPAGE_H
#include <QWidget>
#include <Card.h>
#include <QPushButton>
#include "CardReward.h"


class CardRewardPage : public QWidget{
public:
    CardRewardPage(Card_Manager *manager, QWidget *parent);
    ~CardRewardPage() = default;
    void newReward();
private:
    QWidget *parent;
    Card_Manager *manager;
    CardReward *reward = nullptr;
    QPushButton *confirmBtn;

    friend class PageManager;
};

#endif //CARDREWARDPAGE_H
