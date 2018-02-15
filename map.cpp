//
// Created by Popesco, Luca on 2018-02-05.
//

#include "map.h"
#include <iostream>
#include <vector>
#include <map>
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
        this->previousIn = nullptr;
        this->nextIn = nullptr;
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

    string name=a->getName() + "to" + b->getName();



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
    cout << "link destroyed" << endl;
}

bool Map::addLink(string from, string to) {
    Map::Node *a = nodes[from];
    Map::Node *b = nodes[to];
    Map::Link *link =  new Map::Link(a,b);
    links[a->getName() + "to" + b->getName()] = link;
    return true;
}
string Map::Link::getFrom() {return from->getName();};
string Map::Link::getTo() {return to->getName();};
bool Map::removeLink(string x, string y) {
    string link = x + "to" + y;
    Map::Link *a = links[link];
    string from = a->getFrom();
    string to = a->getTo();
    links.erase(from + "to" + to);
    delete a;
    a = nullptr;
    return true;


}




//NODES
bool Map::addNode(std::string name) {
    Map::Node *node = new Map::Node(name);
    nodes[name] = node;
    return true;
}
bool Map::removeNode(string name) {
    Map::Node *a = nodes[name];
    if(!a->getAdjacent().empty()){
        cout << "There are still links to " << a->getName() << ". Please remove them before deleting the node" << endl;
        return false;
    }
    nodes.erase(a->getName());
    delete a;
    a = nullptr;
    return true;

}

Map::Node::Node(string &a){
    name = a;
    firstIn = nullptr;
    firstOut = nullptr;
    lastIn = nullptr;
    lastOut = nullptr;
    faction = "a";
    terrain = "";
    edge = false;
    reinforcements = 0;
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

vector<Map::Node*> Map::Node::getAdjacentControlled() {
    std::vector<Map::Node*> nodeList;
    if(firstOut != nullptr){
        Map::Link *a = firstOut;
        while(true){
            if(a->to->faction==this->faction) {
                cout << a->to->getName() << " Is allied" << endl;
                nodeList.push_back(a->to);
            }
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
            if(b->from->faction==this->faction) {
                cout << b->from->getName() << " Is allied" << endl;
                nodeList.push_back(b->from);
            }
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

bool Map::Node::setFaction(std::string fac) {faction = fac; return true;}
void Map::Node::setTerrain(string type) {terrain = type;}
void Map::Node::setModifiers(vector<string> mods) {modifiers = mods;}
void Map::Node::toggleEdge() {edge = !edge;}

string Map::Node::getTerrain(){
    return terrain;
}




//MAP
Map::Map(){}

void Map::printAdjacent(string node) {
    nodes[node]->getAdjacent();
}
void Map::printAdjacentControlled(string node){
    nodes[node]->getAdjacentControlled();
}

bool Map::setFaction(std::string node, std::string faction){
    return nodes[node]->setFaction(faction);
}
void Map::setModifiers(string node, vector<string> mods) {nodes[node]->setModifiers(mods);}
void Map::setTerrain(string node, string type) {nodes[node]->setTerrain(type);}
void Map::toggleEdge(string node) {nodes[node]->toggleEdge();}

string Map::getTerrain(string node){
    return nodes[node]->getTerrain();
}


