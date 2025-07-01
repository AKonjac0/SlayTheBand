#ifndef CARDPILE_H
#define CARDPILE_H

#include "Card.h"
#include "Card_Manager.h"
#include "Arrow.h"
class CardPile{
public:
    CardPile(Card_Manager *manager, QWidget *parent);
    ~CardPile();
    void create_cards();
    void clear_cards();
    QVector<Card *> get_cards();
    Card *find_card(Card_Meta *meta);
    void setAnimating(bool isAnimating);
    bool isAnimating();
    void setHover(bool isHover);
    bool isHover();
    void select_card(Card_Meta *meta);
    void unselect();
private:
    Card_Manager *manager;
    QWidget *parent;
    QVector<Card *> cards;
    Arrow *arrow = nullptr;
};
#endif // CARDPILE_H
