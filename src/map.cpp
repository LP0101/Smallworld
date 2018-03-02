//
// Created by Popesco, Luca on 2018-02-05.
//

#include "map.h"
#include "MapLoader.h"
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
    return true;


}




//NODES
//Nodes represent every "zone" on the smallworld map. They contain its entire state, including the race controlling it, the modifiers, and the faction power
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
void Map::Node::addModifier(string mod){modifiers.push_back(mod);}
void Map::Node::removeModifier(string mod) {modifiers.erase( std::remove(modifiers.begin(), modifiers.end(), std::string(mod)), modifiers.end() );}
vector<string> Map::Node::getModifiers() {return modifiers;}


string Map::Node::getTerrain(){
    return terrain;
}
void Map::Node::setReinforcements(vector<Token*> tokens) {
    reinforcements.clear();
    for(auto token : tokens){
        reinforcements.push_back(token);
    }
}
int Map::Node::getReinforcements() {return reinforcements.size();}
string Map::Node::getFaction() {return faction;}
void Map::Node::addscoreMod(Modifier * power) {scoreMods.push_back(power);}
Modifier* Map::Node::removescoreMod() {
    Modifier * temp = nullptr;
    for(auto mod : scoreMods){
        if(mod->getName() != "Mountain"){
            temp = mod;
            scoreMods.erase(find(scoreMods.begin(),scoreMods.end(),mod));
            break;
        }
    }
    return temp;
}
void Map::Node::clearscoreMods() {scoreMods.clear();}
vector<string> Map::Node::getscoreMods() {
    vector<string> temp;
    for(auto mod : scoreMods)
        temp.push_back(mod->getName());
    return temp;
}

std::map<string,Map::Node*> Map::getNodes() {return nodes;}



//MAP
//The map itself is what is exposed to other classes, thus encapsulating all node and link classes
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
string Map::getFaction(string node) {return nodes[node]->getFaction();}
void Map::setModifiers(string node, vector<string> mods) {nodes[node]->setModifiers(mods);}
void Map::setTerrain(string node, string type) {nodes[node]->setTerrain(type);}
void Map::toggleEdge(string node) {nodes[node]->toggleEdge();}
void Map::setReinforcements(string node, vector<Token*> &tokens) {nodes[node]->setReinforcements(tokens);}
int Map::getReinforcements(string node) {nodes[node]->getReinforcements();}

string Map::getTerrain(string node){
    return nodes[node]->getTerrain();
}

void Map::build(string path) {
    MapLoader loader = MapLoader(path, this);
    loader.build();
}
void Map::addModifier(string node, string modifier) {
    nodes[node]->addModifier(modifier);
}
void Map::removeModifier(string node, string modifier) {
    nodes[node]->removeModifier(modifier);
}
vector<string> Map::getModifiers(string node){return nodes[node]->getModifiers();}

void Map::addscoreMod(string node, Modifier* mod) {nodes[node]->addscoreMod(mod);}
Modifier* Map::removescoreMod(string node) { return nodes[node]->removescoreMod();}
void Map::clearscoreMods(string node) {nodes[node]->clearscoreMods();}
vector<string> Map::getscoreMods(string node) {return nodes[node]->getscoreMods();}

