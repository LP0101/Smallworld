#include <iostream>
#include "rDice.h"
#include "map.h"
#include "factions.h"
#include "player.h"

using namespace std;

int main() {
    Map *a = new Map();
    Gamebox *g = new Gamebox();
    a->build("Maps/ThreePlayersR2.map");

    cout << "New map created based on given picture" << endl << endl;

    cout << "Printing adjacent zones to Fo5: " << endl;
    a->printAdjacent("Fo5");

    cout << endl << "Changing Fo5 and Fa4 to faction 'test'" << endl << endl;
    a->setFaction("Fo5","test");
    a->setFaction("Fa4","test");
    cout << "Printing allied adjacent zones to Fo5: " << endl;
    a->printAdjacentControlled("Fo5");

    cout << endl << "Making a new nice object" << endl;
    rDice r = rDice();
    cout << "Rolling dice 10 times:" << endl;

    for(int i=0;i<10;i++) {
        cout << r.roll() << endl;
    }
    cout << "3 was rolled " + to_string(r.getPercentage(3)) << endl;

    cout << endl << "Making a new deck of factions using files in GameConfig" << endl;
    Factions *f = new Factions("GameConfig/Races","GameConfig/Powers");
    vector<string> top = f->topDecks();

    cout << "The top 6 power/race combinations in the deck are: " << endl;

    for(string faction : top){
       cout << faction << endl;
    }

    cout << endl << "Making a new player using the created deck and map. For testing, players start with 20 Victory Points" << endl;
    Player luca = Player("luca",f,a,g);
    cout << "Player chooses race in slot [2]. Victory Points drop by 2." << endl;
    luca.picks_race(2);
    cout << "VP: " << luca.getVp() << endl;
    cout << endl << "Races 1 and 0 now have a point value of (1). New race is added to the top 6" << endl;

    top = f->topDecks();
    for(string faction : top){
       cout << faction << endl;
    }

    cout << endl << "Picking a race with a value gives the player that many VP" << endl;
    luca.picks_race(0);
    cout << "VP: " << luca.getVp() << endl;

    cout << endl << "Players can also conquer spaces, which costs tokens" << endl;
    luca.conquers("Fo1",1);
    luca.conquers("M5",1);
    luca.conquers("W1",2);

    a->printAdjacentControlled("Fo1");

    cout << "\nToken values of each Race+Power combo are given in the GameConfig settings files" << endl;

    cout << "Scoring is based on number of zones controlled." << endl;
    luca.scores();
    cout << "VP: " << luca.getVp() << endl << endl;

    cout << "Players can also lose zones" << endl;

    luca.loses("M5");
    a->printAdjacentControlled("Fo1");

    cout << "\nPieces such as 'Fortress,' 'Dragon,' etc. Are handled through the map object itself, with faction powers on each node" << endl;
    cout << "Adding a dragon to node 'Fo1' can be done like this" << endl;
    a->addFactionPower("Fo1","Dragon");
    cout << "Faction Powers on Fo1 are: " << endl;
    for(string mods : a->getFactionPowers("Fo1")){
        cout << mods << endl;
    }
    cout << endl << "Removing Dragon, the powers are empty: ";
    a->removeFactionPower("Fo1", "Dragon");
    for(string mods : a->getFactionPowers("Fo1")){
        cout << mods << endl;
    }

}
