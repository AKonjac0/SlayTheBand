#ifndef CARD_H
#define CARD_H
#include <QPushButton>
#include <QWidget>
#include <QObject>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QDebug>
#include <QRandomGenerator>
#include <QTimer>
#include <QHBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QGraphicsOpacityEffect>
#include "Card_Meta.h"

class Card{
    // Q_OBJECT
public:
    // Card(Card_Meta *meta, QPushButton *button);
    Card(Card_Meta *meta, QWidget *parent);
    ~Card();
    QPushButton* getButton() const;
    Card_Meta* getMeta() const;
private:
    Card_Meta *meta;
    QPushButton *button;
    QWidget *parent;
    void applyButtonAnimation();
};

#endif //CARD_H
