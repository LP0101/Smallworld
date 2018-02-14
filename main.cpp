#include <iostream>
#include "map.h"
#include "MapLoader.h"

using namespace std;

int main() {
    MapLoader *l = new MapLoader("test.txt");
    l->addNodes();
//    Map a = Map();
//    a.addNode("b");
//    a.addNode("c");
//    a.addNode("d");
//    a.addNode("e");
//
//    a.addLink("b", "c");
//    a.addLink("d", "b");
//    a.addLink("e", "b");
//    a.setFaction("b","z");
//    a.setFaction("e","z");
//
//    a.printAdjacent("b");
//    a.printAdjacentControlled("b");

}
