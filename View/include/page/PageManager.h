#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H
#include <QVector>
#include <QWidget>
#include "Card_Manager.h"
#include "CardView.h"
#include "CharacterAnimation.h"
#include "Music_Manager.h"

enum class PageAnimationDirection {
    LeftToRight,
    RightToLeft
};

class PageManager{
public:
    PageManager(QWidget *parent, int page_width, int page_height);
    ~PageManager();
private:
    void switchToPage(QWidget *targetPage, PageAnimationDirection direction);
    void enterGame();

    QWidget *now_page;
    QWidget *parent;
    int page_width;
    int page_height;
    QWidget *page0;
    QWidget *page1;
    QWidget *page2;
    // QWidget *pageArrow;
    bool animationInProgress = false;

    Player *player;
    Enemy *enemy;

    Card_Manager *card_manager;
    CardView *card_view;
    CharacterAnimation* character_animation;
    Music_Manager *music;
};

#endif // PAGEMANAGER_H
