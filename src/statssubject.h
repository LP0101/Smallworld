//
// Created by Popesco, Luca on 2018-03-30.
//

#ifndef PROJECT_STATSSUBJECT_H
#define PROJECT_STATSSUBJECT_H

#include "subject.h"
#include "map.h"
#include <Map>
#include "player.h"

using namespace std;

class StatsSubject : public Subject{
public:
    StatsSubject(Map* map);
    std::map<std::string,int> getNodes();
    int getTurn();
    void setTurn(int turnNumber);
    vector<Player*> getPlayers();
    void setPlayers(vector<Player*> players);
private:
    vector<Player*> _players;
    Map * map;
    int turn;

};


#endif //PROJECT_STATSSUBJECT_H
