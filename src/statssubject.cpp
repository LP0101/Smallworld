//
// Created by Popesco, Luca on 2018-03-30.
//

#include "statssubject.h"

StatsSubject::StatsSubject(Map *map) {this->map = map;}

std::map<std::string,int> StatsSubject::getNodes() {return map->zonesControlled();}

int StatsSubject::getTurn() {return turn;}

void StatsSubject::setTurn(int turnNumber) {turn = turnNumber;}

vector<Player*> StatsSubject::getPlayers() {return _players;}
void StatsSubject::setPlayers(vector<Player *> players) {_players=players;}