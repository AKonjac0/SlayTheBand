#include "PlayerAnimation.h"

PlayerAnimation::PlayerAnimation(PlayerMeta* _playerMeta, QWidget* _parent) : CharacterAnimation(_playerMeta, _parent){
    manaBar = new ManaBar(getAvatar());
}

void PlayerAnimation::show(int x, int y, int width, int height, int maxHP, int HP, int maxMP, int MP)
{
    if (!getAvatar()) {
        qWarning() << "Player avatar is null";
        return;
    }

    // 设置角色头像大小和位置
    getAvatar()->setGeometry(x, y, width, height);
    getButton()->setGeometry(x, y, width, height);
    getButton()->setStyleSheet(
        "QPushButton {"
        "   background: transparent;"
        "   border: none;"
        "}"
        "QPushButton:hover {"
        "   border: 1px dashed gray;"  // 悬停时显示虚线框（可选）
        "}"
        );
    getAvatar() -> setMovie(getIllustration());
    // getAvatar()->setStyleSheet("border-image: url(:/image/images/soyo.gif);
    // getAvatar()->setAutoFillBackground(true);
    getIllustration()->start();

    // 定位血条
    getHealthBar()->setMaxHealth(maxHP);
    getHealthBar()->setCurrentHealth(HP);
    getHealthBar()->setFixedWidth(getAvatar()->width() - 40); // 血条宽度
    getHealthBar()->move(20, getAvatar()->height() - 60); // 血条位置（底部）

    getManaBar()->setMaxMana(maxMP);
    getManaBar()->setCurrentMana(MP);
    getManaBar()->setFixedWidth(getAvatar()->width() - 40);
    getManaBar()->move(20, getAvatar()->height() - 30); // 法力条在血条下方

    // 确保显示在最上层
    // getAvatar()->raise();
    getAvatar()->show();
    getButton()->show();
    getButton()->raise();
}

void PlayerAnimation::setManaBarAnimation(int MP)
{
    manaBar->setCurrentMana(MP);
}

void PlayerAnimation::setHealthBarAnimation(int HP)
{
    healthBar->setCurrentHealth(HP);
}

void PlayerAnimation::setMaxManaBarAnimation(int maxMP)
{
    manaBar->setMaxMana(maxMP);
}

void PlayerAnimation::setMaxHealthBarAnimation(int maxHP)
{
    healthBar->setMaxHealth(maxHP);
}

PlayerAnimation::~PlayerAnimation(){
    if (manaBar) {
        delete manaBar;
    }
}
