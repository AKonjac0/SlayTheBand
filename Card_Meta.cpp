#include "Card_Meta.h"

Card_Meta::Card_Meta(QString card_name, CardType card_type, int energy_consume, int hurt, BuffType buff_type, int buff_level)
    : card_name(card_name), card_type(card_type), energy_consume(energy_consume), hurt(hurt), buff(buff_type, buff_level){}

QString Card_Meta::get_card_name() { return this->card_name; }
