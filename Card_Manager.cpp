#include "Card_Manager.h"
#include <QString>


Card_Manager::Card_Manager(QWidget* parent) : parent(parent)
{

    control = new CardController(parent);
    card_button = new Card_Button(control, parent);
    card_key = new Card_Key(control, parent);
}


Card_Manager::~Card_Manager() {
    delete control;
    delete card_button;
    delete card_key;
}
