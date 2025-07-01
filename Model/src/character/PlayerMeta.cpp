#include "PlayerMeta.h"

PlayerMeta::PlayerMeta(QString _name, int _HP, int _maxHP, int _MP): CharacterMeta(_name, _HP, _maxHP), MP(_MP), maxMP(_MP){
    qDebug() << "PlayerMeta initialized with name:" << _name << ", HP:" << _HP << ", maxHP:" << _maxHP << ", MP:" << _MP;
}

void PlayerMeta::MP_change(int amount)
{
    MP += amount;
    MP = qBound(0, MP, maxMP);
}
