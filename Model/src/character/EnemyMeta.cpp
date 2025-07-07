#include "EnemyMeta.h"

EnemyMeta::EnemyMeta(QString _name, int _HP, int _maxHP)
    : CharacterMeta(_name, _HP, _maxHP), rnd(std::random_device{}()), intention(new Intention()) {
    int k = rnd() % 3 + 3;
    int lastLevel = 0;
    while(k--){
        int type = rnd() % 10;
        Buff buff = Buff(No, 0);
        if(type >= 10) buff.setType(Block);
        else buff.setType(Damage);
        int mod = std::max(28 - lastLevel, 0) + 1;
        int level = rnd() % mod + 3;
        buff.changeLevel(level);
        intention->add(buff);
        lastLevel = level;
    }
}

EnemyMeta::~EnemyMeta(){
    delete intention;
}
