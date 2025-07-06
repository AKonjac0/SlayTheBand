#ifndef CARD_MANAGER_H
#define CARD_MANAGER_H

#include "CardController.h"
#include "CardGenerator.h"

class Card_Manager : public QObject{
    Q_OBJECT
public:
    Card_Manager();
    ~Card_Manager();
    QVector<Card_Meta *> get_drawcard_pile() const;
    QVector<Card_Meta *> get_discard_pile() const;
    QVector<Card_Meta *> get_handcard() const;
    QVector<Card_Meta *> get_card_deck() const;
    QVector<Card_Meta *> gen(int num) const;
    Card_Meta *get_selected() const;
public slots:
    void drawcard();
    void discard();
    void new_card(Card_Meta *meta);
    void new_combat();
    void select_card(Card_Meta *meta);
    void playACard(Card_Meta *meta);

signals:
    void onSelectedChanged();
    void onHandsChanged();
    void onPlayed();

private:
    CardController *control;
    CardGenerator *generator;

};

#endif // CARD_MANAGER_H
