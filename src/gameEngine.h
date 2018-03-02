//
// Created by luca on 02/03/18.
//

#ifndef PROJECT_GAMEENGINE_H
#define PROJECT_GAMEENGINE_H

#include "map.h"
#include <vector>
#include "factions.h"
#include "gamebox.h"
#include "player.h"


class GameEngine {
public:
    GameEngine();
    void init();

private:
   Map* map;
   vector<Player*> players;
   Factions* deck;
   Gamebox* box;

};


#endif //PROJECT_GAMEENGINE_H
