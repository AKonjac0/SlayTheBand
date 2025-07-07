#ifndef CHARACTERMETA_H
#define CHARACTERMETA_H

#include <QString>
#include <QVector>
#include "Buff.h"
#include "Defs.h"


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
    QVector<Buff> getBuff() const
    {
        return buff;
    }

    void HP_change(int);
    void maxHP_change(int);
    void setHP(int hp);
    void setMaxHP(int mhp);
    void addBuff(Buff& new_buff);
    void clearBuff();
    void setName(QString name) { this->name = name; }

private:

    // shared attributes
    QString name;
    int HP;
    int maxHP;
    QVector<Buff> buff;

    // Enemy Only
    // Intention* intention; // TBD: Intention is not implemented yet

};


#endif // CHARACTERMETA_H
