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


using namespace std;


class Factions {
public:
    Factions(string races, string powers);
    vector<string> topDecks();
    Faction* take(int i);
    void giveBack(Faction* f);
    int requestValue(int i);
private:
    vector<vector<string>> races, powers;
    fstream ifs;
    vector<int> values;
};


#endif //PROJECT_FACTIONS_H
