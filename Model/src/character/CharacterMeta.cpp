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

void CharacterMeta::setHP(int hp)
{
    HP = hp;
    HP = qBound(0, HP, maxHP); // 确保当前 HP 不超过最大 HP
}

void CharacterMeta::setMaxHP(int mhp)
{
    maxHP = mhp;
    maxHP = qMax(0, maxHP);
    HP = qBound(0, HP, maxHP); // 确保当前 HP 不超过最大 HP
}

void CharacterMeta::addBuff(Buff& new_buff)
{
    for (auto &i : this->buff)
    {
        if (i.getType() == new_buff.getType())
        {
            i.changeLevel(new_buff.getLevel());
            return;
        }
    }
    this->buff.push_back(std::move(new_buff));
}

void CharacterMeta::clearBuff() { buff.clear(); }
