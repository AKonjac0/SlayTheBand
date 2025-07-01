#include "Character.h"
#include <QDebug>
#include <QTimer>
#include <QRect>

Character::Character(QString _name, int _HP, QWidget* _parent)
    : name(_name), HP(_HP), maxHP(_HP), parent(_parent)
{
    // 创建角色头像标签
    character_avatar = new QLabel(parent);
    character_avatar->setObjectName("character_avatar_" + name);
    QString pic_path = ":image/images/" + _name + ".gif";
    illustration = new QMovie(pic_path);
    QImageReader reader(pic_path);
    size = reader.size();
    // 创建血条控件
    healthBar = new HealthBar(character_avatar);
}

Character::~Character()
{
    // 清理资源
    if (character_avatar) {
        delete character_avatar;
    }
    if (illustration) {
        delete illustration;
    }
}

void Character::HP_change(int amount)
{
    HP += amount;
    HP = qBound(0, HP, maxHP);
    healthBar->setCurrentHealth(HP);
}

void Character::AffectedBy(Card_Meta* cardMeta){
    switch (cardMeta->getCardType()) {
    case attack:
        HP_change(-cardMeta->getHurt());
        break;
    case skill:
        // TBD
        break;
    case power:
        // TBD
        break;
    default:
        break;
    }
}

void Character::PlayCard(Card_Meta* cardMeta, Character* target){
    // TBD
}
