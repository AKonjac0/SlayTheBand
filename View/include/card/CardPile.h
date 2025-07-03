#ifndef CARDPILE_H
#define CARDPILE_H

#include "Card.h"

#include "Arrow.h"


class CardPile : public QObject{
    Q_OBJECT
public:
    CardPile(QWidget *parent);
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
    void playACard(Card_Meta *meta);
public:
    Card_Meta *get_selected() const { return selected; }
    Card_Meta *get_played() const { return played; }
    QVector<Card_Meta *> get_hands() const { return hands; }

public slots:
    void set_selected(Card_Meta *ret_selected);
    void set_hands(QVector<Card_Meta *> ret_hands);

signals:
    void onSelectedChanged();
    void onHandsChanged();
    void onPlayed();

private:
    QWidget *parent;
    Card_Meta *selected;
    Card_Meta *played;
    QVector<Card *> cards;
    QVector<Card_Meta *> hands;
    Arrow *arrow = nullptr;
};
#endif // CARDPILE_H
