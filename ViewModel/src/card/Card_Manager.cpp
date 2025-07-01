#include "Card_Manager.h"
#include <QString>

// ViewModel
Card_Manager::Card_Manager(QWidget* parent) : parent(parent)
{
    control = new CardController(parent);
    generator = new CardGenerator(parent);
}


Card_Manager::~Card_Manager() {
    delete control;
    delete generator;
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

void Card_Manager::select_card(Card_Meta *meta){
    control->select_card(meta);
}

void Card_Manager::unselect(){
    control->unselect();
}
Card_Meta *Card_Manager::get_selected() const {
    return control->get_selected();
}

QVector<Card_Meta *> Card_Manager::get_card_deck() const {
    return control->get_card_deck();
}
void Card_Manager::new_card(Card_Meta *meta){
    control->new_card(meta);
}
QVector<Card_Meta *> Card_Manager::gen(int num) const{
    return generator->gen(num);
}
void Card_Manager::new_combat(){
    control->new_combat();
}
