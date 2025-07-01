#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include "Card_Meta.h"
#include "Card_Manager.h"
#include "CardAnimation.h"
#include "HoverButton.h"

class Card{
public:
    Card(Card_Meta *meta, Card_Manager *manager, QWidget *parent, bool isHover = true);
    Card(const Card &c);
    ~Card();
    HoverButton* getButton() const;
    Card_Meta* getMeta() const;
    CardAnimation *getAnimation() const;
private:
    Card_Meta *meta;
    HoverButton *button;
    QWidget *parent;
    CardAnimation *animation;
    Card_Manager *manager;
};

#endif //CARD_H
