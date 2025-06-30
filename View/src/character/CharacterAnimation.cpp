#include "CharacterAnimation.h"
#include "Defs.h"

CharacterAnimation::CharacterAnimation(QPair<Player*, Enemy*>* _combatants): combatants(_combatants){}

CharacterAnimation::~CharacterAnimation(){
    delete combatants;
}

void CharacterAnimation::show(){
    // 轴对称
    combatants->first->show_character(
        PLAYER_POSITION_X,
        SCREEN_HEIGHT-PLAYER_POSITION_Y-combatants->first->getSize().height(),
        combatants->first->getSize().width(),
        combatants->first->getSize().height()
    );
    combatants->second->show_character(
        SCREEN_WIDTH-PLAYER_POSITION_X-combatants->second->getSize().width(),
        SCREEN_HEIGHT-PLAYER_POSITION_Y-combatants->second->getSize().height(),
        combatants->second->getSize().width(),
        combatants->second->getSize().height()
    );
}
