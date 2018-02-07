//
// Created by Popesco, Luca on 2018-02-05.
//

#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H

#include <vector>
#include <iostream>
#include <map>
using namespace std;


class Map {
protected:
    class Node;
    class Link;

public:
    //MAP methods
    Map();

    //NODE METHODS
    Link* getFirstIn(Node *node);
    Link* getFirstOut(Node *node);
    bool addNode(std::string name);

    //LINK METHODS
    bool addLink(string from, string to);
    bool removeLink(string from, string to);
    bool removeNode(string name);
    void printAdjacent(string node);


private:
    std::map<string, Node*> nodes;
    std::map<string, Link*> links;


};




class Map::Node{
    friend class Map::Link;
private:
    std::string name;
    Map::Link *firstIn, *firstOut, *lastIn, *lastOut;
public:
    Node(std::string name);
    Map::Link *getFirstIn();
    Map::Link *getFirstOut();
    Map::Link *getLastOut();
    Map::Link *getLastIn();
    std::string getName();
    vector<Map::Node*> getAdjacent();

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
