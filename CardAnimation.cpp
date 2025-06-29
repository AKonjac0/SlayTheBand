#include "CardAnimation.h"
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

CardAnimation::CardAnimation(QWidget *parent) : parent(parent) {}


void CardAnimation::applyButtonAnimation(QPushButton *button)
{

    static bool isAnimating = false;
    if(isAnimating == false) isAnimating = true;
    else return;


    QSequentialAnimationGroup* group = new QSequentialAnimationGroup(parent);

    // 1. 缩小按钮
    QPropertyAnimation* shrink = new QPropertyAnimation(button, "geometry", parent);
    shrink->setDuration(80);
    shrink->setStartValue(button->geometry());
    shrink->setEndValue(button->geometry().adjusted(5, 5, -5, -5));

    // 2. 向上弹跳+放大
    QParallelAnimationGroup* jumpGroup = new QParallelAnimationGroup(parent);

    // 位置动画
    QPropertyAnimation* posAnim = new QPropertyAnimation(button, "pos", parent);
    posAnim->setDuration(150);
    posAnim->setStartValue(button->pos());
    posAnim->setEndValue(button->pos() + QPoint(0, -20));
    posAnim->setEasingCurve(QEasingCurve::OutBack);

    // 缩放动画
    QPropertyAnimation* grow = new QPropertyAnimation(button, "geometry", parent);
    grow->setDuration(150);
    grow->setStartValue(button->geometry().adjusted(5, 5, -5, -5));
    grow->setEndValue(button->geometry().adjusted(-10, -10, 10, 10));

    jumpGroup->addAnimation(posAnim);
    jumpGroup->addAnimation(grow);

    // 3. 返回原位
    QPropertyAnimation* reset = new QPropertyAnimation(button, "geometry", parent);
    reset->setDuration(100);
    reset->setEndValue(button->geometry());

    // 组合所有动画
    group->addAnimation(shrink);
    group->addAnimation(jumpGroup);
    group->addAnimation(reset);
    group->start(QAbstractAnimation::DeleteWhenStopped);

    QObject::connect(group, &QPropertyAnimation::finished, []() {
        isAnimating = false;
    });

}
