//
// Created by luca on 14/02/18.
//

#ifndef PROJECT_MAPLOADER_H
#define PROJECT_MAPLOADER_H


#include <iostream>
#include "map.h"

using namespace std;

class MapLoader {
public:
    MapLoader(string path);
    map build();

private:
    map m;
    string file;
    bool addNodes();
    bool addLinks();



};


#endif //PROJECT_MAPLOADER_H
