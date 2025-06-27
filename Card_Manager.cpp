#include "Card_Manager.h"
#include <QRandomGenerator>
#include <QString>
#include <algorithm>
#include <random>
#include <QPushButton>

Card_Manager::Card_Manager(MainWindow* parent) : parent(parent)
{
    // int cardNum = QRandomGenerator::global()->bounded(10);
    for (int i = 0; i < 5; i++) {
        total_cards.push_back(new_strike());
    }
    for (int i = 0; i < 4; i++) {
        total_cards.push_back(new_defend());
    }
    total_cards.push_back(new_bash());

    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(total_cards.begin(), total_cards.end(), rng);
}

Card_Manager::~Card_Manager() {
    for(auto &i : total_cards) {
        delete i;
    }
    for (auto &i : showed_cards) {
        delete i;
    }
}

void Card_Manager::show_cards() {
    for(int i = 0; i < 5; ++i){
        // Card *card = new Card(total_cards[i], parent);
        // showed_cards.push_back(card);
        //TODO
        QPushButton *card = new QPushButton("card", parent);
        card->setGeometry(50 + 320 * i, 50, 310, 410);

        QString cardPic = "QPushButton{border-image: url(:image/images/" + total_cards[i] -> get_card_name() + ".png);}";

        card->setStyleSheet(cardPic);
    }
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

Card_Meta *Card_Manager::new_second_wind() {
    return new Card_Meta("second_wind", skill, 1, 0, Defence, 5);
}

Card_Meta *Card_Manager::new_power_through() {
    return new Card_Meta("power_through", skill, 1, 0, Defence, 15);
}
