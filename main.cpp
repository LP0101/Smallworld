#include <iostream>
#include "map.h"

int main() {
    Map a = Map();
    Map::Node *b = a.addNode("b");
    Map::Node *c = a.addNode("c");
    Map::Node *d = a.addNode("d");
    Map::Node *e = a.addNode("e");
    a.addLink(b,c);
    a.addLink(b,d);
    a.addLink(e,b);
    e->getAdjacent();
}
