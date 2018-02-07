#include <iostream>
#include "map.h"

using namespace std;

int main() {
    Map a = Map();
    a.addNode("b");
    a.addNode("c");
    a.addNode("d");
    a.addNode("e");

    a.addLink("b","c");
    a.addLink("d","b");
    a.addLink("e","b");
    a.addLink("d","c");

    a.removeLink("d","b");

    a.printAdjacent("b");
    a.printAdjacent("c");


//    Map::Node *b = a.addNode("b");
//    Map::Node *c = a.addNode("c");
//    Map::Node *d = a.addNode("d");
//    Map::Node *e = a.addNode("e");
//    Map::Node *f = a.addNode("f");
//    Map::Link *bToC = a.addLink(b,c);
//    Map::Link *bToD = a.addLink(b,d);
//    Map::Link *fToB = a.addLink(f,b);
//    Map::Link *eToB = a.addLink(e,b);
//    Map::Link *dToC = a.addLink(d,c);
//    a.removeLink(bToD);
//    a.removeLink(dToC);
 //   b->getAdjacent();
//    b->getAdjacent();
//    a.removeNode(d);
   // b->removeNode(e);
//    b->getAdjacent();
}
