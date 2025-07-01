#ifndef CARD_BUTTON_H
#define CARD_BUTTON_H
#include "HoverButton.h"
#include "Card_Manager.h"
#include "CardPileAnimation.h"
#include "CardAnimation.h"
#include "CardPile.h"

class CountButton : public HoverButton {
public:
    CountButton(const QPointF &point, QWidget *parent = nullptr) : HoverButton("0", parent) {
        setGeometry(point.x(), point.y(), 100, 100);
        raise();
        show();
    }

    void setNumber(int num) {
        setText(QString::number(num));
    }

};


class Card_Button{
public:
    Card_Button(Card_Manager *manager, QWidget *parent, CardPile *pile);
    ~Card_Button();
    void init_combat();
private:
    void drawcards();
    void discards();
private:
    QWidget *parent;
    HoverButton *next_round;
    HoverButton *discard_pile;
    HoverButton *drawcard_pile;
    CountButton *discard_num;
    CountButton *drawcard_num;
    Card_Manager *manager;
    CardPileAnimation *animation;
    CardAnimation *next_round_button_animation;
    CardAnimation *discard_pile_animation;
    CardAnimation *drawcard_pile_animation;
    CardPile *pile;
    bool next_round_click;
};
#endif // CARD_BUTTON_H
