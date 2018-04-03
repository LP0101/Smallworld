//
// Created by Popesco, Luca on 2018-04-02.
//

#include "CoinsDecorator.h"

CoinsDecorator::CoinsDecorator(StatsObserver *s, StatsSubject *su) : StatsDecorator(s) {
    _undecorated = s;
    _subject = su;
}

void CoinsDecorator::Update(){
    StatsDecorator::Update();
    cout << "Coins:" << endl;
    for(auto player : _subject->getPlayers()){
        cout << player->getName() << ": " << player->getVp() << endl;
    }

}
string getType(){return "coins";}