#include "Card.h"
#include <QObject>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QDebug>
#include <QRandomGenerator>
#include <QTimer>
#include <QHBoxLayout>
#include <QGraphicsView>

Card::Card(Card_Meta *meta, QWidget *parent) :meta(meta), parent(parent) {
    button = new QPushButton("card", parent);
    QString cardPic = "QPushButton{border-image: url(:image/images/" + meta -> get_card_name() + ".png);}";
    button->setStyleSheet(cardPic);
    button->show();

    QObject::connect(button, &QPushButton::clicked, parent, [this]() {
        // 应用动画效果
        applyButtonAnimation();

        // 这里可以添加按钮原有的点击逻辑
        qDebug() << "按钮被点击:" << button->text();
    });
}

/**
 * @brief Card::~Card
 * should not manage Card_Meta
 * Card_Meta is managed by Card_Manager in order to simplify draw card pile / discard pile logic
 * when cards are discarded, QPushButtons are deconstructed and Card_Meta are inserted into discard pile
 */
Card::~Card(){
    delete button;
}

QPushButton* Card::getButton() const {
    return button;
}

Card_Meta* Card::getMeta() const {
    return meta;
}

void Card::applyButtonAnimation()
{

    static bool isAnimating = false;
    if(isAnimating == false) isAnimating = true;
    else return;

    // QPushButton* button = ui->pushButton;
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
