#ifndef CARD_BUTTON_H
#define CARD_BUTTON_H
#include "HoverButton.h"
#include "CardPileAnimation.h"
#include "CardAnimation.h"
#include "CardPile.h"
#include "Card_Meta.h"

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


class Card_Button : public QObject{
    Q_OBJECT
public:
    Card_Button(QWidget *parent, CardPile *pile);// Card_Manager *manager,

    ~Card_Button();
    void init_combat();
    HoverButton *get_next_round_button() { return next_round; }
    bool get_clickable();
public slots:
    void set_drawcard_pile(QVector<Card_Meta *> ret){
        drawcard_pile = ret;
    }

    void set_discard_pile(QVector<Card_Meta *> ret){
        discard_pile = ret;
    }
    // QAbstractAnimation * drawcards_finish();
private:
    QAbstractAnimation * drawcards();
    QAbstractAnimation * discards();

signals:
    void finish_round();
    void onDrawCardStart();
    void onDisCardStart();
    void onNewCombat();
    void onGetDrawcardPile();
    void onGetDiscardPile();
private:
    QWidget *parent;
    HoverButton *next_round;
    HoverButton *discard_pile_button;
    HoverButton *drawcard_pile_button;
    CountButton *discard_num;
    CountButton *drawcard_num;
    CardPileAnimation *animation;

    QVector<Card_Meta *> drawcard_pile;
    QVector<Card_Meta *> discard_pile;

    // Card_Manager *manager;


    CardAnimation *next_round_button_animation;
    CardAnimation *discard_pile_animation;
    CardAnimation *drawcard_pile_animation;
    CardPile *pile;
    bool next_round_click;
};
#endif // CARD_BUTTON_H
