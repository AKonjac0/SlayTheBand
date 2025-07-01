#ifndef HOMEPAGE_H
#define HOMEPAGE_H
#include <QPushButton>
#include <QMediaPlayer>
#include <QGraphicsVideoItem>

class HomePage : public QWidget
{
public:
    HomePage(QWidget *parent = nullptr);
    ~HomePage();
    QPushButton *getStartButton();
private:
    QWidget *parent;
    QPushButton *startButton;
    QMediaPlayer *videoPlayer;
    QGraphicsVideoItem *videoItem;

    friend class PageManager;
};

#endif //HOMEPAGE_H
