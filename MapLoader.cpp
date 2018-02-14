//
// Created by luca on 14/02/18.
//

#include "MapLoader.h"
#include "map.h"
#include <fstream>

MapLoader::MapLoader(string path) {
    file=path;
    m = new Map();
}
string MapLoader::slurp(ifstream& in) {
    stringstream sstr;
    sstr << in.rdbuf();
    return sstr.str();
}
bool MapLoader::addNodes(){
    ifstream ifs("test.txt");
    string content = slurp(ifs);
    cout << content << endl;
    return true;
}



