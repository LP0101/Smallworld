//
// Created by luca on 02/03/18.
//

#include "gameEngine.h"


GameEngine::GameEngine() {
    map = nullptr;
    box = nullptr;
    deck = nullptr;
    didConquer = false;
}

void GameEngine::init() {
    if(getenv("TERM") != NULL){
        std::system("clear");
    }
    cout << " ________  ___  ___   _      _       _    _  ___________ _    ______ \n"
            "/  ___|  \\/  | / _ \\ | |    | |     | |  | ||  _  | ___ \\ |   |  _  \\\n"
            "\\ `--.| .  . |/ /_\\ \\| |    | |     | |  | || | | | |_/ / |   | | | |\n"
            " `--. \\ |\\/| ||  _  || |    | |     | |/\\| || | | |    /| |   | | | |\n"
            "/\\__/ / |  | || | | || |____| |____ \\  /\\  /\\ \\_/ / |\\ \\| |___| |/ / \n"
            "\\____/\\_|  |_/\\_| |_/\\_____/\\_____/  \\/  \\/  \\___/\\_| \\_\\_____/___/  \n"
            "                                                                    "<< endl << endl;


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
        cout << "It is turn " << turns << " out of " << MAX_TURNS << endl;
        for(auto currentPlayer : players){
            cout << "Current player is: " << currentPlayer->getName() << endl;
            prePhase(currentPlayer);
            mainPhase(currentPlayer);
            firstConquest = false; //MOVE THIS
            lostZone.clear();      //MOVE THIS
        }
    }

}

bool GameEngine::parse(string command, Player * p) {
    if (command == "exit"){
        exit(0);
    }
    vector<string> commands = split(command);
    if(commands[0] == "conquer"){
      return conquer(commands,p);
    }
    if(commands[0] == "show"){
        return show(commands,p);
    }
    if(commands[0] == "decline"){
        return decline(p);
    }
    if(commands[0] == "reinforce"){
        return reinforce(commands,p);
    }
    cout << "Invalid command" << endl;
    return true;

}

bool GameEngine::conquer(vector<string> commands, Player *p) {
    bool isFinal = false;
//    if(commands.size() == 4){
//        if(commands[3] == "final")
//            isFinal = true;
//        else{
//            cout << "Invalid command!" << endl;
//            return true;
//        }
//    }
    if(p->getTokens() == 0){
        cout << "You've used all your tokens!" << endl;
        return false;
    }
//    if(stoi(commands[2]) > p->getTokens() && !isFinal){
//        cout << "You do not have enough tokens for this. Use conquer <Node> <tokens> final instead!" << endl;
//        return true;
//    }
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
//    if(stoi(commands[2]) < cost && !isFinal){
//        cout << "Not enough units, try again or use conquer <Node> <tokens> final" << endl;
//        return true;
//    }else if(isFinal){
//        if(stoi(commands[2]) != p->getTokens()){
//            cout << "Can only final conquest with your last tokens" << endl;
//            return true;
//        }
//        cout << "You need to roll a " << cost - stoi(commands[2]) << endl;
//        int roll = p->roll();
//        cout << "You rolled " << roll << endl;
//        int realValue = roll + stoi(commands[2]);
//        if(realValue < cost){
//            cout << "Proceeding to reinforcement stage" << endl;
//            return false;
//        }
//        else{
//            cout << "You did it!" << endl;
//        }
//    }
    if(cost > p->getTokens()){
        isFinal = true;
        cout << "You need to roll a " << cost - p->getTokens() << endl;
        int roll = p->roll();
        cout << "You rolled " << roll << endl;
        int realValue = roll + p->getTokens();
        if(realValue < cost){
            cout << "Proceeding to reinforcement stage" << endl;
            return false;
        } else
            cout << "You did it!" << endl;
    }

    //check which player loses
    if(map->getPlayer(commands[1]) != ""){
        for(auto player : players){
            if(player->getName() == map->getPlayer(commands[1])){
                player->loses(commands[1]);
                lostZone.push_back(player);
            }
        }
    }
    if(isFinal)
        cost = p->getTokens();
    p->conquers(commands[1],cost);
    cout << commands[1] << " belongs to " << p->getName() << " with " << map->getReinforcements(commands[1]) << " " << map->getFaction(commands[1]) << " tokens" << endl;
    firstConquest = false;
    didConquer = true;
    cout << "You have " << p->getTokens() << " Tokens left" << endl;
    if(p->getTokens() == 0)
        isFinal = true;
    return !isFinal;
}

bool GameEngine::show(vector<string> commands, Player *p) {
    if (commands[1] == "races"){
        for(auto faction : deck->topDecks()){
            cout << faction << endl;
        }
        return true;
    }
    else if ( commands[1] == "vp"){
        cout << p->getVp() << endl;
        return true;
    }
    else if(commands[1] == "tokens"){
        cout << p->getTokens() << " " << p->getPrimary()->getRace()->getName() << " tokens" << endl;
        return true;
    }
    else if(commands[1] == "node"){
        string node = commands[2];
        string terrain = map->getTerrain(node);
        string modifiers;
        string scoremods;
        string race = map->getFaction(node);
        string player = map->getPlayer(node);
        int tokens = map->getReinforcements(node);

        for(auto mod : map->getModifiers(node)){
            if(modifiers == "")
                modifiers+=mod;
            else{
                modifiers+=", ";
                modifiers+=mod;
            }

        }
        for(auto mod : map->getscoreMods(node)){
            if(modifiers == "")
                scoremods+=mod->getName();
            else{
                scoremods+=", ";
                scoremods+=mod->getName();
            }
        }

        cout << "Node " << node << ":\n" << "Terrain: " << terrain << "\nModifiers: " << modifiers << "\nScore Modifiers: " << scoremods << "\nRace: " << race << "\nPlayer: " << player << "\nReinforcements: " << tokens << endl;
        return true;

    }
    else if(commands[1] == "player"){
        string name = commands[2];
        Player * target;
        for(auto player : players){
            if(player->getName() == name) {
                target = player;
                break;
            }
        }
        if(target == nullptr){
            cout << "Player not found" <<endl;
            return true;
        }
        string primary="";
        string secondary="";
        if(target->getPrimary() != nullptr){
            primary = target->getPrimary()->toString();
        }
        if(target->getSecondary() != nullptr){
            secondary = target->getSecondary()->toString();
        }
        cout << name << ":\nPrimary: " << primary <<"\nSecondary: " << secondary << endl;
        return true;
    }
    else{
        cout << "Invalid command" << endl;
        return true;
    }
}

bool GameEngine::decline(Player * p) {
    if(didConquer){
        cout << "Cannot go into decline after conquering!" << endl;
             return true;
    }
    p->decline();
    return false;
}

bool GameEngine::reinforce(vector<string> commands, Player *p) {

}

void GameEngine::prePhase(Player *p) {
    for(auto player : players){
    }
}

void GameEngine::mainPhase(Player *p) {
    if(p->getPrimary() == nullptr || p->getPrimary()->getDecline()){
        int choice;
        cout << "Choose a faction" << endl;
        parse("show races", nullptr);
        cin >> choice;
        p->picks_race(choice);
        firstConquest = true;
    }
    didConquer = false;
    bool cont = true;
    while(cont) {
        string command;
        cout << ">> ";
        cin >> ws;
        getline(cin,command);
        cont = parse(command, p);
    }
}

void GameEngine::reinforcePhase(Player *p) {
    if(p->getPrimary() == nullptr || p->getPrimary()->getDecline()){
        cout << "In decline, can't reinforce" << endl;
        return;
    }
    p->prepare();
    bool cont = true;
    while(cont){
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
