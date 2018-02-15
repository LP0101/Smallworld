//
// Created by luca on 14/02/18.
//

#include "MapLoader.h"
#include "map.h"
#include <fstream>
#include <streambuf>

MapLoader::MapLoader(string path) {
    file=path;
    m = new Map();
}

bool MapLoader::addNodes(){
    ifstream ifs("test.txt");
    std::string content((std::istreambuf_iterator<char>(ifs)),
                    std::istreambuf_iterator<char>());
    cout << content << endl;
    return true;
}



