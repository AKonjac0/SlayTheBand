#include "MapPage.h"


MapPage::MapPage(QWidget *parent) : QWidget(parent), parent(parent), rnd(std::mt19937(std::random_device{}()))
{

    painter = new Line(this);
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
    const int RNDOFS = 100;
    for(int i = 0; i < 8; ++i){ // level 0 ~ 7
        int k = rnd() % 3 + 2; // 2 ~ 4 node
        QVector<RoomButton *> level;
        for(int j = 0; j < k; ++j){

            RoomButton *room = new RoomButton(this);
            int x_offset = rnd() % RNDOFS - RNDOFS / 2, y_offset = rnd() % RNDOFS - RNDOFS / 2;
            room->move((i + 1) * 200 + x_offset, (j + 1) * 200 + y_offset);
            level.push_back(room);
            if(i == 0) room->setVisit(opened);
            else room->setVisit(closed);
        }
        spire_tower.push_back(level);
    }

    for(int i = 0; i < 7; ++i){
        auto this_level = spire_tower[i], next_level = spire_tower[i + 1];
        int total = next_level.size(), remain = next_level.size();
        for(RoomButton *room : this_level){
            int m = rnd() % 3 + 1;
            int k = std::min(remain, m);
            for(int j = total - remain; j < total - remain + k; ++j){
                room->addNext(next_level[j]);
            }
            remain -= k - 1;
        }
        if(remain > 1){
            for(int j = total - remain; j < total; ++j){
                this_level[this_level.size() - 1]->addNext(next_level[j]);
            }
        }
    }
    for(auto &level : spire_tower){
        for(RoomButton *room : level){
            QObject::connect(room, &QPushButton::clicked, parent, [room, &level](){
                if(room->getVisit() == opened){
                    for(RoomButton *r : level) if(room != r) r->setVisit(closed);
                    room->openNext();
                    room->setVisit(visited);
                }
            });
        }
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


MapPage::~MapPage(){
    delete painter;
    for(auto &level : spire_tower){
        for(RoomButton *room : level){
            delete room;
        }
    }
}
