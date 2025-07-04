#ifndef CARDREWARD_H
#define CARDREWARD_H
#include <QWidget>
#include "Card.h"



class CardReward : public QObject{
    Q_OBJECT
public:
    CardReward(QVector<Card_Meta *> gen, QWidget *parent = nullptr);
    ~CardReward();
    // void init();


private:
    QWidget *parent;
    Card *card1, *card2, *card3;
    QVector<Card_Meta *> gen;
    friend class CardRewardPage;
};
#endif // CARDREWARD_H
