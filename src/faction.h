//
// Created by luca on 15/02/18.
//

#ifndef PROJECT_RACE_H
#define PROJECT_RACE_H
#include <iostream>
#include <vector>

using namespace std;

class Faction {
public:
    Faction(vector<string> p, vector<string> r);
    string toString();
    void toggleDecline();
    vector<vector<string>> getRaw();
    int getTokens();
    void setTokens(int i);

private:
    string name, race, power;
    int tokens,rTokens,pTokens;
    bool decline;
};


#endif //PROJECT_RACE_H
