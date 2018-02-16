//
// Created by luca on 14/02/18.
//

#include "MapLoader.h"
#include "map.h"
#include <fstream>
#include <streambuf>

MapLoader::MapLoader(string path, Map *map) {
    m = map;
    ifs.open("../"+path);
//    string mapFile((std::istreambuf_iterator<char>(ifs)),
//                    std::istreambuf_iterator<char>());
    buffer << ifs.rdbuf();
    ifs.close();
}

Map *MapLoader::build() {
    this->separate();
    this->addNodes();
    this->addLinks();
    return m;
}

bool MapLoader::separate() { //gotta keep them separated
    string line;
    bool nodeSection = false;
    bool linkSection = false;
    while(std::getline(buffer, line)){
        if(line == "BEGIN NODES") {
            nodeSection = true;
            continue;
        }
        if(line == "END NODES") {
            nodeSection = false;
            continue;
        }
        if(line == "BEGIN LINKS"){
            linkSection = true;
            continue;
        }
        if(line == "END LINKS")
            break;
        if(nodeSection){
            nodeBuilder << line << endl;
            continue;
        }
        if(linkSection){
            linkBuilder << line << endl;
            continue;
        }
    }
    if (nodeBuilder.str().empty() || linkBuilder.str().empty() || (nodeSection && linkSection)){
        throw new exception;
    }
}

bool MapLoader::addNodes(){
    string line, name, lineS;
    string delimiter = "|";
    vector<string> mods;


    while(getline(nodeBuilder,line)){
        delimiter = "|";
        name = line.substr(0, line.find(delimiter));
        m->addNode(name);
        line.erase(0, line.find(delimiter) + delimiter.length());
        m->setTerrain(name, line.substr(0, line.find(delimiter))); //set terrain
        line.erase(0, line.find(delimiter) + delimiter.length());
        if(line.substr(0, line.find(delimiter)) == "E")
            m->toggleEdge(name);    //make edgy
        line.erase(0, line.find(delimiter) + delimiter.length());
        //remove array brackets
        line.erase(0,1);
        line.erase(line.length()-1);

        delimiter = ",";
        while(true){
            if(line.find(delimiter) == string::npos){
                mods.push_back(line);
                break;
            } //check if there's any other elements left
            mods.push_back(line.substr(0, line.find(delimiter)));
            line.erase(0, line.find(delimiter) + delimiter.length());

        }
        m->setModifiers(name,mods);
    }
    return true;
}

bool MapLoader::addLinks() {
    string line, from, to;
    string delimiter=",";
    
    while(getline(linkBuilder, line)){
        from =  line.substr(0, line.find(":"));
        if(from == "")
            throw new exception;
        line.erase(0, line.find(":") + delimiter.length());
        while(true){
            if(line.find(delimiter) == string::npos){
                to = line;
                m->addLink(from, to);
                break;
            }
            to = line.substr(0, line.find(delimiter));
            m->addLink(from, to);
            line.erase(0, line.find(delimiter) + delimiter.length());


        }
    }
    return true;
}



