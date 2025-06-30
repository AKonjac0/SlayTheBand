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
    button = new HoverButton("card", parent, true);
    QString cardPic = "QPushButton{border-image: url(:image/images/" + meta -> get_card_name() + ".png);}";
    button->setStyleSheet(cardPic);
    // button->show();
    button->hide();

    animation = new CardAnimation(parent);

    QObject::connect(button, &QPushButton::clicked, parent, [this]() {
        // 应用动画效果
        animation->applyButtonAnimation(button);

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

