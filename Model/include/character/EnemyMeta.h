#ifndef ENEMYMETA_H
#define ENEMYMETA_H
#include "CharacterMeta.h"


class EnemyMeta : public CharacterMeta
{
public:
    EnemyMeta(QString _name, int _HP, int _maxHP);
    ~EnemyMeta() override = default;

private:
    // Enemy Only
    // Intention* intention;
};

#endif // ENEMYMETA_H
