#ifndef CARDVIEW_H
#define CARDVIEW_H
#include "Card_Manager.h"
#include "Card_Button.h"
#include "CardPile.h"
#include "Card.h"

class CardView{
public:
    CardView(Card_Manager *manager, QWidget *parent);
    ~CardView();

private:
    void create_cards();
    void clear_cards();
private:
    Card_Manager *manager;
    QWidget *parent;

    Card_Button *card_button;
    CardPile *card_pile;

    QVector<Card *> cards;
};
#endif // CARDVIEW_H
