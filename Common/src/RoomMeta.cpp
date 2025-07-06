#include "RoomMeta.h"


void RoomMeta::setVisit(visitType vis) {
    if(visit != vis){
        visit = vis;
        emit onVisitChanged();
    }
}

void RoomMeta::addNext(RoomMeta *room){
    next.push_back(room);
}

void RoomMeta::openNext(){
    for(RoomMeta *i : next){
        i->setVisit(opened);
    }
}
