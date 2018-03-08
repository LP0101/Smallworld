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
    firstConquest = false;
    MAX_TURNS = 10;
    turns = 0;
    map = new Map();
    box = new Gamebox();
    deck = new Factions("Gameconfig/Races","Gameconfig/Powers",box);
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



void GameEngine::gameLoop() {
    while(turns < MAX_TURNS){
        for(auto currentPlayer : players){
            cout << "Current player is: " << currentPlayer->getName() << endl;
            prePhase(currentPlayer);
            mainPhase(currentPlayer);
            firstConquest = false; //MOVE THIS
        }
    }

}

bool GameEngine::parse(string command, Player * p) {
    if (command == "exit"){
        exit(0);
    }
    if(command == "showraces") {
        for(auto faction : deck->topDecks()){
           cout << faction << endl;
        }
        return true;
    }
    vector<string> commands = split(command);
    if(commands[0] == "conquer"){
      return conquer(commands,p);
    }
    cout << "Invalid command" << endl;
    return true;

}

bool GameEngine::conquer(vector<string> commands, Player *p) {
    int cost = 0;
    cost +=2;
    cost += map->getReinforcements(commands[1]);
    for(auto mod : map->getscoreMods(commands[1])){
        if(mod->getEffect() == 1)
            cost+=1;
        else{
            cout << "Cannot capture this node!" << endl;
            return true;
        }
    }
    if(map->getTerrain(commands[1]) == "Water" && p->getPrimary()->getPower()->getName() != "Seafaring"){
        cout << "Not seafaring, cannot capture water!" << endl;
        return true;
    }
//    vector<string> controlled = this->map->getControlled(p->getPrimary()->getRace()->getName());
    //check if first conquest
    if(firstConquest){
        if(!map->isEdge(commands[1])){
           cout << "First conquest must be on an edge!" << endl;
            return true;
        }
    }
    else{
        if(!map->isAdjacentControl(commands[1],p->getPrimary()->getRace()->getName())){
            cout << "This territory is not adjacent to your active race" << endl;
            return true;
        }
    }
    if(stoi(commands[2]) < cost){
        cout << "Not enough units, try again or use finalConquest" << endl;
        return true;
    }
    p->conquers(commands[1],stoi(commands[2]));
    cout << commands[1] << " belongs to " << p->getName() << " with " << map->getReinforcements(commands[1]) << " " << map->getFaction(commands[1]) << " tokens" << endl;
    firstConquest = false;
    cout << "You have " << p->getTokens() << " Tokens left" << endl;
    return true;

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
        firstConquest = true;
    }
    bool cont = true;
    while(cont) {
        string command;
        cout << ">> ";
        cin >> ws;
        getline(cin,command);
        cont = parse(command, p);
    }
}



vector<string> GameEngine::split(string s){
    std::stringstream ss(s);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vstrings(begin, end);
//    std::copy(vstrings.begin(), vstrings.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
    return vstrings;
}
