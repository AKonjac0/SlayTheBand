#include "CharacterMeta.h"

CharacterMeta::CharacterMeta(QString _name, int _HP, int _maxHP)
    : name(_name), HP(_HP), maxHP(_maxHP)
{
    // TBD: get buff
}

void CharacterMeta::HP_change(int amount)
{
    HP += amount;
    HP = qBound(0, HP, maxHP);
}
