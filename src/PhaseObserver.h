//
// Created by Popesco, Luca on 2018-03-29.
//

#ifndef PROJECT_PHASEOBSERVER_H
#define PROJECT_PHASEOBSERVER_H

#include "observer.h"
#include "PhaseSubject.h"
#include <iostream>

using namespace std;



class PhaseObserver : public Observer{
public:
    PhaseObserver();
    PhaseObserver(PhaseSubject* s);
    ~PhaseObserver();
    void Update();
private:
    PhaseSubject* _subject;
    string player;
    string action;

};


#endif //PROJECT_PHASEOBSERVER_H
