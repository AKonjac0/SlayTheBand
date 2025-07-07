#ifndef ENEMYMETA_H
#define ENEMYMETA_H
#include "CharacterMeta.h"
#include "Buff.h"
#include <random>

class Intention{
public:
    const Buff &next(){
        int n = intent_sequence.size();
        current_intent = (current_intent + 1) % n;
        return intent_sequence[current_intent];
    }
    const Buff &get(){
        return intent_sequence[current_intent];
    }
    void add(const Buff &intent){
        intent_sequence.push_back(intent);
    }
private:
    QVector<Buff> intent_sequence;
    int current_intent;
};

class EnemyMeta : public CharacterMeta
{
public:
    EnemyMeta(QString _name, int _HP, int _maxHP);
    ~EnemyMeta() override;
    const Buff &nextIntent(){ return intention->next(); }
    const Buff &getIntent(){ return intention->get(); }
private:
    // Enemy Only
    Intention* intention;
    std::mt19937 rnd;
};

#endif // ENEMYMETA_H
