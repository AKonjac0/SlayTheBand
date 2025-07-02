#ifndef CARDGENERATOR_H
#define CARDGENERATOR_H
#include "Card_Meta.h"
#include <QWidget>
#include <random>
class CardGenerator{
public:
    CardGenerator(QWidget *parent = nullptr);
    ~CardGenerator();
    QVector<Card_Meta *> gen(int num);
private:
    QWidget *parent;
    QVector<Card_Meta *> full_card_deck;
    QVector<Card_Meta *> drawcard_pile;
    void new_gen();
    std::mt19937 rng;
};

#endif // CARDGENERATOR_H
