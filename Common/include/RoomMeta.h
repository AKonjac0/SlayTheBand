#ifndef ROOM_H
#define ROOM_H
#include <QString>
#include <QVector>
#include <QObject>
// enum RoomType{Invalid, Monster, Elite, Boss};
enum visitType{closed, opened, visited};


class RoomMeta : public QObject{
    Q_OBJECT
public:
    RoomMeta(int x, int y, const QString &name, visitType visit, std::pair<int, int> id) : x(x), y(y), name(name), visit(visit), id(id) {}
    ~RoomMeta() = default;
    const QString &getRoomName() const { return name; }
    visitType getVisit() const { return visit; }
    const QVector<RoomMeta *> &getNext() const { return next; }
    const std::pair<int, int > &getId() const { return id; }
    int getX() { return x; }
    int getY() { return y; }
public slots:
    void setVisit(visitType vis);
    void addNext(RoomMeta *room);
    void openNext();
signals:
    void onVisitChanged();
private:
    int x, y;
    QString name;
    QVector<RoomMeta*> next;
    visitType visit;
    std::pair<int, int> id;
};
#endif // ROOM_H
