#include "CardView.h"

CardView::CardView(Card_Manager *manager, QWidget *parent) : manager(manager), parent(parent){
    card_pile = new CardPile(parent);
    card_button = new Card_Button(manager, parent, card_pile);
}



CardView::~CardView(){
    delete card_pile;
    delete card_button;
}

Card_Button *CardView::getButton() const{ return card_button; }

Card_Manager *CardView::getManager() const { return manager; }

CardPile *CardView::getCardPile() const { return card_pile; }
