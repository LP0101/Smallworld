//
// Created by Popesco, Luca on 2018-03-29.
//

#ifndef PROJECT_PHASESUBJECT_H
#define PROJECT_PHASESUBJECT_H

#include "subject.h"
#include <iostream>

using namespace std;


class PhaseSubject : public Subject {
private:
    string player;
    string action;
public:
    PhaseSubject();
    ~PhaseSubject();
    string getPlayer();
    string getAction();
    void setPlayer(string player);
    void setAction(string action);
};


#endif //PROJECT_PHASESUBJECT_H
