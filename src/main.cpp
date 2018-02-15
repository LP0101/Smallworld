#include <iostream>
#include "rDice.h"
#include "map.h"

using namespace std;

int main() {
    Map a = Map();
    a.build("Maps/ThreePlayersR2.map");

    a.printAdjacent("Fo5");
    a.setFaction("S2","Orcs");
    a.printAdjacentControlled("Fo5");

    rDice r = rDice();

    for(int i=0;i<10;i++) {
        r.roll();
    }
    cout << "3 was rolled " + to_string(r.getPercentage(3)) << endl;

}
