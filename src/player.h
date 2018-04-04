//
// Created by luca on 15/02/18.
//

#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H

class Strategy;
class RandomStrategy;
#include <iostream>
#include "faction.h"
#include "map.h"
#include <algorithm>
#include "factions.h"
#include "piece.h"
#include "rDice.h"
#include "gamebox.h"
#include "Strategy.h"

using namespace std;


class Player {
public:
    Player(string name, Factions *f, Map *m, Gamebox *g);
    void picks_race(int i);
    void conquers(string node, int i);
    void loses(string node);
    int scores(int i);
    int getVp();
    void addVp(vector<vCoin*>);
    int getTokens();
    vector<vCoin*> removeVp(int i);
    string readSummarySheet();
    void addMod(string node);
    void removeMod(string node);
    Faction * getPrimary();
    string getName();
    vector<Token *> * getTokenRef();
    void prepare();
    vector<string> getNodes();
    void decline();
    int roll();
    Faction* getSecondary();
    void reinforce(string node, int i);
    void abandon(string node);
    Map *getMap();
    void Strategize(int reinforce);
    void setStrategy(Strategy* strategy);

private:
    vector<vCoin*> oneP,threeP,fiveP,tenP;
    rDice * dice;
    string name, summarySheet;
    Faction *primary, *secondary, *spirit;
    vector<string> nodes;
    Factions *deck;
    Map *map;
    Gamebox *box;
    vector<Token*> primaryTokens;
    vector<Modifier*> powerMods;
    Strategy *_strategy;
};


#endif //PROJECT_PLAYER_H
