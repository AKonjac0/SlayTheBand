#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H
#include "Card_Manager.h"
#include "CardView.h"
#include "Player.h"
#include "Enemy.h"
#include "Music_Manager.h"
#include "CardRewardPage.h"
#include "HomePage.h"
#include "MapPage.h"
#include "BattlePage.h"

enum class PageAnimationDirection {
    LeftToRight,
    RightToLeft
};

class PageManager{
public:
    PageManager(QWidget *parent, int page_width, int page_height);
    ~PageManager();
    Card_Manager *getCardManager();
    CardView *getCardView();
private:
    void switchToPage(QWidget *targetPage, PageAnimationDirection direction);
    void enterGame();

    QWidget *now_page;
    QWidget *parent;
    int page_width;
    int page_height;
    HomePage *page0;
    BattlePage *page1;
    MapPage *page2;
    CardRewardPage *page3;
    bool animationInProgress = false;

    Player *player;
    Enemy *enemy;

    Card_Manager *card_manager;
    CardView *card_view;
    Music_Manager *music;

    friend class CardRewardPage;
};

#endif // PAGEMANAGER_H
