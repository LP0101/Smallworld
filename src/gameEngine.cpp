//
// Created by luca on 02/03/18.
//

#include "gameEngine.h"


GameEngine::GameEngine() {
    map = nullptr;
    box = nullptr;
    deck = nullptr;
}

void GameEngine::init() {
    cout << "How many players?" << endl;
    int playerCount;
    cin >> playerCount;
    string mapFile = "Maps/" + to_string(playerCount) + "players.map";
    cout << "Loading ../" + mapFile << endl;
    map = new Map();
    box = new Gamebox();
    map->build(mapFile);
    for (auto const& x : map->getNodes())
{
    if(x.second->getTerrain() == "Mountain"){
        x.second->addscoreMod(box->giveModifier("Mountain"));
    }
}
    for(int i=0;i<playerCount;i++){
        cout << "Player " + to_string(i+1)+ ", please input your name: ";
        string playername;
        cin >> playername;
        players.push_back(new Player(playername,deck,map,box));
    }

}