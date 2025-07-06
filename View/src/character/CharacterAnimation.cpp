#include "CharacterAnimation.h"

CharacterAnimation::CharacterAnimation(QWidget* _parent){
    // 创建角色头像标签
    parent = _parent;
    character_avatar = new QLabel(parent);
    button = new QPushButton(parent);
    healthBar = new HealthBar(getAvatar());
}

void CharacterAnimation::init(){
    character_avatar->setObjectName("character_avatar_" + name);
    QString pic_path = ":image/images/" + name + ".gif";
    illustration = new QMovie(pic_path);
    QImageReader reader(pic_path);
    size = reader.size();
}

CharacterAnimation::~CharacterAnimation(){
    if (character_avatar != nullptr){
        delete character_avatar;
    }
    if (illustration != nullptr){
        delete illustration;
    }
}
