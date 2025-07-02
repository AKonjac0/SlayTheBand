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

void CharacterMeta::maxHP_change(int amount)
{
    maxHP += amount;
    maxHP = qMax(0, maxHP);
    HP = qBound(0, HP, maxHP); // 确保当前 HP 不超过最大 HP
}

void CharacterMeta::clearBuff() { buff.clear(); }
