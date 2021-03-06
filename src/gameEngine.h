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
#include "statssubject.h"
#include "statsobserver.h"
#include "undecoratedObserver.h"
#include "ConquestDecorator.h"
#include "HandDecorator.h"
#include "CoinsDecorator.h"
#include <typeinfo>
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
    bool showDecoratorOptions;
    bool decorators[3];
   vector<Player*> players;
   Factions* deck;
   Gamebox* box;
    bool parse(string command, Player* p);
    vector<string> split(string);
    bool conquer(vector<string> commands, Player * p);
    bool show(vector<string> commands, Player * p);
    bool abandon(vector<string> commands, Player * p);
    bool setDecorators();
    bool removeDecorators();
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
    StatsObserver* statsObserver;
    StatsSubject* statsSubject;
    bool removeDecorator(string decorator);



};


#endif //PROJECT_GAMEENGINE_H
