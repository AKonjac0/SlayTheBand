#ifndef CARD_BUTTON_H
#define CARD_BUTTON_H
#include <QPushButton>
#include "CardController.h"
class Card_Button{
public:
    Card_Button(CardController *control, QWidget *parent);
    ~Card_Button();
private:
    QWidget *parent;
    QPushButton *next_round;
    CardController *control;
};
#endif // CARD_BUTTON_H
