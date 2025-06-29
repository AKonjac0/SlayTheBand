#include "Card_Manager.h"
#include <QString>

// ViewModel
Card_Manager::Card_Manager(QWidget* parent) : parent(parent)
{
    control = new CardController(parent);
}


Card_Manager::~Card_Manager() {
    delete control;
}

void Card_Manager::drawcard(){
    control->drawcard();
}

void Card_Manager::discard(){
    control->discard();
}
QVector<Card_Meta *> Card_Manager::get_drawcard_pile() const{
    return control->get_drawcard_pile();
}
QVector<Card_Meta *> Card_Manager::get_discard_pile() const{
    return control->get_discard_pile();
}
QVector<Card_Meta *> Card_Manager::get_handcard() const{
    return control->get_handcard();
}
