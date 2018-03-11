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
#include <sstream>


class GameEngine {
public:
    GameEngine();
    void init();
    void gameLoop();

private:
   Map* map;
    int turns;
    int MAX_TURNS;
    void prePhase(Player * p);
    void mainPhase(Player * p);
    void reinforcePhase(Player * p);
    void scorePhase(Player * p);
    void endPhase(Player * p);
   vector<Player*> players;
   Factions* deck;
   Gamebox* box;
    bool parse(string command, Player* p);
    vector<string> split(string);
    bool conquer(vector<string> commands, Player * p);
    bool show(vector<string> commands, Player * p);
    vector<string> getControlled(string race);
    bool firstConquest;
    vector<Player *> lostZone;
    bool decline(Player * p);
    bool didConquer;
    bool reinforce(vector<string> commands, Player * p);
    int pillaged;


};


#endif //PROJECT_GAMEENGINE_H
