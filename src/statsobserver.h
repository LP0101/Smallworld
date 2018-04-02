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
private:
    StatsSubject * _subject;

public:
    StatsObserver();
    StatsObserver(StatsSubject* s);
    void Update();
    string barGraph();

};


#endif //PROJECT_STATSOBSERVER_H
