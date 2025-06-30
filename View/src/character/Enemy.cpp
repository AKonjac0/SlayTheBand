#include "Enemy.h"

Enemy::Enemy(QString _name, int _HP, QWidget* _parent): Character(_name, _HP, _parent) {}

void Enemy::show_character(int x, int y, int width, int height)
{
    if (!getAvatar()) {
        qWarning() << "Character avatar is null for" << getname();
        return;
    }

    // 设置角色头像大小和位置
    getAvatar()->setGeometry(x, y, width, height);

    getAvatar() -> setMovie(getIllustration());
    getIllustration() -> start();

    // 定位血条
    getHealthBar()->setMaxHealth(getmaxHP());
    getHealthBar()->setCurrentHealth(getHP());
    getHealthBar()->setFixedWidth(getAvatar()->width() - 40); // 血条宽度
    getHealthBar()->move(20, getAvatar()->height() - 30); // 血条位置（底部）

    // 确保显示在最上层
    getAvatar()->raise();
    getAvatar()->show();
}
