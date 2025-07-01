#include "CardGenerator.h"
#include <algorithm>



CardGenerator::CardGenerator(QWidget *parent) : parent(parent), rng(std::mt19937(time(0))) {
    full_card_deck.push_back(new Card_Meta("strike", attack, 1, 6, No, 0));
    full_card_deck.push_back(new Card_Meta("defend", skill, 1, 0, No, 5));
    full_card_deck.push_back(new Card_Meta("bash", attack, 2, 8, Vulnerable, 2));
    full_card_deck.push_back(new Card_Meta("power_through", skill, 1, 0, No, 15));
    full_card_deck.push_back(new Card_Meta("second_wind", skill, 1, 0, No, 0));
    new_gen();

}
CardGenerator::~CardGenerator() {
    for (auto &i : full_card_deck) {
        delete i;
    }
}

QVector<Card_Meta*> CardGenerator::gen(int num){
    qDebug() << num << " " << full_card_deck.size();
    assert(num <= full_card_deck.size());
    if(drawcard_pile.size() < num){
        new_gen();
    }
    QVector<Card_Meta *> ret;
    while(num--) ret.push_back(drawcard_pile.back()), drawcard_pile.pop_back();
    // does drawcard_pile.back() need copy ctor?
    return ret;
}


void CardGenerator::new_gen(){
    drawcard_pile.clear();
    for(Card_Meta *meta : full_card_deck) drawcard_pile.push_back(meta);
    std::shuffle(drawcard_pile.begin(), drawcard_pile.end(), rng);
}
