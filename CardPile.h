#ifndef CARDPILE_H
#define CARDPILE_H

#include "Card.h"
#include "Card_Manager.h"
class CardPile{
public:
    CardPile(Card_Manager *manager, QWidget *parent);
    ~CardPile();
    void create_cards();
    void clear_cards();
    QVector<Card *> get_cards();

private:
    Card_Manager *manager;
    QWidget *parent;
    QVector<Card *> cards;
};
#endif // CARDPILE_H
