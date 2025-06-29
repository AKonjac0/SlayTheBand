#ifndef CARD_H
#define CARD_H
#include <QPushButton>
#include <QWidget>
#include "Card_Meta.h"
#include "CardAnimation.h"
class Card{
public:
    Card(Card_Meta *meta, QWidget *parent);
    ~Card();
    QPushButton* getButton() const;
    Card_Meta* getMeta() const;
private:
    Card_Meta *meta;
    QPushButton *button;
    QWidget *parent;
    CardAnimation *animation;
};

#endif //CARD_H
