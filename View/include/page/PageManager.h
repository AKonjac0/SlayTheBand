#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include "CardView.h"
#include "Music_Manager.h"
#include "CardRewardPage.h"
#include "HomePage.h"
#include "MapPage.h"
#include "BattlePage.h"
#include "PlayerAnimation.h"
#include "EnemyAnimation.h"
#include "CombatView.h"

enum class PageAnimationDirection {
    LeftToRight,
    RightToLeft
};

class PageManager : public QObject{
    Q_OBJECT
public:
    PageManager(QWidget *parent, int page_width, int page_height);
    ~PageManager();

    CardView *getCardView(){return card_view;}
    CombatView *getCombatView(){return combat_view;}
    CardRewardPage *getCardRewardPage() const { return page3; }
    PlayerAnimation *getPlayerAnimation() { return playerAnimation; }
    EnemyAnimation *getEnemyAnimation() { return enemyAnimation; }
    void init();
signals:
    void startGame();
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

    PlayerAnimation *playerAnimation;
    EnemyAnimation *enemyAnimation;


    CardView *card_view;
    Music_Manager *music;

    // Combat *combat;
    CombatView *combat_view;

    friend class CardRewardPage;
};

#endif // PAGEMANAGER_H
