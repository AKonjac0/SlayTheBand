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
#include <QGraphicsColorizeEffect>

Card::Card(Card_Meta *meta, QWidget *parent) :meta(meta), parent(parent) {
    button = new HoverButton("card", parent, true);
    QString cardPic = "QPushButton{border-image: url(:image/images/" + meta -> getCardName() + ".png);}";
    button->setStyleSheet(cardPic);
    // button->show();
    button->hide();

    animation = new CardAnimation(parent);

    QObject::connect(button, &QPushButton::clicked, parent, [this]() {
        // 应用动画效果
        animation->applyButtonAnimation(button);

        QGraphicsColorizeEffect* effect = new QGraphicsColorizeEffect(button);
        effect->setColor(Qt::white);      // 高光颜色
        effect->setStrength(0.0);         // 初始不可见
        button->setGraphicsEffect(effect);

        // 连接动画
        QPropertyAnimation* anim = new QPropertyAnimation(effect, "strength");
        anim->setDuration(150);           // 动画时长(毫秒)

        if(this->getButton()->Selected()){
            this->getButton()->Selected() = false;
            anim->stop();
            anim->setStartValue(0.3);
            anim->setEndValue(0.0);       // 释放时消失
            anim->start(QAbstractAnimation::DeleteWhenStopped);
        }else{
            this->getButton()->Selected() = true;
            anim->stop();
            anim->setStartValue(0.0);
            anim->setEndValue(0.3);       // 按下时显示强度
            anim->start(QAbstractAnimation::DeleteWhenStopped);
        }

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
    delete animation;
}

HoverButton* Card::getButton() const {
    return button;
}

Card_Meta* Card::getMeta() const {
    return meta;
}

