#include "Buff.h"

Buff::Buff(BuffType type, int level, bool isAll) : type(type), level(level), isAll(isAll) {}

BuffType Buff::getType() { return this->type; }

void Buff::setType(BuffType buff) { this->type = buff; }

int Buff::getLevel() { return this->level; }

bool Buff::getIsAll() { return this->isAll; }

bool Buff::changeLevel(int delta) {
    int temp = level + delta;
    if (temp <= 0) return false;
    this->level += delta;
    return true;
}
