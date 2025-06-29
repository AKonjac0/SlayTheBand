#include "Character.h"
#include <QDebug>
#include <QTimer>

Character::Character(QString _name, int _HP, MainWindow* _parent)
    : name(_name), HP(_HP), maxHP(_HP), parent(_parent)
{
    // 创建角色头像标签
    character_avatar = new QLabel(parent);
    character_avatar->setObjectName("character_avatar_" + name);

    // 创建血条控件
    healthBar = new HealthBar(character_avatar);
}

Character::~Character()
{
    // 清理资源
    if (character_avatar) {
        delete character_avatar;
    }
    // healthBar是character_avatar的子控件，会自动删除
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

    // 设置角色头像大小
    character_avatar->setFixedSize(310, 410);

    // 设置角色图片
    QString imagePath = ":image/images/" + this->getname() + ".png";
    QPixmap pixmap(imagePath);

    if (pixmap.isNull()) {
        qWarning() << "Failed to load character image:" << imagePath;
        character_avatar->setStyleSheet("background-color: #2c3e50; border: 2px solid #7f8c8d;");
        character_avatar->setAlignment(Qt::AlignCenter);
        character_avatar->setText("Image not found:\n" + this->getname());
    } else {
        QString characterPic = "QLabel { border-image: url(" + imagePath + "); }";
        character_avatar->setStyleSheet(characterPic);
    }

    // 定位血条
    healthBar->setMaxHealth(maxHP);
    healthBar->setCurrentHealth(HP);
    healthBar->setFixedWidth(character_avatar->width() - 40); // 血条宽度
    healthBar->move(20, character_avatar->height() - 30); // 血条位置（底部）
    // 确保显示在最上层
    character_avatar->raise();
    character_avatar->show();

    // 调试信息
    qDebug() << "Displaying character:" << name
             << "| Position:" << character_avatar->geometry()
             << "| Parent size:" << parent->size()
             << "| Image path:" << imagePath;
}
