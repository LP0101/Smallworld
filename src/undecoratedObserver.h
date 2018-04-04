//
// Created by Popesco, Luca on 2018-04-02.
//

#ifndef PROJECT_UNDECORATEDOBSERVER_H
#define PROJECT_UNDECORATEDOBSERVER_H
#include "StatsDecorator.h"


class undecoratedObserver : public StatsObserver {
public:
    explicit undecoratedObserver(StatsSubject *s);
    void Update();
    string getType();
    StatsObserver* getUnder();
    void setUnder(StatsObserver* under);

protected:
    StatsSubject *_subject;
};


#endif //PROJECT_UNDECORATEDOBSERVER_H
