//
// Created by Popesco, Luca on 2018-03-30.
//

#include "statssubject.h"

StatsSubject::StatsSubject(Map *map) {this->map = map; this->turnNumber=0;}

std::map<std::string,int> StatsSubject::getNodes() {return map->zonesControlled();}
int StatsSubject::getTurn() {return this->turnNumber;}
void StatsSubject::setTurn(int turnNumber) {this->turnNumber = turnNumber;}