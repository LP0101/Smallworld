//
// Created by luca on 15/02/18.
//

#ifndef PROJECT_RACE_H
#define PROJECT_RACE_H
#include <iostream>
#include <vector>
#include "piece.h"

using namespace std;

class Faction {
public:
    Faction(Power *p, Race *r);
    string toString();
    void toggleDecline();
    int getTokens();
    Race* getRace();
    Power* getPower();

private:
    string name;
    int tokens,rTokens,pTokens;
    bool decline;
    Power *power;
    Race *race;
};


#endif //PROJECT_RACE_H
