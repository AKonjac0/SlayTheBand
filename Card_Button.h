#ifndef CARD_BUTTON_H
#define CARD_BUTTON_H
#include <QPushButton>
#include "Card_Manager.h"
#include "CardPileAnimation.h"
#include "CardPile.h"
class Card_Button{
public:
    Card_Button(Card_Manager *manager, QWidget *parent, CardPile *pile);
    ~Card_Button();
private:
    void drawcards();
    void discards();
private:
    QWidget *parent;
    QPushButton *next_round;
    Card_Manager *manager;
    CardPileAnimation *animation;
    CardPile *pile;
    bool next_round_click;
};
#endif // CARD_BUTTON_H
