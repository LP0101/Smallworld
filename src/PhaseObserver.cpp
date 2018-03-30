//
// Created by Popesco, Luca on 2018-03-29.
//

#include "PhaseObserver.h"

PhaseObserver::PhaseObserver() {}
PhaseObserver::PhaseObserver(PhaseSubject *s) {_subject = s; _subject->Attach(this);}

void PhaseObserver::Update() {
    this->player = _subject->getPlayer();
    this->action = _subject->getAction();

    cout << player << " " << action << endl;
}
