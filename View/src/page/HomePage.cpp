#include "HomePage.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QAudioOutput>

HomePage::HomePage(QWidget *parent) : QWidget(parent), parent(parent)
{
    this->setGeometry(0, 0, parent->width(), parent->height());
    this->setAutoFillBackground(true);

    QGraphicsScene *scene = new QGraphicsScene(this);
    QGraphicsView *graphicsView = new QGraphicsView(scene, this);
    graphicsView->setGeometry(0, 0, 1920, 1080);
    graphicsView->setFrameShape(QFrame::NoFrame);
    graphicsView->setStyleSheet("background: transparent; border: none;");
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 创建视频项
    videoItem = new QGraphicsVideoItem();
    videoItem->setSize(QSizeF(1920, 1080));
    scene->addItem(videoItem);

    QAudioOutput *audioOutput = new QAudioOutput(this);

    // 创建媒体播放器
    videoPlayer = new QMediaPlayer(this);
    videoPlayer->setVideoOutput(videoItem);
    videoPlayer->setAudioOutput(audioOutput);
    videoPlayer->setLoops(-1);
    videoPlayer->setSource(QUrl::fromLocalFile("../../Videos/video1.mp4"));
    videoPlayer->play();

    startButton = new QPushButton("开始游戏", this);
    startButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgba(50, 150, 250, 200);"
        "   color: white;"
        "   font-size: 16px;"
        "   border-radius: 10px;"
        "   padding: 10px;"
        "}"
        );
    startButton->setGeometry(150, 500, 150, 80);
}

QPushButton *HomePage::getStartButton()
{
    return startButton;
}

HomePage::~HomePage()
{
    delete videoItem;
}
