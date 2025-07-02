#include "Card.h"
#include <QObject>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QDebug>
#include <QRandomGenerator>
#include <QTimer>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QGraphicsColorizeEffect>

Card::Card(Card_Meta *meta, Card_Manager *manager, QWidget *parent, bool isHover) :meta(meta), manager(manager), parent(parent) {
    button = new HoverButton("card", parent, isHover);
    // button->move(QPoint(400, 400));
    QString cardPic = "QPushButton{border-image: url(:image/images/" + meta -> getCardName() + ".png);}";
    button->setStyleSheet(cardPic);
    // button->show();
    button->hide();
    animation = new CardAnimation(parent);
    // connect moved into CardPile
}

Card::Card(const Card &c){
    meta = c.meta;
    manager = c.manager;
    parent = c.parent;
    button = c.button;
    animation = c.animation;
}

/**
 * @brief Card::~Card
 * should not manage Card_Meta
 * Card_Meta is managed by Card_Manager in order to simplify draw card pile / discard pile logic
 * when cards are discarded, QPushButtons are deconstructed and Card_Meta are inserted into discard pile
 */
Card::~Card(){
    delete button;
    delete animation;
}

HoverButton* Card::getButton() const {
    return button;
}

Card_Meta* Card::getMeta() const {
    return meta;
}

CardAnimation *Card::getAnimation() const{
    return animation;
}

