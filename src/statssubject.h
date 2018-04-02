//
// Created by Popesco, Luca on 2018-03-30.
//

#ifndef PROJECT_STATSSUBJECT_H
#define PROJECT_STATSSUBJECT_H

#include "subject.h"
#include "map.h"
#include <Map>

using namespace std;

class StatsSubject : public Subject{
public:
    StatsSubject(Map* map);
    std::map<std::string,int> getNodes();
    int getTurn();
    void setTurn(int turnNumber);
private:
    Map * map;
    int turnNumber;

};


#endif //PROJECT_STATSSUBJECT_H
