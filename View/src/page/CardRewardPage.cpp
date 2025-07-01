#include <CardRewardPage.h>
#include <QPushButton>

CardRewardPage::CardRewardPage(Card_Manager *manager, QWidget *parent) : QWidget(parent), manager(manager), parent(parent), reward(nullptr) {}

void CardRewardPage::newReward(){
    if(reward) delete reward, reward = nullptr;
    reward = new CardReward(manager, this);
    // update();
}

