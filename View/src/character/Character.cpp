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

void Character::setHP(int newHP)
{
    HP = qBound(0, newHP, maxHP);
    healthBar->setCurrentHealth(HP);
}

void Character::show_character(int x, int y, int width, int height)
{
    if (!character_avatar) {
        qWarning() << "Character avatar is null for" << name;
        return;
    }

    // 设置角色头像大小和位置
    character_avatar->setGeometry(x, y, width, height);

    character_avatar -> setMovie(illustration);
    illustration -> start();

    // 定位血条
    healthBar->setMaxHealth(maxHP);
    healthBar->setCurrentHealth(HP);
    healthBar->setFixedWidth(character_avatar->width() - 40); // 血条宽度
    healthBar->move(20, character_avatar->height() - 30); // 血条位置（底部）
    // 确保显示在最上层
    character_avatar->raise();
    character_avatar->show();
}
