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
#include "PhaseSubject.h"
#include "PhaseObserver.h"
#include <string>


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
    void retreatPhase(Player * p);
   vector<Player*> players;
   Factions* deck;
   Gamebox* box;
    bool parse(string command, Player* p);
    vector<string> split(string);
    bool conquer(vector<string> commands, Player * p);
    bool show(vector<string> commands, Player * p);
    bool abandon(vector<string> commands, Player * p);
    void help();
    vector<string> getControlled(string race);
    bool firstConquest;
    vector<Player *> lostZone;
    bool decline(Player * p);
    bool didConquer;
    bool reinforce(vector<string> commands, Player * p);
    int pillaged;
    int conquered;
    string currentPhase;
    PhaseObserver* phaseObserver;
    PhaseSubject* phaseSubject;


};


#endif //PROJECT_GAMEENGINE_H
