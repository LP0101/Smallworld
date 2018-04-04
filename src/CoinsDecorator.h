//
// Created by Popesco, Luca on 2018-04-02.
//

#ifndef PROJECT_COINSDECORATOR_H
#define PROJECT_COINSDECORATOR_H
#include "StatsDecorator.h"

class CoinsDecorator : public StatsDecorator{
public:
    CoinsDecorator(StatsObserver *s, StatsSubject* su);
    void Update();
    string getType();
    StatsObserver *getUnder();
    void setUnder(StatsObserver* under);

protected:
    StatsObserver *_undecorated;
};


#endif //PROJECT_COINSDECORATOR_H
