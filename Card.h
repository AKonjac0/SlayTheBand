#ifndef CARD_H
#define CARD_H
#include <QPushButton>
#include <QWidget>
#include "Card_Meta.h"
#include "mainwindow.h"

class Card{
    // Q_OBJECT
public:
    // Card(Card_Meta *meta, QPushButton *button);
    Card(Card_Meta *meta, MainWindow *parent);
    ~Card() = default;
    QPushButton* getbutton(){
        return button;
    }
private:
    Card_Meta *meta;
    QPushButton *button;
};

#endif //CARD_H
