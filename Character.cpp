#include "Character.h"
#include <QDebug>

Character::Character(QString _name, int _HP, MainWindow* _parent)
    : name(_name), HP(_HP), parent(_parent)
{
    // 创建角色头像标签，并设置父对象为主窗口
    character_avatar = new QLabel(parent);
    character_avatar->setObjectName("character_avatar_" + name); // 设置唯一对象名
}

Character::~Character()
{
    if (character_avatar) {
        delete character_avatar;
        character_avatar = nullptr;
    }
}

void Character::show_character(int x, int y, int width, int height)
{
    if (!character_avatar) {
        qWarning() << "Character avatar is null for" << name;
        return;
    }


    character_avatar->setGeometry(x, y, width, height);

    QString characterPic = "QLabel { border-image: url(:image/images/" + this->getname() + ".png); }";
    character_avatar->setStyleSheet(characterPic);
    character_avatar->raise();
    character_avatar->show();

    // 5. 调试信息
    qDebug() << "Displaying character:" << name
             << "| Position:" << character_avatar->geometry()
             << "| Parent size:" << parent->size()
             << "| Image path: :image/images/" + name + ".png";
}
