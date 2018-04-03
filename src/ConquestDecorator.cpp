//
// Created by Popesco, Luca on 2018-04-02.
//

#include "ConquestDecorator.h"

ConquestDecorator::ConquestDecorator(StatsObserver *s, StatsSubject *su) : StatsDecorator(s){
   cout << "Decorated" << endl;
    _undecorated = s;
    _subject = su;
}

void ConquestDecorator::Update() {
    StatsDecorator::Update();
    cout << barGraph() << endl;
//    cout << "The undecoratedObserver is at"  << _undecorated <<endl;
//    cout << "The the conquestSubject is at " << _subject << endl;
    cout << "\n";
}

string ConquestDecorator::barGraph() {
    std::map<string, int> zonesControlled =_subject->getNodes();
    int totalZones = 0;
    for(auto const &x : zonesControlled){
        totalZones+=x.second;
    }
    string graph;
    graph = "Zones Controlled:\n";
    float percent;

    for (auto const &x : zonesControlled) {
        if(x.first == "")
            continue;
        percent = (float)x.second / totalZones;
        percent*=100;
        string player = x.first;
        string bar;
        for (int i = 5; i < (int)percent; i += 5) {
            bar += "*";
        }
        string row = player + ": " + bar + " " + to_string(percent)+"%\n";
        graph+=row;
    }
    return graph;
}

string ConquestDecorator::getType() {return "conquest";}