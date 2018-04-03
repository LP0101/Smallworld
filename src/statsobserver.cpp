//
// Created by Popesco, Luca on 2018-03-30.
//

#include "statsobserver.h"

StatsObserver::StatsObserver(StatsSubject* s) {_subject = s; _subject->Attach(this);}
StatsObserver::StatsObserver() {}

//string StatsObserver::barGraph() {
//    std::map<string, int> zonesControlled = _subject->getNodes();
//    int totalZones = 0;
//    for(auto const &x : zonesControlled){
//        totalZones+=x.second;
//    }
//    string graph;
//    graph = "Zones Controlled:\n";
//    float percent;
//
//    for (auto const &x : zonesControlled) {
//        if(x.first == "")
//            continue;
//        percent = (float)x.second / totalZones;
//        percent*=100;
//        string player = x.first;
//        string bar;
//        for (int i = 5; i < (int)percent; i += 5) {
//            bar += "*";
//        }
//        string row = player + ": " + bar + " " + to_string(percent)+"%\n";
//        graph+=row;
//    }
//    return graph;
//}

int StatsObserver::getTurns() {return this->_subject->getTurn();}
void StatsObserver::detachSelf() {_subject->Detach(&*this);}
StatsSubject* StatsObserver::getSubject() {return this->_subject;}
