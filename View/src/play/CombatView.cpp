#include "CombatView.h"

void CombatView::playACard(){
    emit onPlayACard();
}

void CombatView::endOfRound(){
    emit onEndOfRound();
}

void CombatView::setEnemy(Enemy *ret_enemy){
    if(enemy != ret_enemy){
        enemy = ret_enemy;
        emit onSetEnemy();
    }
}
