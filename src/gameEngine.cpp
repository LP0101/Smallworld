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
    MAX_TURNS = 10;
    turns = 0;
    map = new Map();
    box = new Gamebox();
    deck = new Factions("Gameconfig/Races","Gameconfig/Powers",box);
    map->build(mapFile);
    for (auto const& x : map->getNodes())
{
    if(x.second->getTerrain() == "Mountain"){
//        cout << "Mountain found!" << endl;
        x.second->addscoreMod(box->giveModifier("Mountain"));
    }
}
//    for(Modifier * mod : map->getscoreMods("M1")){
//        cout << mod->getName() << endl;
//    }
    for(int i=0;i<playerCount;i++){
        cout << "Player " + to_string(i+1)+ ", please input your name: ";
        string playername;
        cin >> playername;
        players.push_back(new Player(playername,deck,map,box));
    }
}

void GameEngine::gameLoop() {
    while(turns < MAX_TURNS){
        for(auto currentPlayer : players){
            cout << "Current player is: " << currentPlayer->getName() << endl;
            prePhase(currentPlayer);
            mainPhase(currentPlayer);
        }
    }

}

bool GameEngine::parse(string command, Player * p) {
    if(command == "showraces") {
        for(auto faction : deck->topDecks()){
           cout << faction << endl;
        }
        return true;
    }
    vector<string> commands = split(command);
    if(commands[0] == "conquer"){
        p->conquers(commands[1],stoi(commands[2]));
        cout << commands[1] << " belongs to " << p->getName() << " with " << map->getReinforcements(commands[1]) << " " << map->getFaction(commands[1]) << " tokens" << endl;
        return true;
    }

}

void GameEngine::prePhase(Player *p) {
    for(auto player : players){
    }
}

void GameEngine::mainPhase(Player *p) {
    if(p->getPrimary() == nullptr || p->getPrimary()->getDecline()){
        int choice;
        cout << "Choose a faction" << endl;
        parse("showraces", nullptr);
        cin >> choice;
        p->picks_race(choice);
    }
    bool cont = true;
    while(cont) {
        string command;
        cout << ">> ";
        cin.ignore();
        getline(cin,command);
        cont = parse(command, p);
    }
}

vector<string> GameEngine::split(string s){
    std::stringstream ss(s);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vstrings(begin, end);
    std::copy(vstrings.begin(), vstrings.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
    return vstrings;
}