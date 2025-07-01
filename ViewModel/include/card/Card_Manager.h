#ifndef CARD_MANAGER_H
#define CARD_MANAGER_H

#include "CardController.h"




class Card_Manager{
public:
    Card_Manager(QWidget* parent);
    ~Card_Manager();
    void drawcard();
    void discard();
    QVector<Card_Meta *> get_drawcard_pile() const;
    QVector<Card_Meta *> get_discard_pile() const;
    QVector<Card_Meta *> get_handcard() const;
    void select_card(Card_Meta *meta);
    void unselect();
    Card_Meta *get_selected() const;
private:
    CardController *control;

private:
    QWidget *parent;
};

#endif // CARD_MANAGER_H
