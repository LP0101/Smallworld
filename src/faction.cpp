//
// Created by luca on 15/02/18.
//

#include "faction.h"

//The faction card the player holds, composed of a power, race, and a number of tokens.

Faction::Faction(vector<string> p, vector<string> r) {
    power = p[0];
    race = r[0];
    pTokens = stoi(p[1]);
    rTokens=stoi(r[1]);
    name = p[0] + " " + r[0];
    decline = false;
    tokens = rTokens+pTokens;

}

string Faction::toString() {
    return name;
}

void Faction::toggleDecline() {
    decline = !decline;
}

//Returns the initial two vectors used to make the object. Used when returning it to the deck
vector<vector<string>> Faction::getRaw(){
    vector<vector<string>> f;
    vector<string> p,r;
    p.push_back(power);
    p.push_back(to_string(pTokens));
    r.push_back(race);
    r.push_back(to_string(rTokens));
    f.push_back(p);
    f.push_back(p);
    return f;
}
int Faction::getTokens() {return tokens;}
void Faction::setTokens(int i){tokens = i;}
