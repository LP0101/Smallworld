#include <iostream>
#include <zconf.h>
#include "map.h"

using namespace std;

int main() {
    Map a = Map();
    a.build("Maps/ThreePlayersR2.map");

    a.printAdjacent("Fo5");

//    string test = "a,b,c";
//    string delimiter = ",";
//    while(true){
//        cout << test << endl;
//        test.erase(0, test.find(delimiter) + delimiter.length());
//        if(test.find(delimiter) == string::npos){
//            cout << test << endl;
//            break;
//        }
//    }

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
