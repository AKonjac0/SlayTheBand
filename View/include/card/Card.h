#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include "Card_Meta.h"
#include "CardAnimation.h"
#include "HoverButton.h"
class Card{
public:
    Card(Card_Meta *meta, QWidget *parent);
    ~Card();
    HoverButton* getButton() const;
    Card_Meta* getMeta() const;
private:
    Card_Meta *meta;
    HoverButton *button;
    QWidget *parent;
    CardAnimation *animation;
};

#endif //CARD_H
