#include "CombatView.h"

void CombatView::playACard(){
    emit onPlayACard();
}

void CombatView::endOfRound(){
    emit onEndOfRound();
}

void CombatView::setEnemy(){
    emit onSetEnemy();
}
