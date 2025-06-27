#ifndef CARD_H
#define CARD_H
#include <QPushButton>
#include <QWidget>
#include "Card_Meta.h"
#include "mainwindow.h"

class Card : public QPushButton {
    Q_OBJECT
public:
    Card(Card_Meta *meta, MainWindow *parent);
private:
    Card_Meta *meta;
};

#endif //CARD_H
