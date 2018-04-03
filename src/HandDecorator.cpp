//
// Created by Popesco, Luca on 2018-04-02.
//

#include "HandDecorator.h"

HandDecorator::HandDecorator(StatsObserver *s, StatsSubject *su) : StatsDecorator(s) {
    _undecorated = s;
    _subject = su;
}

void HandDecorator::Update() {
    StatsDecorator::Update();
    cout << "Hands: " << endl;
    for(auto player : _subject->getPlayers()){
        if(player->getPrimary() != nullptr) {
            cout << player->getName() << ": " << player->getPrimary()->toString() << endl;
        }
    }
    cout << "\n";
}
string HandDecorator::getType() {return "hand";}