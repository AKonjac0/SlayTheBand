#include "Card_Meta.h"

Card_Meta::Card_Meta(QString card_name, CardType card_type, int energy_consume)
    : card_name(card_name), card_type(card_type), energy_consume(energy_consume){
    buff.clear();
}

QString Card_Meta::getCardName() { return this->card_name; }

CardType Card_Meta::getCardType() { return this->card_type; }

int Card_Meta::getEnergyConsumption(){ return energy_consume; }
QVector<Buff> Card_Meta::getBuff() const { return buff; }


void Card_Meta::addBuff(BuffType type, int level, bool isAll){
    Buff new_buff = Buff(type, level, isAll);
    buff.push_back(new_buff);
}

Card_Meta::~Card_Meta(){}

Card_Meta::Card_Meta(const Card_Meta &other){
    card_name = other.card_name;
    card_type = other.card_type;
    energy_consume = other.energy_consume;
    buff = other.buff; // QVector copy ctor
}
