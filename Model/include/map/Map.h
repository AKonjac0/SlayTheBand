#ifndef MAP_H
#define MAP_H
#include "RoomMeta.h"


#include <QVector>
#include <random>
class Map{
public:
    Map();
    ~Map();
    QVector<QVector<RoomMeta*> > get_tower() const {return spire_tower; }
private:
    QVector<QVector<RoomMeta*> > spire_tower;
    std::mt19937 rnd;
};
#endif // MAP_H
