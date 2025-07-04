#include "CardPile.h"

CardPile::CardPile(QWidget *parent) : parent(parent){
    create_cards();
}

CardPile::~CardPile(){
    clear_cards();
}

void CardPile::set_selected(Card_Meta *ret_selected){
    if(selected != ret_selected){
        selected = ret_selected;
        emit onSelectedChanged();
    }
}

void CardPile::set_hands(QVector<Card_Meta *> ret_hands){
    if(hands != ret_hands){
        hands = ret_hands;
        emit onHandsChanged();
    }
}


void CardPile::create_cards(){
    // get_hands
    for(Card_Meta *meta : hands){
        Card *card = new Card(meta, parent);
        cards.push_back(card);
    }

    for(Card *card : cards){
        HoverButton *button = card->getButton();
        QObject::connect(button, &QPushButton::clicked, parent, [button, card, this]() {
            // 应用动画效果
            if(selected == nullptr){ // unselected, select this
                if(button->Animating()) return;
                button->Animating() = true;
                QAbstractAnimation *anim = card->getAnimation()->applyButtonClickAnimation(button);
                card->getButton()->Hover() = false;
                select_card(card->getMeta());
                QObject::connect(anim, &QAbstractAnimation::finished, [button]() {
                    button->Animating() = false;
                });
            }else if(selected == card->getMeta()){ // selected this card, then unselect it
                if(button->Animating()) return;
                unselect();
                card->getButton()->Hover() = true;
            }
            if(selected == nullptr) qDebug() << "empty";
            else qDebug() << selected->getCardName();
        });
    }

}
void CardPile::clear_cards(){
    for(Card *card : cards) delete card;
    cards.clear();
    // hands.clear();
}
QVector<Card *> CardPile::get_cards(){
    return cards;
}
Card *CardPile::find_card(Card_Meta *meta){
    if(meta == nullptr){
        qDebug() << "[warning]: finding nullptr in CardPile::find_card()";
        return nullptr;
    }
    for(Card *card : cards){
        if(card->getMeta() == meta) return card;
    }
    return nullptr;
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

void CardPile::select_card(Card_Meta *meta){
    Card *card = find_card(meta);
    // manager->select_card(meta);
    // emit onSelectCard(meta);
    set_selected(meta);
    if(arrow) delete arrow, arrow = nullptr;
    QPointF center = card->getButton()->pos() + QPointF(card->getButton()->width() / 2.0, card->getButton()->height() / 2.0);
    arrow = new Arrow(center, parent);
    card->getAnimation()->applyHighLightAnimation(card->getButton());
}
void CardPile::unselect(){
    Card *card = find_card(selected);
    // manager->unselect();
    // emit onUnselect();
    set_selected(nullptr);
    if(arrow) delete arrow, arrow = nullptr;
    QAbstractAnimation *anim = nullptr;
    if(card) anim = card->getAnimation()->applyDeHighLightAnimation(card->getButton());
}

void CardPile::playACard(Card_Meta *meta) {
    played = meta;
    unselect();
    Card *toDel = nullptr;
    // QVector<Card_Meta*> new_hands;
    for (auto i = cards.begin(); i != cards.end(); i++) {
        if ((*i)->getMeta() == meta) {
            toDel = *i;
            cards.erase(i);
            break;
        }else{
            // new_hands.push_back((*i)->getMeta());
        }
    }
    if (toDel) {
        delete toDel;
    }
    // set_hands(new_hands);
    qDebug() << "onplayed";
    emit onPlayed();
}
