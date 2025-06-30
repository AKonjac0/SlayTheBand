#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H
#include <QVector>
#include <QWidget>
#include <QPushButton>

enum class PageAnimationDirection {
    LeftToRight,
    RightToLeft
};

class PageManager{
public:
    PageManager(QWidget *parent, int page_width, int page_height);
    ~PageManager();
    QWidget *get_now_page();
private:
    void switchToPage(QWidget *targetPage, PageAnimationDirection direction);
    QWidget *now_page;
    QWidget *parent;
    int page_width;
    int page_height;
    QWidget *page1;
    QPushButton *switchBtn1;
    QWidget *page2;
    QPushButton *switchBtn2;
    bool animationInProgress = false;
};

#endif // PAGEMANAGER_H
