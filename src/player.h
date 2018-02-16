//
// Created by luca on 15/02/18.
//

#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H

#import <iostream>
#import "faction.h"
#import "map.h"
#import <algorithm>
#include "factions.h"
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
    void addVp(int i);
    void removeVp(int i);
    rDice *dice;

private:
    int vp;
    string name;
    Faction *primary, *secondary, *spirit;
    vector<string> nodes;
    Factions *deck;
    Map *map;

};


#endif //PROJECT_PLAYER_H
