#include "Buff.h"

Buff::Buff(BuffType type, int level, bool isAll) : type(type), level(level), isAll(isAll) {}

BuffType Buff::getType() { return this->type; }

int Buff::getLevel() { return this->level; }

bool Buff::getIsAll() { return this->isAll; }