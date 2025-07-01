#include "MapPage.h"

MapPage::MapPage(QWidget *parent) : QWidget(parent), parent(parent)
{
    this->setGeometry(0, 0, parent->width(), parent->height());
    this->setAutoFillBackground(true);
    QPixmap bkgnd2(":/image/images/map_page.png");
    if (bkgnd2.isNull()) {
        qDebug() << "[page2]: Failed to load background image!";
    } else {
        bkgnd2 = bkgnd2.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QPalette palette2;
        palette2.setBrush(QPalette::Window, bkgnd2);
        this->setPalette(palette2);
    }

    level1 = new QPushButton(this);
    level1->resize(128, 128);
    level1->move(500, 500);
    level1->setStyleSheet("QPushButton{border-image: url(:image/images/monster.png);}");

    // 初始化页面2为透明并隐藏在右侧
    this->setWindowOpacity(0.0);
    this->move(parent->width(), 0);

    switchBtn = new QPushButton(this);
    switchBtn->move(1830, 20);
    switchBtn->resize(64, 64);
    QString BtnPic = "QPushButton{border-image: url(:image/images/map.png);}";
    switchBtn->setStyleSheet(BtnPic);
    switchBtn->hide();
}