#include "EnemyAnimation.h"

EnemyAnimation::~EnemyAnimation() {
    delete intention;
}


EnemyAnimation::EnemyAnimation(QWidget *_parent): CharacterAnimation(_parent), intention(new QPushButton(_parent)) {}

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
    getBlockBar()->setFixedWidth(getAvatar()->width() - 40); // 宽度
    getBlockBar()->move(20, getAvatar()->height() - 30); // 位置（底部）
    getBlockBar()->hide();

    // 确保显示在最上层
    // getAvatar()->raise();
    getAvatar()->show();
    getButton()->show();
    getButton()->raise();

    const int intentWidth = 128, intentHeight = 128;
    intention->setGeometry(x + width / 2 - intentWidth / 2, y - intentHeight, intentWidth, intentHeight);
    intention->show();
    intention->raise();
}

void EnemyAnimation::setHealthBarAnimation(int HP)
{
    healthBar->setCurrentHealth(HP);
}

void EnemyAnimation::setMaxHealthBarAnimation(int maxHP)
{
    healthBar->setMaxHealth(maxHP);
}

void EnemyAnimation::setBlockBarAnimation(int Block)
{
    blockBar->setCurrentBlock(Block);
}

void EnemyAnimation::setIntent(Buff intent)
{
    if(intent.getType() == Damage){
        int level = std::min(intent.getLevel() / 5 + 1, 7);
        QString str = "";
        str += static_cast<char>(level + '0');
        intention->setText(QString::number(intent.getLevel()));
        intention->setStyleSheet("QPushButton{border-image: url(:/image/images/attack/attack_intent_" + str + ".png);}");
    }else{
        intention->setStyleSheet("QPushButton{border-image: url(:/image/images/defend_intent_1.png);}");
    }
}
