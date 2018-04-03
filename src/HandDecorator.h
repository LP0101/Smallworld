//
// Created by Popesco, Luca on 2018-04-02.
//

#ifndef PROJECT_HANDDECORATOR_H
#define PROJECT_HANDDECORATOR_H
#include "StatsDecorator.h"


class HandDecorator : public StatsDecorator{
public:
    HandDecorator(StatsObserver *s, StatsSubject *su);
    void Update();
    string getType();

protected:
    StatsObserver *_undecorated;
};


#endif //PROJECT_HANDDECORATOR_H
