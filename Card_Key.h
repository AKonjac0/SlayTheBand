#ifndef CARD_KEY_H
#define CARD_KEY_H
#include <QWidget>
#include "CardController.h"
class Card_Key{
public:
    Card_Key(CardController *control, QWidget *parent);
    ~Card_Key();
private:
    CardController *control;
    QWidget *parent;
};
#endif // CARD_KEY_H
