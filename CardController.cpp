#include "CardController.h"



CardController::CardController(QWidget *parent) : parent(parent), drawcard_num(5) {
    for (int i = 0; i < 5; i++) {
        drawcard_pile.push_back(new_strike());
    }
    for (int i = 0; i < 4; i++) {
        drawcard_pile.push_back(new_defend());
    }
    drawcard_pile.push_back(new_bash());
    drawcard_pile.push_back(new_bash()); // 11 cards, test draw card

    shuffle(drawcard_pile);
}

CardController::~CardController() {
    for(auto &i : discard_pile) {
        delete i;
    }
    for (auto &i : drawcard_pile) {
        delete i;
    }
    for (auto &i : handcard) {
        delete i;
    }
}


void CardController::shuffle(QVector<Card_Meta*> &pile){
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::shuffle(pile.begin(), pile.end(), rng);
}


void CardController::transfer(QVector<Card_Meta *> &to, QVector<Card_Meta *> &from){
    if(!to.empty()) qDebug() << "[warning] transfering cards to a pile that is not empty!";
    for(auto &i : from){
        to.push_back(i);
    }
    from.clear();
}
void CardController::drawcard() {
    for(int i = 0; i < drawcard_num; ++i){
        if(drawcard_pile.empty()){
            transfer(drawcard_pile, discard_pile);
            shuffle(drawcard_pile);
            qDebug() << "牌堆被洗混";

        }
        Card *card = new Card(drawcard_pile.back(), parent);
        handcard.push_back(card);
        drawcard_pile.pop_back();


    }
}
void CardController::discard() {
    int handcard_num = handcard.size();
    for(int i = 0; i < handcard_num; ++i){
        discard_pile.push_back(handcard.back()->getMeta());
        Card *card = handcard.back();
        delete card;
        handcard.pop_back();
    }
}

QVector<Card_Meta *> CardController::get_drawcard_pile() const{
    return drawcard_pile;
}
QVector<Card_Meta *> CardController::get_discard_pile() const{
    return discard_pile;
}
QVector<Card *> CardController::get_handcard() const{
    return handcard;
}

//TODO
Card_Meta *CardController::new_strike() {
    return new Card_Meta("strike", attack, 1, 6, No, 0);

}

Card_Meta *CardController::new_defend() {
    return new Card_Meta("defend", skill, 1, 0, No, 5);
}

Card_Meta *CardController::new_bash() {
    return new Card_Meta("bash", attack, 2, 8, Vulnerable, 2);
}

void CardController::applyDisCardAnimation(){


    const QSize endSize(31, 41);
    const QSize startSize(310, 410);
    const int parentWidth = 1920 - 200;
    const int parentHeight = 1080;
    const int spacing = -70; // 卡片间距
    QVector<Card *> cards = get_handcard();

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
        opacityAnim->setStartValue(0.5);
        opacityAnim->setEndValue(0.0);

        // opacityAnim->setEasingCurve(QEasingCurve::InQuad);

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


    discard();
}


void CardController::applyDrawCardAnimation(){



    drawcard();


    const QSize startSize(31, 41);
    const QSize endSize(310, 410);
    const int parentWidth = 1920 - 200;
    const int parentHeight = 1080;
    const int spacing = -70; // 卡片间距
    QVector<Card *> cards = get_handcard();

    // 计算卡片排列的总宽度
    int totalWidth = cards.size() * endSize.width() + (cards.size() - 1) * spacing;
    int startX = parentWidth - totalWidth - 50; // 右侧起始位置
    int yPos = 50;
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
