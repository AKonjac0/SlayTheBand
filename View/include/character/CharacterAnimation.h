#ifndef CHARACTERANIMATION_H
#define CHARACTERANIMATION_H

#include <QWidget>
#include <QLabel>
#include <QMovie>
#include <QSize>
#include <QPushButton>
#include "Healthbar.h"


class CharacterAnimation {
public:
    template<typename MetaType>
    CharacterAnimation(MetaType*, QWidget*);
    virtual ~CharacterAnimation() = 0;

    QLabel* getAvatar() const { return character_avatar; }
    QPushButton* getButton() const { return button; }
    HealthBar* getHealthBar() const { return healthBar; }
    QMovie* getIllustration() const { return illustration; }
    QSize getSize() const { return size; }
protected:
    // View
    QWidget* parent;
    QLabel* character_avatar;
    QMovie* illustration;
    HealthBar* healthBar;
    // Literally size of avatar
    QSize size;
    QPushButton *button;
};

// 哦牛批，模板构造函数必须和类本身一块实现在头文件里，泛型毁了OOP
template<typename MetaType>
CharacterAnimation::CharacterAnimation(MetaType* _meta, QWidget*_parent){
    // 创建角色头像标签
    parent = _parent;
    character_avatar = new QLabel(parent);
    button = new QPushButton(parent);
    character_avatar->setObjectName("character_avatar_" + _meta->getname());
    QString pic_path = ":image/images/" + _meta->getname() + ".gif";
    illustration = new QMovie(pic_path);
    QImageReader reader(pic_path);
    size = reader.size();
    // 创建血条控件
    healthBar = new HealthBar(getAvatar());
}

#endif // CHARACTERANIMATION_H
