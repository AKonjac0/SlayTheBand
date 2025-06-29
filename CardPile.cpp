#include "CardPile.h"
CardPile::CardPile(Card_Manager *manager, QWidget *parent) : manager(manager), parent(parent){
    create_cards();
}

CardPile::~CardPile(){
    clear_cards();
}
void CardPile::create_cards(){
    QVector<Card_Meta *> hands = manager->get_handcard();
    for(Card_Meta *meta : hands){
        Card *card = new Card(meta, parent);
        cards.push_back(card);
    }
}
void CardPile::clear_cards(){
    for(Card *card : cards) delete card;
    cards.clear();
}
QVector<Card *> CardPile::get_cards(){
    return cards;
}
