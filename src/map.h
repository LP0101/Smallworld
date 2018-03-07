//
// Created by Popesco, Luca on 2018-02-05.
//

#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H

#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include "gamebox.h"
using namespace std;


class Map {
private:
    class Node;
    class Link;

public:
    //MAP methods
    Map();
    void printAdjacent(string node);
    void printAdjacentControlled(string node);
    void build(string path);

    //NODE METHODS
    bool addNode(std::string name);
    bool setFaction(std::string node, std::string faction);
    void setTerrain(string node, string type);
    void setModifiers(string node, vector<string> mods);
    void addModifier(string node, string modifier);
    void removeModifier(string node, string modifier);
    vector<string> getModifiers(string node);
    void toggleEdge(string node);
    string getTerrain(string node);
    void setReinforcements(string node, vector<Token*> &);
    int getReinforcements(string node);
    string getFaction(string node);
    void addscoreMod(string node, Modifier* power);
    Modifier* removescoreMod(string node);
    void clearscoreMods(string node);
    vector<Modifier *> getscoreMods(string node);
    std::map<string,Map::Node*> getNodes();
    vector<string> getControlled(string race);

    //LINK METHODS
    bool addLink(string from, string to);
    bool removeLink(string from, string to);
    bool removeNode(string name);



private:
    std::map<string, Node*> nodes;
    std::map<string, Link*> links;


};




class Map::Node{
    friend class Map::Link;
private:
    std::string name, faction, terrain;
    Map::Link *firstIn, *firstOut, *lastIn, *lastOut;
    vector<std::string> modifiers;
    vector<Modifier*> scoreMods;
    vector<Token*> reinforcements;
    bool edge;
public:
    Node(std::string &name);
    Map::Link *getFirstIn();
    Map::Link *getFirstOut();
    Map::Link *getLastOut();
    Map::Link *getLastIn();
    std::string getName();
    string getFaction();
    bool setFaction(std::string fac);
    void setTerrain(string type);
    void setModifiers(vector<string> mods);
    void addscoreMod(Modifier* mod);
    Modifier* removescoreMod();
    void clearscoreMods();
    vector<Modifier *> getscoreMods();
    vector<Map::Node*> getAdjacent();
    vector<Map::Node*> getAdjacentControlled();
    void toggleEdge();
    string getTerrain();
    void setReinforcements(vector<Token*> tokens);
    int getReinforcements();
    void addModifier(string mod);
    void removeModifier(string mod);
    vector<string> getModifiers();

};




class Map::Link{
    friend class Map::Node;
private:
    Map::Node *from, *to;
    Link *previousOut, *previousIn, *nextOut, *nextIn;

public:
    Link(Map::Node *from, Map::Node *to);
    ~Link();
    string getFrom();
    string getTo();
};




#endif //PROJECT_MAP_H
