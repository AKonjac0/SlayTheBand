#ifndef CARD_MANAGER_H
#define CARD_MANAGER_H
#include <QVector>
#include <QString>
#include <QWidget>
#include "Card.h"
#include "Card_Meta.h"
#include "mainwindow.h"

class Card_Manager{
public:
    Card_Manager(MainWindow* parent);
    ~Card_Manager();
    void show_cards();
private:
    QVector<Card_Meta *> total_cards;
    QVector<Card *> showed_cards;
    MainWindow *parent;
    void init();
    Card_Meta *new_strike();
    Card_Meta *new_defend();
    Card_Meta *new_bash();
    Card_Meta *new_second_wind();
    Card_Meta *new_power_through();
};

#endif // CARD_MANAGER_H
