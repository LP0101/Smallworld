//
// Created by Popesco, Luca on 2018-02-05.
//

#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H

#include <iostream>
using namespace std;


class Map {
public:
    class Node;

    class Link;

    //MAP methods
    Map();

    //NODE METHODS
    Link* getFirstIn(Node *node);
    Link* getFirstOut(Node *node);
    Node *addNode(std::string name);
    bool removeLink(Node *from, Node *to);
    bool removeNode(Node *rip);

    //LINK METHODS
    void addLink(Node *a, Node *b);

private:
    Node *seed;

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
    void getAdjacent();

};




class Map::Link{
    friend class Map::Node;
private:
    Map::Node *from, *to;
    Link *previousOut, *previousIn, *nextOut, *nextIn;

public:
    Link(Map::Node *from, Map::Node *to);
};




#endif //PROJECT_MAP_H
