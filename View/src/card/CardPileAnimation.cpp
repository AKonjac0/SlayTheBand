#include "CardPileAnimation.h"
#include "Card.h"
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QEventLoop>
#include <QTimer>

CardPileAnimation::CardPileAnimation(QWidget *parent) : parent(parent) {}


void CardPileAnimation::applyDisCardAnimation(QVector<Card *> cards){

    // isAnimating, prevent other animations



    const QSize endSize(31, 41);
    const int card_size_x = 248;
    const int card_size_y = 328;
    const QSize startSize(card_size_x, card_size_y);
    const int parentWidth = parent->width();
    const int parentHeight = parent -> height();
    const int spacing = -70; // 卡片间距

    // 计算卡片排列的总宽度

    int endX = parentWidth; // 右侧起始位置
    int yPos = parentHeight;
    // 使用并行动画组管理所有卡片动画
    const int animationDuration = 600; // 每个卡片动画总时长

    int card_size = cards.size();
    for (int i = card_size - 1; i >= 0; --i) {
        QPushButton *card = cards[i]->getButton();

        QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(card);
        opacityEffect->setOpacity(1.0);
        card->setGraphicsEffect(opacityEffect);

        // 目标位置（从右向左排列）
        int targetX = endX;
        QPoint endPos(targetX, yPos);

        // 位置动画
        QPropertyAnimation *posAnim = new QPropertyAnimation(card, "pos", parent);
        posAnim->setDuration(animationDuration);
        posAnim->setStartValue(card->pos());
        posAnim->setEndValue(endPos);
        posAnim->setEasingCurve(QEasingCurve::OutBack);

        // 大小动画（310x410 -> 31x41）
        QPropertyAnimation *sizeAnim = new QPropertyAnimation(card, "geometry", parent);
        sizeAnim->setDuration(animationDuration);
        sizeAnim->setStartValue(QRect(card->pos().x(), card->pos().y(), startSize.width(), startSize.height()));
        sizeAnim->setEndValue(QRect(endPos, endSize));
        sizeAnim->setEasingCurve(QEasingCurve::OutBack);

        // 透明度动画（1 -> 0）
        QPropertyAnimation *opacityAnim = new QPropertyAnimation(opacityEffect, "opacity", parent);
        opacityAnim->setDuration(animationDuration);
        opacityAnim->setStartValue(1.0);
        opacityAnim->setEndValue(0.0);
        opacityAnim->setEasingCurve(QEasingCurve::OutBack);

        // 组合动画（位置+大小+透明度同步）
        QParallelAnimationGroup *cardGroup = new QParallelAnimationGroup(parent);
        cardGroup->addAnimation(posAnim);
        cardGroup->addAnimation(sizeAnim);
        cardGroup->addAnimation(opacityAnim);

        // 设置卡片动画的延迟启动（每个卡片比前一个卡片延迟overlapDelay毫秒）
        QEventLoop loop;
        QTimer::singleShot(100, &loop, SLOT(quit()));
        loop.exec();
        if(!loop.isRunning()){
            cardGroup->start(QAbstractAnimation::DeleteWhenStopped);
        }

    }

    // manager->discard();
}

void CardPileAnimation::applyDrawCardAnimation(QVector<Card *> cards){

    // manager->drawcard();

    const QSize startSize(31, 41);
    const int card_size_x = 248;
    const int card_size_y = 328;
    const QSize endSize(card_size_x, card_size_y);
    const int parentWidth = parent->width();
    const int parentHeight = parent -> height();
    const int spacing = -70; // 卡片间距
    // QVector<Card *> cards = control->get_handcard();

    // 计算卡片排列的总宽度
    int totalWidth = cards.size() * endSize.width() + (cards.size() - 1) * spacing;
    int startX = (parentWidth - totalWidth) / 2; // 右侧起始位置
    int yPos = parentHeight - card_size_y + 100;
    // 使用并行动画组管理所有卡片动画
    const int animationDuration = 600; // 每个卡片动画总时长

    int card_size = cards.size();
    for (int i = card_size - 1; i >= 0; --i) {
        QPushButton *card = cards[i]->getButton();

        // 设置初始状态：左下角外、小尺寸、完全透明
        card->setGeometry(0, parentHeight, startSize.width(), startSize.height());
        card->show();
        // 设置透明度效果
        QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(card);
        opacityEffect->setOpacity(0.0);
        card->setGraphicsEffect(opacityEffect);

        // 目标位置（从右向左排列）
        int targetX = startX + i * (endSize.width() + spacing);
        QPoint endPos(targetX, yPos);

        // 位置动画（左下角 -> 目标位置）
        QPropertyAnimation *posAnim = new QPropertyAnimation(card, "pos", parent);
        posAnim->setDuration(animationDuration);
        posAnim->setStartValue(QPoint(0, parentHeight));
        posAnim->setEndValue(endPos);
        posAnim->setEasingCurve(QEasingCurve::OutBack);

        // 大小动画（31x41 -> 310x410）
        QPropertyAnimation *sizeAnim = new QPropertyAnimation(card, "geometry", parent);
        sizeAnim->setDuration(animationDuration);
        sizeAnim->setStartValue(QRect(0, parentHeight, startSize.width(), startSize.height()));
        sizeAnim->setEndValue(QRect(endPos, endSize));
        sizeAnim->setEasingCurve(QEasingCurve::OutBack);

        // 透明度动画（0 -> 1）
        QPropertyAnimation *opacityAnim = new QPropertyAnimation(opacityEffect, "opacity", parent);
        opacityAnim->setDuration(animationDuration);
        opacityAnim->setStartValue(0.0);
        opacityAnim->setEndValue(1.0);

        opacityAnim->setEasingCurve(QEasingCurve::InQuad);

        // 组合动画（位置+大小+透明度同步）
        QParallelAnimationGroup *cardGroup = new QParallelAnimationGroup(parent);
        cardGroup->addAnimation(posAnim);
        cardGroup->addAnimation(sizeAnim);
        cardGroup->addAnimation(opacityAnim);

        // 设置卡片动画的延迟启动（每个卡片比前一个卡片延迟overlapDelay毫秒）
        QEventLoop loop;
        QTimer::singleShot(100, &loop, SLOT(quit()));
        loop.exec();
        if(!loop.isRunning()){
            cardGroup->start(QAbstractAnimation::DeleteWhenStopped);
        }

    }

}


