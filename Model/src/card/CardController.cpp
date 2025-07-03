#include "CardController.h"


// Model
CardController::CardController() : drawcard_num(5) {
    for (int i = 0; i < 5; i++) {
        card_deck.push_back(new_strike());
    }
    for (int i = 0; i < 4; i++) {
        card_deck.push_back(new_defend());
    }
    card_deck.push_back(new_bash());
}

void CardController::new_combat(){
    drawcard_pile.clear();
    discard_pile.clear();
    handcard.clear();
    for(Card_Meta *meta : card_deck){
        drawcard_pile.push_back(meta);
    }
    shuffle(drawcard_pile);
    // drawcard();
}
void CardController::new_card(Card_Meta *meta){
    // copy
    Card_Meta *new_meta = new Card_Meta(*meta);
    card_deck.push_back(new_meta);
}
CardController::~CardController() {
    // for(auto &i : discard_pile) {
    //     delete i;
    // }
    // for (auto &i : drawcard_pile) {
    //     delete i;
    // }
    // for (auto &i : handcard) {
    //     delete i;
    // }
    for (auto &i : card_deck) {
        delete i;
    }
}


void CardController::shuffle(QVector<Card_Meta*> &pile){
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::shuffle(pile.begin(), pile.end(), rng);
}


void CardController::transfer(QVector<Card_Meta *> &to, QVector<Card_Meta *> &from){
    if(!to.empty()) qDebug() << "[warning] transfering cards to a pile that is not empty!";
    for(auto &i : from){
        to.push_back(i);
    }
    from.clear();
}
void CardController::drawcard() {
    for(int i = 0; i < drawcard_num; ++i){
        if(drawcard_pile.empty()){
            transfer(drawcard_pile, discard_pile);
            shuffle(drawcard_pile);
            qDebug() << "牌堆被洗混";

        }
        // Card *card = new Card(drawcard_pile.back(), parent);
        handcard.push_back(drawcard_pile.back());
        drawcard_pile.pop_back();


    }
}
void CardController::discard() {
    int handcard_num = handcard.size();
    for(int i = 0; i < handcard_num; ++i){
        discard_pile.push_back(handcard.back());
        // Card *card = handcard.back();
        handcard.pop_back();
    }
}

QVector<Card_Meta *> CardController::get_drawcard_pile() const{
    return drawcard_pile;
}
QVector<Card_Meta *> CardController::get_discard_pile() const{
    return discard_pile;
}
QVector<Card_Meta *> CardController::get_handcard() const{
    return handcard;
}
QVector<Card_Meta *> CardController::get_card_deck() const{
    return card_deck;
}

Card_Meta *CardController::new_strike() {
    Card_Meta *meta = new Card_Meta("strike", attack, 1);
    meta->addBuff(BuffType::Damage, 6, false);
    return meta;
}

Card_Meta *CardController::new_defend() {
    Card_Meta *meta = new Card_Meta("defend", skill, 1);
    meta->addBuff(BuffType::Block, 5, false);
    return meta;
}

Card_Meta *CardController::new_bash() {
    Card_Meta *meta = new Card_Meta("bash", attack, 2);
    meta->addBuff(BuffType::Damage, 8, false);
    meta->addBuff(BuffType::Vulnerable, 2, false);
    return meta;
}

void CardController::unselect(){
    selected = nullptr;
}

void CardController::select_card(Card_Meta *meta){
    selected = meta;
}

Card_Meta *CardController::get_selected() const {
    return selected;
}

void CardController::playACard(Card_Meta *meta) {
    for (auto i = handcard.begin(); i != handcard.end(); ++i) {
        if (*i == meta) {
            handcard.erase(i);
            break;
        }
    }
    discard_pile.push_back(meta);
}
