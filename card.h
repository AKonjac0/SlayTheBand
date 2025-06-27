#ifndef CARD_H
#define CARD_H

#include <QRandomGenerator>
#include <vector>
#include <string>
#include <QTimer>
#include <QHBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QDebug>
#include <QPushButton>
#include "mainwindow.h"


using namespace std;


class Card{
public:
    Card(MainWindow *);
private slots:
    void applyButtonAnimation(QPushButton *button);
    void applyDrawCardAnimation(QList<QPushButton*> cards);
private:
    void setupButtonAnimations();
    MainWindow *window;
};


#endif // CARD_H
