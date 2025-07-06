#ifndef COMBATVIEW_H
#define COMBATVIEW_H
#include <QWidget>
#include "EnemyAnimation.h"

class CombatView : public QObject{
    Q_OBJECT
public:
    CombatView(QWidget *parent = nullptr) : parent(parent) {}
    ~CombatView() {}
    void endOfRound();
    void playACard();
    void setEnemy();
    EnemyAnimation *getEnemy(){ return enemy; }
signals:
    void onEndOfRound();
    void onPlayACard();
    void onSetEnemy();
private:
    QWidget *parent;
    EnemyAnimation *enemy;
};
#endif // COMBATVIEW_H
