#include "Card_Manager.h"
#include <QString>
#include <QDebug>

// ViewModel
Card_Manager::Card_Manager()
{
    control = new CardController();
    generator = new CardGenerator();
}


Card_Manager::~Card_Manager() {
    delete control;
    delete generator;
}

void Card_Manager::drawcard(){
    control->drawcard();
    emit onHandsChanged();
}

void Card_Manager::discard(){
    control->discard();
    emit onHandsChanged();
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
    if(control->get_selected() != meta){
        control->select_card(meta);
        emit onSelectedChanged();
    }
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
    emit onSelectedChanged();
    emit onHandsChanged();
}

void Card_Manager::playACard(Card_Meta *meta) {
    // unselect();
    qDebug() << "total cards:" << control->get_discard_pile().size() << " " << control->get_drawcard_pile().size() << " " << control->get_handcard().size();
    select_card(nullptr);
    control->playACard(meta);
    emit onSelectedChanged();
    emit onHandsChanged();
    // emit onPlayed();

}
