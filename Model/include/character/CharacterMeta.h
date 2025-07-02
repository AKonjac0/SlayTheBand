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
    QVector<Buff> getBuff() const
    {
        return buff;
    }

    void HP_change(int);
    void maxHP_change(int);
    void setHP(int hp)
    {
        HP = hp;
    }
    void setMaxHP(int mhp)
    {
        maxHP = mhp;
    }
    void addBuff(Buff& buff)
    {
        this->buff.push_back(std::move(buff));
    }

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
