//
// Created by Popesco, Luca on 2018-04-02.
//

#include "undecoratedObserver.h"

undecoratedObserver::undecoratedObserver(StatsSubject* s) {_subject = s; _subject->Attach(this);}
void undecoratedObserver::Update() {
    cout << "The turn number is: " << _subject->getTurn() << endl;
//    cout << "The undecorated oberserver's subject is at " << _subject << endl;
//    cout << "This is at: " << this << endl;
}
string undecoratedObserver::getType() {return "undecorated";}
StatsObserver* undecoratedObserver::getUnder() {return nullptr;}
void undecoratedObserver::setUnder(StatsObserver *under) {}