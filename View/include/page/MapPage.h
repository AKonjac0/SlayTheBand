#ifndef MAPPAGE_H
#define MAPPAGE_H
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <Qpen>
#include <random>
#include <QGraphicsColorizeEffect>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

enum visitType{closed, opened, visited};

class RoomButton : public QPushButton{
public:
    RoomButton(QWidget *parent = nullptr) : QPushButton(parent), parent(parent), visit(closed) {
        next.clear();
        effect = new QGraphicsColorizeEffect(this);
        resize(128, 128);
        setStyleSheet("QPushButton{border-image: url(:image/images/monster.png);}");
    }
    ~RoomButton(){
        delete effect;
    }
    visitType getVisit() const { return visit; }
    void setVisit(visitType vis) {
        visit = vis;
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
    QGraphicsColorizeEffect *effect;
};



class Line{
public:
    Line(QWidget *parent = nullptr) : parent(parent) {}

public:
    void paint(const QPointF &from, const QPointF &to){
        QPainter painter(parent);
        // 创建虚线画笔
        QPen pen(Qt::gray);       // 设置颜色
        pen.setWidth(2);           // 设置线宽
        pen.setStyle(Qt::DashLine); // 设置为虚线样式
        painter.setPen(pen); // 应用画笔
        painter.drawLine(QLine(from.x(), from.y(), to.x(), to.y()));
    }
private:
    QWidget *parent;
};


class MapPage : public QWidget
{
    Q_OBJECT
public:
    MapPage(QWidget *parent = nullptr);
    ~MapPage();
    void paintEvent(QPaintEvent *event) override {
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
private:
    QWidget *parent;
    QVector<QVector<RoomButton *> > spire_tower;
    QPushButton *switchBtn;
    Line *painter;
    std::mt19937 rnd;
    friend class PageManager;
};

#endif //MAPPAGE_H
