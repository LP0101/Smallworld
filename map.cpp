//
// Created by Popesco, Luca on 2018-02-05.
//

#include "map.h"
#include <iostream>

using namespace std;

// LINKS
Map::Link::Link(Node *a, Node *b){
    from = a;
    to = b;
    Map::Link *lastOut = a->getLastOut();
    Map::Link *firstOut = a->getFirstOut();
    Map::Link *firstIn = b->getFirstIn();
    Map::Link *lastIn = b->getLastIn();

    if(lastOut == nullptr && firstOut == nullptr){
        a->firstOut = this;
        a->lastOut = this;
        this -> previousOut = NULL;
        this -> nextOut = NULL;
    }
    else{
        this->previousOut=lastOut;
        a->lastOut->nextOut = this;
        a->lastOut = this;
        this -> nextOut = nullptr;
    }
    if(firstIn == nullptr && lastIn == nullptr){
        b->firstIn = this;
        b->lastIn = this;
        this->previousIn = NULL;
        this->nextIn = NULL;
    }
    else{
        this->previousIn=lastIn;
        b->lastIn->nextIn = this;
        b->lastIn = this;
        this -> nextIn = nullptr;
    }


}

void Map::addLink(Node *a, Node *b) {
    new Map::Link(a,b);
}




//NODES
Map::Node *Map::addNode(std::string name) {
    Map::Node *node = new Map::Node(name);
    return node;
}

Map::Node::Node(string a){
    name = a;
    firstIn = nullptr;
    firstOut = nullptr;
    lastIn = nullptr;
    lastOut = nullptr;
}
void Map::Node::getAdjacent() {
    if(firstOut != nullptr){
        Map::Link *a = firstOut;
        while(true){
            cout << a->to->getName() << endl;
            if(a->nextOut == nullptr){
                break;
            }
            a = a->nextOut;
        }
    }
    if(firstIn != nullptr){
        Map::Link *b = firstIn;
        while(true){
            cout << b->from->getName() << endl;
            if(b -> nextOut == nullptr)
                break;
            b = b->nextIn;
        }
    }
}

Map::Link* Map::Node::getFirstIn() {
    return firstIn;
}
Map::Link* Map::Node::getFirstOut(){
    return firstOut;
}
Map::Link* Map::Node::getLastIn() {
    return lastIn;
}
Map::Link* Map::Node::getLastOut() {
    return lastOut;
}
std::string Map::Node::getName() {
    return name;
}




//MAP
Map::Map(){
}

