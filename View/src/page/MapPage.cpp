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

void MapPage::createRooms(){
    for(auto &level : map){ // level 0 ~ 7
        QVector<RoomButton *> new_level;
        for(RoomMeta *room : level){
            RoomButton *button = new RoomButton(room, this);
            new_level.push_back(button);
        }
        spire_tower.push_back(new_level);
    }


    for(auto &level : map){
        for(RoomMeta *room : level){
            auto next_list = room->getNext();
            RoomButton *now_button = find_button(room);
            for(RoomMeta *next_room : next_list){
                now_button->addNext(find_button(next_room));
            }
        }
    }
}



void MapPage::paintEvent(QPaintEvent *event) {
    // 创建 QPainter 对象
    QPainter painter(this);

    // 创建 QPen 并设置为虚线样式
    QPen pen(Qt::gray);  // 设置颜色
    pen.setWidth(2);      // 设置线条宽度
    pen.setStyle(Qt::DashLine);  // 设置为虚线

    // 将 QPen 应用到 QPainter
    painter.setPen(pen);

    for(int i = 0; i < 7; ++i){
        auto this_level = spire_tower[i], next_level = spire_tower[i + 1];
        for(RoomButton *room : this_level){
            auto next_rooms = room->getNext();
            for(auto next_room : next_rooms){
                QPointF room_center = room->pos() + QPointF(room->width() / 2.0, room->height() / 2.0);
                QPointF next_center = next_room->pos() + QPointF(next_room->width() / 2.0, next_room->height() / 2.0);
                painter.drawLine(room_center.x(), room_center.y(), next_center.x(), next_center.y());
            }
        }
    }

}

MapPage::~MapPage(){
    for(auto &level : spire_tower){
        for(RoomButton *room : level){
            delete room;
        }
    }
}
