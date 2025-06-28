#ifndef CARD_MANAGER_H
#define CARD_MANAGER_H

#include "CardController.h"
#include "Card_Button.h"
#include "Card_Key.h"


class Card_Manager{
public:
    Card_Manager(QWidget* parent);
    ~Card_Manager();

private:
    CardController *control;
    Card_Button *card_button;
    Card_Key *card_key;
private:
    QWidget *parent;
};

#endif // CARD_MANAGER_H
