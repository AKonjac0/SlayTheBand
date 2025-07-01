#include "Card_Meta.h"

Card_Meta::Card_Meta(QString card_name, CardType card_type, int energy_consume, int hurt, BuffType buff_type, int buff_level)
    : card_name(card_name), card_type(card_type), energy_consume(energy_consume), hurt(hurt), buff(new Buff(buff_type, buff_level)){}

QString Card_Meta::getCardName() { return this->card_name; }

CardType Card_Meta::getCardType() { return this->card_type; }

int Card_Meta::getEnergyConsumption(){ return energy_consume; }
int Card_Meta::getHurt(){ return hurt; }
Buff *Card_Meta::getBuff(){ return buff; }

Card_Meta::Card_Meta(const Card_Meta &other){
    card_name = other.card_name;
    card_type = other.card_type;
    energy_consume = other.energy_consume;
    hurt = other.hurt;
    buff = new Buff(*other.buff);
}
Card_Meta::~Card_Meta(){
    delete buff;
}
