#ifndef CARD_CONTROLLER_H
#define CARD_CONTROLLER_H
#include <QVector>
#include <random>

#include "Card_Meta.h"

class CardController{
public:
    CardController();
    ~CardController();
    void drawcard();
    void discard();
    void new_combat();
    QVector<Card_Meta *> get_drawcard_pile() const;
    QVector<Card_Meta *> get_discard_pile() const;
    QVector<Card_Meta *> get_handcard() const;
    QVector<Card_Meta *> get_card_deck() const;
    void select_card(Card_Meta *meta);
    void new_card(Card_Meta *meta);
    void unselect();
    Card_Meta *get_selected() const;
    void playACard(Card_Meta *meta);
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
    Card_Meta *selected = nullptr;
    QVector<Card_Meta *> card_deck;
    QVector<Card_Meta *> drawcard_pile;
    QVector<Card_Meta *> discard_pile;
    QVector<Card_Meta *> handcard;
};

#endif // CARD_CONTROLLER_H
