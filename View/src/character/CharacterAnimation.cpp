#include "CharacterAnimation.h"

CharacterAnimation::~CharacterAnimation(){
    if (character_avatar != nullptr){
        delete character_avatar;
    }
    if (illustration != nullptr){
        delete illustration;
    }
}
