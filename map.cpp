//
// Created by Popesco, Luca on 2018-02-05.
//

#include "map.h"
#include <iostream>
#include <vector>
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
        this -> previousOut = nullptr;
        this -> nextOut = nullptr;
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
        this->previousIn=b->lastIn;
        b->lastIn->nextIn = this;
        b->lastIn = this;
        this -> nextIn = nullptr;
    }
    lastOut=nullptr;
    firstOut = nullptr;
    lastIn = nullptr;
    lastOut = nullptr;


}
Map::Link::~Link() {

    //check if FI/FO
    if(from->firstOut == this){
        from->firstOut = nextOut;
    }
    if(from->lastOut == this){
        from->lastOut = previousOut;
    }
    if(to->firstIn == this){
        to->firstIn = nextIn;
    }
    if(to->lastIn == this) {
        to->lastIn = previousIn;
    }

    //Link previousIn to nextIn
    if(previousIn != nullptr){
        if(nextIn == nullptr){
            previousIn->nextIn = nullptr;
        }
        else{
            previousIn->nextIn = nextIn;
        }
    }


    //Link previousOut to nextOut
    if(previousOut != nullptr){
        if(nextOut == nullptr){
            previousOut->nextOut = nullptr;
        }
        else{
            previousOut->nextOut = nextIn;
        }
    }
}

Map::Link *Map::addLink(Node *a, Node *b) {
    return new Map::Link(a,b);
}
void Map::removeLink(Map::Link *a) {
    delete a;
    a = nullptr;

}




//NODES
Map::Node *Map::addNode(std::string name) {
    Map::Node *node = new Map::Node(name);
    return node;
}
bool Map::removeNode(Node *a) {
    if(!a->getAdjacent().empty()){
        cout << "There are still links to " << a->getName() << ". Please remove them before deleting the node" << endl;
        return false;
    }
    delete a;
    a = nullptr;
    return true;

}

Map::Node::Node(string a){
    name = a;
     firstIn = nullptr;
     firstOut = nullptr;
     lastIn = nullptr;
     lastOut = nullptr;
}


vector<Map::Node*> Map::Node::getAdjacent() {
    std::vector<Map::Node*> nodeList;
    if(firstOut != nullptr){
        Map::Link *a = firstOut;
        while(true){
            cout << a->to->getName() << endl;
            nodeList.push_back(a->to);
            if(a->nextOut == nullptr){
                a=nullptr;
                break;
            }
            a = a->nextOut;
        }
    }
    if(firstIn != nullptr){
        Map::Link *b = firstIn;
        while(true){
            cout << b->from->getName() << endl;
            nodeList.push_back(b->from);
            if(b -> nextIn == nullptr) {
                b=nullptr;
                break;
            }
            b = b->nextIn;
        }
    }
    return nodeList;
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
Map::Map(){}

