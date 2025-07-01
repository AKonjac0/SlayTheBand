#ifndef CARD_META_H
#define CARD_META_H
#include "Buff.h"
#include <QString>

enum CardType {attack, skill, power};

class Card_Meta{
public:
    Card_Meta(QString card_name, CardType card_type, int energy_consume, int hurt, BuffType buff_type, int buff_level);
    Card_Meta(const Card_Meta &);
    ~Card_Meta();
    QString getCardName();
    CardType getCardType();
    int getEnergyConsumption();
    int getHurt();
    Buff *getBuff();
private:
    QString card_name;
    CardType card_type;
    int energy_consume;
    int hurt;
    Buff *buff;
};

#endif // CARD_META_H
