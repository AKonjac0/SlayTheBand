#include "Map.h"

Map::Map() : rnd(std::mt19937(std::random_device{}())){
    const int RNDOFS = 100;
    for(int i = 0; i < 8; ++i){ // level 0 ~ 7
        int k = rnd() % 3 + 2; // 2 ~ 4 node
        QVector<RoomMeta *> level;
        for(int j = 0; j < k; ++j){
            int x_offset = rnd() % RNDOFS - RNDOFS / 2, y_offset = rnd() % RNDOFS - RNDOFS / 2;
            int type = rnd() % 10;
            int x = (i + 1) * 200 + x_offset, y = (j + 1) * 200 + y_offset;
            // RoomMeta *room = new RoomMeta(x, y, (type == 0 ? "elite" : "monster"), (i == 0 ? opened : closed), std::make_pair(i, j));
            RoomMeta *room = new RoomMeta(x, y, "monster", (i == 0 ? opened : closed), std::make_pair(i, j));
            level.push_back(room);
        }
        spire_tower.push_back(level);
    }


    for(int i = 0; i < 7; ++i){
        auto this_level = spire_tower[i], next_level = spire_tower[i + 1];
        int total = next_level.size(), remain = next_level.size();
        for(RoomMeta *room : this_level){
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
}


Map::~Map(){
    for(auto &level : spire_tower){
        for(RoomMeta *room : level){
            delete room;
        }
    }
}
