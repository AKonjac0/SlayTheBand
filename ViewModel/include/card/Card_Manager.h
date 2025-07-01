#ifndef CARD_MANAGER_H
#define CARD_MANAGER_H

#include "CardController.h"
#include "CardGenerator.h"



class Card_Manager{
public:
    Card_Manager(QWidget* parent);
    ~Card_Manager();
    void drawcard();
    void discard();
    QVector<Card_Meta *> get_drawcard_pile() const;
    QVector<Card_Meta *> get_discard_pile() const;
    QVector<Card_Meta *> get_handcard() const;
    QVector<Card_Meta *> get_card_deck() const;
    QVector<Card_Meta *> gen(int num) const;
    void new_card(Card_Meta *meta);
    void new_combat();
    void select_card(Card_Meta *meta);
    void unselect();
    Card_Meta *get_selected() const;
private:
    CardController *control;
    CardGenerator *generator;

private:
    QWidget *parent;
};

#endif // CARD_MANAGER_H
