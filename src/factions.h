//
// Created by luca on 15/02/18.
//

#ifndef PROJECT_FACTIONS_H
#define PROJECT_FACTIONS_H
#import <iostream>
#import <vector>
#import <sstream>
#import <fstream>
#import "faction.h"

using namespace std;

class Factions {
public:
    Factions(string races, string powers);
    vector<string> topDecks();
    Faction* take(int);
    void giveBack(Faction* f);
private:
    vector<vector<string>> races, powers;
    fstream ifs;
};


#endif //PROJECT_FACTIONS_H
