#include "EnemyAnimation.h"

EnemyAnimation::~EnemyAnimation() = default;


EnemyAnimation::EnemyAnimation(QWidget *_parent): CharacterAnimation(_parent){}

void EnemyAnimation::init() {
    emit getName();
    CharacterAnimation::init();
}

void EnemyAnimation::show(int x, int y, int width, int height, int maxHP, int HP)
{
    if (!getAvatar()) {
        qWarning() << "Enemy avatar is null";
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
    // getButton()->raise();
    // getButton()->set;
    getAvatar()->setMovie(getIllustration());
    getAvatar()->setStyleSheet("QLabel {"
        "   background: transparent;"
        "   border: none;"
        "}"
        // "border-image: url(:/image/images/soyo.gif);"
        );
    getAvatar()->setAutoFillBackground(true);
    getIllustration()->start();

    // 定位血条
    getHealthBar()->setMaxHealth(maxHP);
    getHealthBar()->setCurrentHealth(HP);
    getHealthBar()->setFixedWidth(getAvatar()->width() - 40); // 血条宽度
    getHealthBar()->move(20, getAvatar()->height() - 60); // 血条位置（底部）

    // 确保显示在最上层
    // getAvatar()->raise();
    getAvatar()->show();
    getButton()->show();
    getButton()->raise();
}

void EnemyAnimation::setHealthBarAnimation(int HP)
{
    healthBar->setCurrentHealth(HP);
}

void EnemyAnimation::setMaxHealthBarAnimation(int maxHP)
{
    healthBar->setMaxHealth(maxHP);
}
