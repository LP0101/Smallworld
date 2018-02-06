#include <iostream>
#include "map.h"

using namespace std;

int main() {
    Map a = Map();
    Map::Node *b = a.addNode("b");
    Map::Node *c = a.addNode("c");
    Map::Node *d = a.addNode("d");
    Map::Node *e = a.addNode("e");
    Map::Node *f = a.addNode("f");
    Map::Link *bToC = a.addLink(b,c);
    Map::Link *bToD = a.addLink(b,d);
    Map::Link *fToB = a.addLink(f,b);
    Map::Link *eToB = a.addLink(e,b);
    Map::Link *dToC = a.addLink(d,c);
    a.removeLink(bToD);
    a.removeLink(dToC);
    //b->getAdjacent();
    if (d->getAdjacent().empty()){
        cout << "yay" << endl;
    }
    a.removeNode(d);
   // b->removeNode(e);
//    b->getAdjacent();
}
