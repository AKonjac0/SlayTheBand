#ifndef CARD_META_H
#define CARD_META_H
#include "Buff.h"
#include <QString>
#include <QVector>
enum CardType {attack, skill, power};

class Card_Meta{
public:
    Card_Meta(QString card_name, CardType card_type, int energy_consume);
    Card_Meta(const Card_Meta &);
    ~Card_Meta();
    QString getCardName();
    CardType getCardType();
    int getEnergyConsumption();
    void addBuff(BuffType type, int level, bool isAll = false);
    QVector<Buff> getBuff() const;
private:
    QString card_name;
    CardType card_type;
    int energy_consume;
    QVector<Buff> buff;
};

#endif // CARD_META_H
