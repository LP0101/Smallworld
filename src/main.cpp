#include <iostream>
#include "rDice.h"
#include "map.h"
#include "factions.h"
#include <vector>
#include <zconf.h>
#include "faction.h"
#include "player.h"

using namespace std;

int main() {
    Map *a = new Map();
    a->build("Maps/ThreePlayersR2.map");

//    a->printAdjacent("Fo5");
//    a->setFaction("S2","Orcs");
//    a->printAdjacentControlled("Fo5");

//    rDice r = rDice();
//
//    for(int i=0;i<10;i++) {
//        r.roll();
//    }
//    cout << "3 was rolled " + to_string(r.getPercentage(3)) << endl;
//
    Factions *f = new Factions("GameConfig/Races","GameConfig/Powers");
    vector<string> top = f->topDecks();
//
//    for(string faction : top){
//       cout << faction << endl;
//    }

//    Faction *z = f.take(2);
//
//    usleep(2000000);
//    top = f.topDecks();
//
//    for(string faction : top){
//       cout << faction << endl;
//    }
//
//    cout << z->toString() << endl;
//    cout << z->getTokens() << endl;
//
//    f.giveBack(z);

    Player luca = Player("luca",f,a);
    luca.picks_race(2);
    luca.picks_race(3);
    luca.picks_race(4);
    luca.conquers("Fo1",1);
    luca.conquers("M5",1);
    luca.conquers("W1",2);
    a->printAdjacent("Fo1");
    a->printAdjacentControlled("Fo1");
    luca.loses("M5");
    a->printAdjacentControlled("Fo1");
}
