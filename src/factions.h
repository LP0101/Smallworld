//
// Created by luca on 15/02/18.
//

#ifndef PROJECT_FACTIONS_H
#define PROJECT_FACTIONS_H
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "faction.h"
#include "piece.h"
#include "gamebox.h"


using namespace std;


class Factions {
public:
    Factions(string races, string powers, Gamebox * gamebox);
    vector<string> topDecks();
    Faction* take(int i, vector<vCoin*> cost);
    void giveBack(Faction* f);
    int requestValue(int i);
private:
    vector<Race*> races;
    vector<Power*> powers;
    fstream ifs;
    vector<vector<vCoin*>*> values;
    Gamebox *g;
};


#endif //PROJECT_FACTIONS_H
