#include "PlayerMeta.h"

PlayerMeta::PlayerMeta(QString _name, int _HP, int _maxHP, int _MP): CharacterMeta(_name, _HP, _maxHP), MP(_MP), maxMP(_MP){
    qDebug() << "PlayerMeta initialized with name:" << _name << ", HP:" << _HP << ", maxHP:" << _maxHP << ", MP:" << _MP;
}

void PlayerMeta::MP_change(int amount)
{
    MP += amount;
    MP = qBound(0, MP, maxMP);
}

void PlayerMeta::setMP(int mp)
{
    MP = mp;
    MP = qBound(0, MP, maxMP); // 确保当前 MP 不超过最大 MP
}

void PlayerMeta::maxMP_change(int amount)
{
    maxMP += amount;
    maxMP = qMax(0, maxMP);
    MP = qBound(0, MP, maxMP); // 确保当前 MP 不超过最大 MP
}
void PlayerMeta::setMaxMP(int mmp)
{
    maxMP = mmp;
    maxMP = qMax(0, maxMP);
    MP = qBound(0, MP, maxMP); // 确保当前 MP 不超过最大 MP
}
