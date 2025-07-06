#ifndef CARDVIEW_H
#define CARDVIEW_H
#include "Card_Button.h"
#include "CardPile.h"


class CardView{
public:
    CardView(QWidget *parent);
    ~CardView();
    Card_Button *getButton() const;
    CardPile *getCardPile() const;
private:
    QWidget *parent;

    Card_Button *card_button;
    CardPile *card_pile;
    // Arrow *arrow;
};
#endif // CARDVIEW_H
