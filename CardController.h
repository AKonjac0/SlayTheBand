#ifndef CARD_CONTROLLER_H
#define CARD_CONTROLLER_H


#include <QVector>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QGraphicsOpacityEffect>
#include <QTimer>
#include <QEventLoop>
#include <algorithm>
#include <random>
#include "Card.h"
#include "Card_Meta.h"

class CardController{
public:
    CardController(QWidget *parent);
    ~CardController();
    void drawcard();
    void discard();
    QVector<Card_Meta *> get_drawcard_pile() const;
    QVector<Card_Meta *> get_discard_pile() const;
    QVector<Card *> get_handcard() const;
public slots:
    void applyDrawCardAnimation();
    void applyDisCardAnimation();
private:


    void shuffle(QVector<Card_Meta *>&);
    void transfer(QVector<Card_Meta *>&, QVector<Card_Meta *>&);
    Card_Meta *new_strike();
    Card_Meta *new_defend();
    Card_Meta *new_bash();

private:
    int drawcard_num;
    QWidget *parent;
    QVector<Card_Meta *> drawcard_pile;
    QVector<Card_Meta *> discard_pile;
    QVector<Card *> handcard;
};

#endif // CARD_CONTROLLER_H
