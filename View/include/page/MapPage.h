#ifndef MAPPAGE_H
#define MAPPAGE_H
#include <QWidget>
#include <QPushButton>
#include <QGraphicsColorizeEffect>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QPainter>
#include <QPen>
#include "RoomMeta.h"

class RoomButton : public QPushButton{
public:
    RoomButton(RoomMeta *room, QWidget *parent = nullptr) : QPushButton(parent), parent(parent), visit(closed), room(room) {
        next.clear();
        effect = new QGraphicsColorizeEffect(this);
        setGeometry(room->getX(), room->getY(), 128, 128);
        setStyleSheet("QPushButton{border-image: url(:image/images/" + room->getRoomName() + ".png);}");
        setVisit(room->getVisit());
        show();
    }
    ~RoomButton(){
        delete effect;
    }
    visitType getVisit() const { return room->getVisit(); }
    std::pair<int, int> getId() const { return room->getId(); }
    void setVisit(visitType vis) {
        room->setVisit(vis);
        if(vis == opened){
            effect->setColor(Qt::blue);
            effect->setStrength(1.0);

        }else if(vis == closed){
            effect->setColor(Qt::red);
            effect->setStrength(1.0);

        }else{
            effect->setColor(Qt::green);
            effect->setStrength(1.0);
            setStyleSheet("QPushButton{border-image: url(:image/images/mapCompleteIcon.png);}");
        }
        setGraphicsEffect(effect);

    }
    const QVector<RoomButton *> &getNext() const {
        return next;
    }

    void addNext(RoomButton *room){
        next.push_back(room);
    }
    void openNext(){
        for(RoomButton *i : next){
            i->setVisit(opened);
        }
    }

private:
    QWidget *parent;
    visitType visit;
    QVector<RoomButton *> next;
    RoomMeta *room;
    QGraphicsColorizeEffect *effect;
};



class MapPage : public QWidget
{
    Q_OBJECT
public:
    MapPage(QWidget *parent = nullptr);
    ~MapPage();
    void paintEvent(QPaintEvent *event) override;
    RoomButton *find_button(RoomMeta *room){
        std::pair<int, int> id = room->getId();
        return spire_tower[id.first][id.second];
    }
    void setMap(QVector<QVector<RoomMeta *> > ret_map){
        if(map != ret_map) map = ret_map;
    }
    QVector<QVector<RoomButton *> > getTower(){ return spire_tower; }
    void createRooms();
public slots:
    void fireGetMap(){
        emit onGetMap();
    }
signals:
    void onGetMap();
public:
    QPushButton *switchBtn;
private:
    QWidget *parent;
    QVector<QVector<RoomButton *> > spire_tower;
    QVector<QVector<RoomMeta *> > map;

    friend class PageManager;
};

#endif //MAPPAGE_H
