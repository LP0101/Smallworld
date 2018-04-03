//
// Created by Popesco, Luca on 2018-03-30.
//

#ifndef PROJECT_STATSOBSERVER_H
#define PROJECT_STATSOBSERVER_H

#include "observer.h"
#include <iostream>
#include "statssubject.h"
#include "map.h"

using namespace std;

class StatsObserver : public Observer{
public:
    StatsSubject * _subject;

public:
    StatsObserver();
    explicit StatsObserver(StatsSubject* s);
    virtual void Update()=0;
    virtual string getType()=0;
//    string barGraph();
    int getTurns();
    void detachSelf();
    StatsSubject *getSubject();

};


#endif //PROJECT_STATSOBSERVER_H
