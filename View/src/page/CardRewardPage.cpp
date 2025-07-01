#include <CardRewardPage.h>
#include <QPushButton>

CardRewardPage::CardRewardPage(Card_Manager *manager, QWidget *parent) : QWidget(parent), manager(manager), parent(parent), reward(nullptr)
{
    this->setGeometry(0, 0, parent->width(), parent->height());
    this->setAutoFillBackground(true);
    confirmBtn = new QPushButton(this);
    confirmBtn->setText("确定");
    confirmBtn->resize(64, 64);
    confirmBtn->move(10, 10);
}

void CardRewardPage::newReward(){
    if(reward) delete reward, reward = nullptr;
    reward = new CardReward(manager, this);
}

