//
// Created by luca on 14/02/18.
//

#ifndef PROJECT_MAPLOADER_H
#define PROJECT_MAPLOADER_H


#include <iostream>
#include "map.h"
#include <fstream>
#include <sstream>

using namespace std;


class MapLoader {
public:
    MapLoader(std::string path);
    Map build();


    Map *m;
    string file;
    bool addNodes();
    bool addLinks();
    string nodeList;
    string linkLink;
    string slurp(ifstream& in);
};


#endif //PROJECT_MAPLOADER_H
