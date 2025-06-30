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
    setHover(false);
}
void CardPile::clear_cards(){
    for(Card *card : cards) delete card;
    cards.clear();
}
QVector<Card *> CardPile::get_cards(){
    return cards;
}

void CardPile::setAnimating(bool isAnimating){
    for(Card *card : cards){
        card->getButton()->Animating() = isAnimating;
    }
}

bool CardPile::isAnimating(){
    for(Card *card : cards){
        if(card->getButton()->Animating()) return true;
    }
    return false;
}
void CardPile::setHover(bool isHover){
    for(Card *card : cards){
        card->getButton()->Hover() = isHover;
    }
}

bool CardPile::isHover(){
    for(Card *card : cards){
        if(card->getButton()->Hover()) return true;
    }
    return false;
}
