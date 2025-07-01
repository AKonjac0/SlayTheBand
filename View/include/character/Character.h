#ifndef CHARACTER_H
#define CHARACTER_H

#include "QWidget"
#include <QLabel>
#include <QString>
#include <QMovie>
#include <QVector>
#include "Healthbar.h"
#include "Card_Meta.h"
#include "Buff.h"

class Character
{
public:
    Character(QString _name, int _HP, QWidget* _parent);
    virtual ~Character();

    // basic attribute getters
    int getHP() const { return HP; }
    QString getname() const { return name; }
    int getmaxHP() const { return maxHP;}
    void HP_change(int amount);
    virtual void show_character(int, int, int, int) = 0;
    QLabel* getAvatar() const { return character_avatar; }
    HealthBar* getHealthBar() const { return healthBar; }
    QMovie* getIllustration() const { return illustration; }
    QSize getSize() const { return size; }

    // ready to play cards
    void AffectedBy(Card_Meta* cardMeta);
    void PlayCard(Card_Meta* cardUsed, Character* target);

private:
    QWidget* parent;

    // Model
    int HP;
    int maxHP;
    QString name;
    QVector<Buff*> buff;

    // View
    QLabel* character_avatar;
    QMovie* illustration;
    HealthBar* healthBar;
    // Literally size of avatar
    QSize size;

};

#endif // CHARACTER_H
