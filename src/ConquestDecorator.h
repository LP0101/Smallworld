//
// Created by Popesco, Luca on 2018-04-02.
//

#ifndef PROJECT_CONQUESTDECORATOR_H
#define PROJECT_CONQUESTDECORATOR_H
#include "StatsDecorator.h"

class ConquestDecorator : public StatsDecorator {

public:
    explicit ConquestDecorator(StatsObserver *s, StatsSubject* su);
    void Update();
    string barGraph();
    string getType();
protected:
    StatsObserver * _undecorated;

};


#endif //PROJECT_CONQUESTDECORATOR_H
