#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include "Card_Meta.h"
#include "CardAnimation.h"
#include "HoverButton.h"

class Card{
public:
    Card(Card_Meta *meta, QWidget *parent, bool isHover = true);
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
};

#endif //CARD_H
