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
        Card *card = new Card(meta, manager, parent);
        cards.push_back(card);
        // card->getButton()->show();
    }

    for(Card *card : cards){
        HoverButton *button = card->getButton();
        QObject::connect(button, &QPushButton::clicked, parent, [button, card, this]() {
            // 应用动画效果
            if(button->Animating()) return;
            button->Animating() = true;
            card->getAnimation()->applyButtonClickAnimation(button);

            if(this->manager->get_selected() == nullptr){ // unselected, select this
                select_card(card->getMeta());
            }else if(this->manager->get_selected() == card->getMeta()){ // selected this card, then unselect it
                unselect();
            }else{ // selected other card, then select this
                select_card(card->getMeta());
            }
            if(this->manager->get_selected() == nullptr) qDebug() << "empty";
            else qDebug() << this->manager->get_selected()->getCardName();

            // 这里可以添加按钮原有的点击逻辑
            // qDebug() << "按钮被点击:" << button->text();
        });
    }

}
void CardPile::clear_cards(){
    for(Card *card : cards) delete card;
    cards.clear();
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
    Card *other_card = find_card(manager->get_selected());
    Card *card = find_card(meta);
    manager->select_card(meta);
    if(arrow) delete arrow, arrow = nullptr;

    QPointF center = card->getButton()->posOffset() + QPointF(card->getButton()->width() / 2.0, card->getButton()->height() / 2.0);
    arrow = new Arrow(center, parent);
    // qDebug() << center;
    // this->arrow->raise();
    if(other_card) other_card->getAnimation()->applyDeHighLightAnimation(other_card->getButton());
    card->getAnimation()->applyHighLightAnimation(card->getButton());
}
void CardPile::unselect(){
    Card *card = find_card(manager->get_selected());
    manager->unselect();
    if(arrow) delete arrow, arrow = nullptr;
    if(card) card->getAnimation()->applyDeHighLightAnimation(card->getButton());

}
// Card *CardPile::get_selected(){
//     find_card(manager->get_selected());
// }
