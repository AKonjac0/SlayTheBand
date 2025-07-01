#include "EnemyAnimation.h"

EnemyAnimation::~EnemyAnimation()
{
    if (character_avatar) delete character_avatar;
    if (illustration) delete illustration;
    if (healthBar) delete healthBar;
}

EnemyAnimation::EnemyAnimation(EnemyMeta *_enemyMeta, QWidget *_parent): CharacterAnimation(_enemyMeta, _parent){}

void EnemyAnimation::show(int x, int y, int width, int height, int maxHP, int HP)
{
    if (!getAvatar()) {
        qWarning() << "Enemy avatar is null";
        return;
    }

    // 设置角色头像大小和位置
    getAvatar()->setGeometry(x, y, width, height);

    getAvatar() -> setMovie(getIllustration());
    getIllustration() -> start();

    // 定位血条
    getHealthBar()->setMaxHealth(maxHP);
    getHealthBar()->setCurrentHealth(HP);
    getHealthBar()->setFixedWidth(getAvatar()->width() - 40); // 血条宽度
    getHealthBar()->move(20, getAvatar()->height() - 60); // 血条位置（底部）

    // 确保显示在最上层
    getAvatar()->raise();
    getAvatar()->show();
}

void EnemyAnimation::setHealthBarAnimation(int HP)
{
    healthBar->setCurrentHealth(HP);
}

