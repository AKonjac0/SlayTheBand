#ifndef CARDVIEW_H
#define CARDVIEW_H
#include "Card_Manager.h"
#include "Card_Button.h"
#include "CardPile.h"


class CardView{
public:
    CardView(Card_Manager *manager, QWidget *parent);
    ~CardView();


private:
    Card_Manager *manager;
    QWidget *parent;

    Card_Button *card_button;
    CardPile *card_pile;
    // Arrow *arrow;
};
#endif // CARDVIEW_H
