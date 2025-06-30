#include "Player.h"

Player::Player(QString _name, int _HP, QWidget* _parent, int _MP):Character(_name,_HP, _parent), maxMP(_MP){
    MP = maxMP;
    manaBar = new ManaBar(getAvatar());
};

void Player::MP_change(int amount){
    MP += amount;
    MP = qBound(0, MP, maxMP);
    manaBar->setCurrentMana(MP);
}

void Player::show_character(int x, int y, int width, int height)
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
    getHealthBar()->move(20, getAvatar()->height() - 50); // 血条位置（底部）

    getManaBar()->setMaxMana(getMaxMP());
    getManaBar()->setCurrentMana(getMP());
    getManaBar()->setFixedWidth(getAvatar()->width() - 40);
    getManaBar()->move(20, getAvatar()->height() - 30); // 法力条在血条下方

    // 确保显示在最上层
    getAvatar()->raise();
    getAvatar()->show();
}
