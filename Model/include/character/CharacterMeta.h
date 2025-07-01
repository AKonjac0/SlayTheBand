#ifndef CHARACTERMETA_H
#define CHARACTERMETA_H

#include <QString>
#include <QWidget>
#include "Buff.h"
#include "Defs.h"
// #include "Intension.h"


class CharacterMeta
{
public:
    virtual ~CharacterMeta() = default;

    CharacterMeta(QString _name, int _HP, int _maxHP);

    int getHP() const
    {
        return HP;
    }
    QString getname() const
    {
        return name;
    }
    int getmaxHP() const
    {
        return maxHP;
    }
    QVector<Buff *> *getBuff() const
    {
        return buff;
    }

    void HP_change(int);

private:

    // shared attributes
    QString name;
    int HP;
    int maxHP;
    QVector<Buff *> *buff = nullptr;

    // Enemy Only
    // Intention* intention; // TBD: Intention is not implemented yet

};


#endif // CHARACTERMETA_H
