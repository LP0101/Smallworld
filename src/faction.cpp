//
// Created by luca on 15/02/18.
//

#include "faction.h"

//The faction card the player holds, composed of a power, race, and a number of tokens.

Faction::Faction(Power *p, Race *r) {
    power = p;
    race = r;
    pTokens = power->getTokens();
    rTokens=race->getTokens();
    name = power->getName() + " " + race->getName();
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
Race* Faction::getRace(){
    return race;
}
Power* Faction::getPower() {return power;}
int Faction::getTokens() {return tokens;}
