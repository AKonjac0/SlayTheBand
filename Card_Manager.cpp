#include "Card_Manager.h"
#include <QString>
#include <algorithm>
#include <random>

Card_Manager::Card_Manager(QWidget* parent) : parent(parent)
{
    drawcard_num = 5; // default

    for (int i = 0; i < 5; i++) {
        drawcard_pile.push_back(new_strike());
    }
    for (int i = 0; i < 4; i++) {
        drawcard_pile.push_back(new_defend());
    }
    drawcard_pile.push_back(new_bash());
    drawcard_pile.push_back(new_bash()); // 11 cards, test draw card

    shuffle(drawcard_pile);
}
void Card_Manager::shuffle(QVector<Card_Meta*> &pile){
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::shuffle(pile.begin(), pile.end(), rng);
}

Card_Manager::~Card_Manager() {
    for(auto &i : discard_pile) {
        delete i;
    }
    for (auto &i : drawcard_pile) {
        delete i;
    }
    for (auto &i : handcard) {
        delete i;
    }
}
void Card_Manager::transfer(QVector<Card_Meta *> &to, QVector<Card_Meta *> &from){
    if(!to.empty()) qDebug() << "[warning] transfering cards to a pile that is not empty!";
    for(auto &i : from){
        to.push_back(i);
    }
    from.clear();
}
void Card_Manager::drawcard() {
    for(int i = 0; i < drawcard_num; ++i){
        if(drawcard_pile.empty()){
            transfer(drawcard_pile, discard_pile);
            shuffle(drawcard_pile);
            qDebug() << "牌堆被洗混";

        }
        Card *card = new Card(drawcard_pile.back(), parent);
        handcard.push_back(card);
        drawcard_pile.pop_back();


    }
}
void Card_Manager::discard() {
    int handcard_num = handcard.size();
    for(int i = 0; i < handcard_num; ++i){
        discard_pile.push_back(handcard.back()->getMeta());
        Card *card = handcard.back();
        delete card;
        handcard.pop_back();
    }
}

QVector<Card_Meta *> Card_Manager::get_drawcard_pile() const{
    return drawcard_pile;
}
QVector<Card_Meta *> Card_Manager::get_discard_pile() const{
    return discard_pile;
}
QVector<Card *> Card_Manager::get_handcard() const{
    return handcard;
}

//TODO
Card_Meta *Card_Manager::new_strike() {
    return new Card_Meta("strike", attack, 1, 6, No, 0);

}

Card_Meta *Card_Manager::new_defend() {
    return new Card_Meta("defend", skill, 1, 0, Defence, 5);
}

Card_Meta *Card_Manager::new_bash() {
    return new Card_Meta("bash", attack, 2, 8, Vulnerability, 2);
}

// Card_Meta *Card_Manager::new_second_wind() {
//     return new Card_Meta("second_wind", skill, 1, 0, Defence, 5);
// }

// Card_Meta *Card_Manager::new_power_through() {
//     return new Card_Meta("power_through", skill, 1, 0, Defence, 15);
// }
