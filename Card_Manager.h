#ifndef CARD_MANAGER_H
#define CARD_MANAGER_H
#include <QVector>
#include <QString>
#include <QWidget>
#include "Card.h"
#include "Card_Meta.h"

class Card_Manager{
public:
    Card_Manager(QWidget* parent);
    ~Card_Manager();
    void drawcard();
    void discard();
    QVector<Card_Meta *> get_drawcard_pile() const;
    QVector<Card_Meta *> get_discard_pile() const;
    QVector<Card *> get_handcard() const;
private:
    QVector<Card_Meta *> drawcard_pile;
    QVector<Card_Meta *> discard_pile;
    QVector<Card *> handcard;
    int drawcard_num;
    void shuffle(QVector<Card_Meta *>&);
    void transfer(QVector<Card_Meta *>&, QVector<Card_Meta *>&);

    QWidget *parent;
    void init();
    Card_Meta *new_strike();
    Card_Meta *new_defend();
    Card_Meta *new_bash();
    // Card_Meta *new_second_wind();
    // Card_Meta *new_power_through();
};

#endif // CARD_MANAGER_H
