#ifndef COMBATVIEW_H
#define COMBATVIEW_H
#include <QWidget>
#include "Enemy.h"
class CombatView : public QObject{
    Q_OBJECT
public:
    CombatView(QWidget *parent = nullptr) : parent(parent) {}
    ~CombatView() {}
    void endOfRound();
    void playACard();
    void setEnemy(Enemy*);
    Enemy *getEnemy(){ return enemy; }
signals:
    void onEndOfRound();
    void onPlayACard();
    void onSetEnemy();
private:
    QWidget *parent;
    Enemy *enemy;
};
#endif // COMBATVIEW_H
