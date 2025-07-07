#ifndef CARDREWARDPAGE_H
#define CARDREWARDPAGE_H
#include <QWidget>
#include <Card.h>
#include <QPushButton>
#include "CardReward.h"


class CardRewardPage : public QWidget{
    Q_OBJECT
public:
    CardRewardPage(QWidget *parent);
    ~CardRewardPage() = default;
    void newReward();
    CardReward *getCardReward() const { return reward; }
    QVector<Card_Meta*> getReward() const { return gen; }
    Card_Meta *getNewCard() const { return new_card; }
public slots:
    void setReward(QVector<Card_Meta*> ret_gen){
        gen = ret_gen;
    }
    void setNewCard(Card_Meta *meta) {
        new_card = meta;
        emit onNewCard();
    }
    void fireGenReward(){
        emit onGenReward();
    }
    void init();
signals:
    void onGenReward();
    void onNewCard();
private:
    QWidget *parent;
    CardReward *reward = nullptr;
    QPushButton *confirmBtn;
    QVector<Card_Meta*> gen;
    Card_Meta *new_card;
    friend class PageManager;
};

#endif //CARDREWARDPAGE_H
