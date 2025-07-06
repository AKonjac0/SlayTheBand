#include "CardView.h"

CardView::CardView(QWidget *parent) : parent(parent){
    card_pile = new CardPile(parent);
    card_button = new Card_Button(parent, card_pile);
}



CardView::~CardView(){
    delete card_pile;
    delete card_button;
}

Card_Button *CardView::getButton() const{ return card_button; }

CardPile *CardView::getCardPile() const { return card_pile; }
