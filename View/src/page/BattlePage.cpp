#include "BattlePage.h"

BattlePage::BattlePage(QWidget *parent) : QWidget(parent), parent(parent)
{
    this->setGeometry(0, 0, parent->width(), parent->height());
    this->setAutoFillBackground(true);
    // 加载并设置背景图片
    QPixmap bkgnd1(":/image/images/Background1.jpg");
    if(bkgnd1.isNull()) {
        qDebug() << "[page]: Failed to load background image!";
    } else {
        bkgnd1 = bkgnd1.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QPalette palette1;
        palette1.setBrush(QPalette::Window, bkgnd1);
        this->setPalette(palette1);
    }
    this->setWindowOpacity(0.0);

    switchBtn = new QPushButton(this);
    switchBtn->move(1830, 20);
    switchBtn->resize(64, 64);
    QString BtnPic = "QPushButton{border-image: url(:image/images/map.png);}";
    switchBtn->setStyleSheet(BtnPic);
}