//
// Created by luca on 15/02/18.
//

#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H

#include <iostream>
#include "faction.h"
#include "map.h"
#include <algorithm>
#include "factions.h"
#include "piece.h"
#include "rDice.h"

using namespace std;


class Player {
public:
    Player(string name, Factions *f, Map *m);
    void picks_race(int i);
    void conquers(string node, int i);
    void loses(string node);
    void scores();
    int getVp();
    void addVp(vector<vCoin*>);
    vCoin *removeVp(int i);
    rDice *dice;
    string readSummarySheet();

private:
    vector<vCoin*> oneP,threeP,fiveP,tenP;
    string name, summarySheet;
    Faction *primary, *secondary, *spirit;
    vector<string> nodes;
    Factions *deck;
    Map *map;

};


#endif //PROJECT_PLAYER_H
