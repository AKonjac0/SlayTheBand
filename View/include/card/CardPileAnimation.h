#ifndef CARDPILEANIMATION_H
#define CARDPILEANIMATION_H
// #include "Card_Manager.h"
#include "Card.h"


class CardPileAnimation{

public:
    // CardPileAnimation(Card_Manager *manager, QWidget *parent);
    CardPileAnimation(QWidget *parent);
    ~CardPileAnimation() = default;

    QAbstractAnimation *applyDisCardAnimation(QVector<Card *> cards);
    QAbstractAnimation *applyDrawCardAnimation(QVector<Card *> cards);
private:
    QWidget *parent;
    // Card_Manager *manager;
};
#endif // CARDPILEANIMATION_H
