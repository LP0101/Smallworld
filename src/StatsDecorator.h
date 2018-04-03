//
// Created by Popesco, Luca on 2018-04-02.
//

#ifndef PROJECT_STATSDECORATOR_H
#define PROJECT_STATSDECORATOR_H
#include "statsobserver.h"

class StatsDecorator : public StatsObserver {
protected:
    StatsObserver *_decoratedObserver;
public:
    explicit StatsDecorator(StatsObserver *s);
    void Update();

};


#endif //PROJECT_STATSDECORATOR_H
