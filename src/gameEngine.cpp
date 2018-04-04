//
// Created by luca on 02/03/18.
//

#include "gameEngine.h"


GameEngine::GameEngine() {
    map = nullptr;
    box = nullptr;
    deck = nullptr;
    didConquer = false;
    pillaged = 0;
    conquered = 0;
    turns = 1;
    phaseSubject = new PhaseSubject();
    phaseObserver = new PhaseObserver(phaseSubject);
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



    string mapFile;
    int playerCount;
    int acceptedValues[] = {2,3,4,5};

    while(true) { //will only proceded when input is correct
        cout << "How many players?" << endl;
        cin >> ws;
        cin >> playerCount;
        if(cin.fail()){
            cin.clear(); // clears error flags
            cin.ignore(999,'\n'); // the first parameter is just some arbitrarily large value, the second param being the character to ignore till
            cout << "Please enter a valid number" << endl;
            continue;
        }

        mapFile = "Maps/" + to_string(playerCount) + "players.map";
        cout << "Loading ../" + mapFile << endl << endl;
        if(std::find(std::begin(acceptedValues), std::end(acceptedValues), playerCount) != std::end(acceptedValues))
            break;
        else
            cout << "Map error, try again" << endl;
    }
    firstConquest = false;
    //sets max number of turns
    if(playerCount==2 || playerCount==3)
        MAX_TURNS=10;
    if(playerCount==4)
        MAX_TURNS=9;
    if(playerCount==5)
        MAX_TURNS=8;
    turns = 1;
    map = new Map();
    box = new Gamebox();
    deck = new Factions("Gameconfig/Races","Gameconfig/Powers",box);
    map->build(mapFile);
    for (auto const& x : map->getNodes())
{
    if(x.second->getTerrain() == "Mountain"){
        x.second->addscoreMod(box->giveModifier("Mountain"));
    }
    vector<string> mods = x.second->getModifiers();
    if(std::find(mods.begin(), mods.end(), "LostTribes") != mods.end()){
        map->setReinforcements(x.second->getName(),box->giveTokens("Lost Tribes",1));
        map->setFaction(x.second->getName(),"Lost Tribes");
    }
}

    for(int i=0;i<playerCount;i++){
        cout << "Player " + to_string(i+1)+ ", please input your name: ";
        string playername;
        cin >> playername;
        players.push_back(new Player(playername,deck,map,box));
    }
    for(auto player : players){
        for(int i=0;i<5;i++){
            player->addVp(box->giveCoins(1));
        }
    }
    statsSubject = new StatsSubject(map);
    statsSubject->setPlayers(players);
    statsObserver = new undecoratedObserver(statsSubject);
//    statsSubject->Detach(statsObserver);
//    statsObserver = new BaseObserverDecorator(statsObserver);
//    statsSubject->Attach(statsObserver);
//    statsObserver = new ConquestDecorator(statsObserver,statsSubject);
//    statsSubject->Attach(statsObserver);
//    statsSubject->Detach(statsObserver);
//    statsObserver=new HandDecorator(statsObserver,statsSubject);
//    statsSubject->Attach(statsObserver);
//    statsSubject->Detach(statsObserver);
//    statsObserver = new CoinsDecorator(statsObserver, statsSubject);
//    statsSubject->Attach(statsObserver);
//    cout << statsObserver->getUnder()->getType() << endl;
//    removeDecorator("conquest");
}

void GameEngine::gameLoop() {
    while(turns < MAX_TURNS+1){
        cout << "It is turn " << turns << " out of " << MAX_TURNS << endl;
        statsSubject->setTurn(turns);
        if(showDecoratorOptions){
            setDecorators();
            removeDecorators();
        }
        for(auto currentPlayer : players){
            cout << "Current player is: " << currentPlayer->getName() << endl;
            phaseSubject->setPlayer(currentPlayer->getName());
            prePhase(currentPlayer);
            pillaged=0;
            mainPhase(currentPlayer);
            reinforcePhase(currentPlayer);
            scorePhase(currentPlayer);
            endPhase(currentPlayer);
            firstConquest = false; //MOVE THIS
            lostZone.clear();      //MOVE THIS
        }

        turns++;
    }
    int maxscore = 0;
    string winner;
    for(auto player : players){
        if(player->getVp() > maxscore){
            maxscore = player->getVp();
            winner = player->getName();
        }
    }
    cout << "The winner is " << winner << " with " << maxscore << " points!";

}

bool GameEngine::parse(string command, Player * p) {
    if (command == "exit"){
        exit(0);
    }
    if(command == "help"){
        help();
        return true;
    }
    if(command == "strategize"){
        bool rein=false;
        if(currentPhase == "retreat" || currentPhase == "reinforce")
            rein = true;
        else
            rein = false;
        p->Strategize(rein,didConquer);
        return true;
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
    if(commands[0] == "skip")
        return false;
    if(commands[0] == "abandon")
        return abandon(commands, p);
    cout << "Invalid command" << endl;
    return true;

}

//Uses PhaseObserver
bool GameEngine::conquer(vector<string> commands, Player *p) {
    if(currentPhase != "main"){
        cout << "Cannot conquer right now" << endl;
        return true;
    }
    if(!map->isNode(commands[1])){
        cout << "Node not found!" <<endl;
        return true;
    }
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

    //check for pillaging/orcs
    if(map->getFaction(commands[1]) != "")
        pillaged+=1;

    //check which player loses
    if(map->getPlayer(commands[1]) != ""){
        for(auto player : players){
            if(player->getName() == map->getPlayer(commands[1])){
                if(player->getPrimary()->getRace()->getName() == map->getFaction(commands[1])) {
                    if(std::find(lostZone.begin(),lostZone.end(), player) == lostZone.end())
                    lostZone.push_back(player);
                }
                player->loses(commands[1]);
            }
        }
    }
    if(isFinal)
        cost = p->getTokens();
    p->conquers(commands[1],cost);
    phaseSubject->setAction("conquers "+commands[1]+" with " + to_string(map->getReinforcements(commands[1])) + " " + map->getFaction(commands[1]) + " tokens");
//    cout << commands[1] << " belongs to " << p->getName() << " with " << map->getReinforcements(commands[1]) << " " << map->getFaction(commands[1]) << " tokens" << endl;
    phaseSubject->Notify();
    firstConquest = false;
    didConquer = true;
    cout << "You have " << p->getTokens() << " Tokens left" << endl;
    conquered++;
    if(p->getTokens() == 0)
        isFinal = true;
    return !isFinal;
}

//Uses StateObserver
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
        if(!map->isNode(commands[2])){
            cout << "Node not found!" << endl;
            return true;
        }
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
    else if(commands[1] == "info"){
        statsSubject->Notify();
        return true;
    }
    else{
        cout << "Invalid command" << endl;
        return true;
    }
}

//Uses PhaseObserver
bool GameEngine::decline(Player * p) {
    if(currentPhase != "main"){
        cout << "Cannot go into decline right now!" << endl;
        return true;
    }
    if(didConquer){
        cout << "Cannot go into decline after conquering!" << endl;
             return true;
    }
    p->decline();
    phaseSubject->setAction("goes into decline");
    phaseSubject->Notify();
    return false;
}

//Uses PhaseObserver
bool GameEngine::reinforce(vector<string> commands, Player *p) {
    if(!(currentPhase == "reinforce" || currentPhase == "retreat")){
        cout << "Cannot reinforce right now!" << endl;
        return true;
    }
    if(!map->isNode(commands[1])){
        cout << "Node not found!"<<endl;
        return true;
    }
    if(commands[2] == ""){
        cout << "Please indicate how many units to reinforce with!" << endl;
        return true;
    }
    if(map->getFaction(commands[1]) != p->getPrimary()->getRace()->getName()){
        cout << "You can only reinforce your primary faction's nodes!" << endl;
        return true;
    }

    if(p->getTokens() < stoi(commands[2])){
        cout << "Not enough tokens to do this" << endl;
        return true;
    }
    p->reinforce(commands[1],stoi(commands[2]));

//    cout << "You reinforced " << commands[1] << " with " << commands[2] << " tokens" << endl;
    phaseSubject->setAction("has reinforced " + commands[1] + " with " + commands[2] + " tokens");
    phaseSubject->Notify();
    cout << "You have " << p->getTokens() << " tokens remaining"<<endl;
    return(p->getTokens() != 0); //returns true if no more tokens

}

//Uses PhaseObserver
bool GameEngine::abandon(vector<string> commands, Player *p) {
    if(currentPhase != "reinforce"){
        cout << "Cannot abandon right now!" << endl;
        return true;
    }
    if(!map->isNode(commands[1])){
        cout << "Node not found!" << endl;
        return true;
    }
    if(map->getFaction(commands[1]) != p->getPrimary()->getRace()->getName()){
        cout << "You can only abandon your primary race" << endl;
        return true;
    }
    p->abandon(commands[1]);
    phaseSubject->setAction("abandonned " + commands[1]);
    phaseSubject->Notify();
    return true;
}

void GameEngine::prePhase(Player *p) {
    int choice;
    while(true) {
        cout << "Choose a strategy for this turn\n1. Random\n2. Moderate\n3. Defensive\n4. Aggressive" << endl;
        cin >> ws;
        cin >> choice;
        if (cin.fail()) {
            cin.clear(); // clears error flags
            cin.ignore(999,
                       '\n'); // the first parameter is just some arbitrarily large value, the second param being the character to ignore till
            cout << "Please enter a valid number" << endl;
            continue;
        }
        if(choice > 4 || choice < 1){
            cout << "Enter a valid number" << endl;
            continue;
        }
        break;
    }
    switch(choice){
        case 1:{
            p->setStrategy(new RandomStrategy(p));
        }break;
        case 2:{
            p->setStrategy(new ModerateStrategy(p));
        }break;
        case 3:{
            p->setStrategy(new DefensiveStrategy(p));
        }break;
        case 4:{
            p->setStrategy(new AggressiveStrategy(p));
        }break;
        default: {}
    }
}

void GameEngine::mainPhase(Player *p) {
    currentPhase = "main";
    conquered = 0;
    while(p->getPrimary() == nullptr || p->getPrimary()->getDecline()){
        int choice;
        cout << "Choose a faction" << endl;
        parse("show races", nullptr);
        cin >> ws;
        cin >> choice;
        if(cin.fail()){
            cin.clear(); // clears error flags
            cin.ignore(999,'\n'); // the first parameter is just some arbitrarily large value, the second param being the character to ignore till
            cout << "Please enter a valid number" << endl;
            continue;
        }
        if(choice < 0 || choice > 5){
            cout << "Please enter a valid number" << endl;
            continue;
        }
        p->picks_race(choice);
        firstConquest = true;
    }
    cout << "========== Conquer Phase ==========" << endl << endl;
    p->prepare();
    didConquer = false;
    bool cont = true;
    while(cont) {
        string command;
        cout << ">> ";
        cin >> ws;
        getline(cin,command);
        cont = parse(command, p);
    }
    phaseSubject->setAction("has conquered " + to_string(conquered) +  " zones in his turn!");
    phaseSubject->Notify();
//    cout << "Entering reinforce phase" << endl;
}

void GameEngine::reinforcePhase(Player *p) {
    currentPhase="reinforce";
    cout << "========== Reinforce Phase ==========" << endl;
    if(p->getPrimary() == nullptr || p->getPrimary()->getDecline()){
        cout << "In decline, can't reinforce" << endl;
        return;
    }
    p->prepare();
    cout << "You have " << p->getTokens() << " tokens to reinforce with" << endl;
    bool cont = true;
    while(cont){
        string command;
        cout << ">> ";
        cin >> ws;
        getline(cin,command);
        cont = parse(command, p);
    }

}

void GameEngine::retreatPhase(Player *p) {
    currentPhase="retreat";
    cout << "========== " << "Reinforce Phase" << "==========";
    cout << p->getName() <<", you have " << p->getTokens() << " tokens to reinforce with" << endl;
    bool cont = true;
    if(p->getTokens() == 0){
        cout << "skipping retreat phase" << endl;
        cont = false;
    }
    while(cont){
        string command;
        cout << ">> ";
        cin >> ws;
        getline(cin,command);
        cont = parse(command, p);
    }
}

void GameEngine::scorePhase(Player *p) {
    currentPhase="score";
    phaseSubject->setAction("scored"+to_string(p->scores(pillaged)) + " points!");
    phaseSubject->Notify();
//    cout << p->getName() <<" just scored " << p->scores(pillaged) << " points!" << endl;
}
void GameEngine::endPhase(Player *p) {
   for(auto lost : lostZone){
       retreatPhase(lost);
   }
}

void GameEngine::help() {
    cout << "The available commands are: " << endl << endl;
    cout << "conquer <nodename>: conquers a node. Will roll if you don't have enough" << endl;
    cout << "reinforce <nodename> <number>: reinforce a node with 'n' units" << endl;
    cout << "decline: go into decline" << endl;
    cout << "show <vp>/<tokens/<node>/<races>: show given information. Must specifiy a name after 'node'" <<endl;
}

vector<string> GameEngine::split(string s){
    std::stringstream ss(s);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vstrings(begin, end);
//    std::copy(vstrings.begin(), vstrings.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
    return vstrings;
}

bool GameEngine::removeDecorator(string decorator) {
    StatsObserver* temp = statsObserver;
    StatsObserver* onTop = nullptr;
    while(temp->getType() != "undecorated"){
        if(temp->getType() == decorator){
            if(onTop==nullptr){
                statsSubject->Detach(statsObserver);
                statsObserver = temp->getUnder();
                statsSubject->Attach(statsObserver);
//                delete temp;
                return true;
            }
            else{
                onTop->setUnder(temp->getUnder());
//                statsObserver = temp->getUnder();
//                delete temp;
                return true;
            }
        }
        else{
            onTop = temp;
            temp = temp->getUnder();
        }
    }
    cout << "Not found!" << endl;
    return false;
}
bool GameEngine::setDecorators() {
    bool repeat= true;
    while(repeat) { //will only proceded when input is correct
        cout << "1: Conquest\n2: Hands\n3: Coins\n0: Exit\n";
        int decorator;
        cout << "Which Decorator would you like to attach?" << endl;
        cin >> ws;
        cin >> decorator;
        if(cin.fail()){
            cin.clear(); // clears error flags
            cin.ignore(999,'\n'); // the first parameter is just some arbitrarily large value, the second param being the character to ignore till
            cout << "Please enter a valid number" << endl;
            continue;
        }
        switch(decorator){
            case 1:{
                if(decorators[0]){
                    cout << "Already attached!" << endl;
                    break;
                }
                statsSubject->Detach(statsObserver);
                statsObserver=new ConquestDecorator(statsObserver,statsSubject);
                statsSubject->Attach(statsObserver);
                decorators[0]=true;
            } break;
            case 2:{
                if(decorators[1]){
                    cout << "Already attached!" << endl;
                    break;
                }
                statsSubject->Detach(statsObserver);
                statsObserver = new HandDecorator(statsObserver,statsSubject);
                statsSubject->Attach(statsObserver);
                decorators[1]=true;
            } break;
            case 3:{
                if(decorators[2]){
                    cout << "Already attached!" << endl;
                    break;
                }
                statsSubject->Detach(statsObserver);
                statsObserver = new CoinsDecorator(statsObserver,statsSubject);
                statsSubject->Attach(statsObserver);
                decorators[2] = true;
            } break;
            case 0:{
                repeat = false;
            }break;
        }
    }
}
bool GameEngine::removeDecorators(){
    bool repeat= true;
    while(repeat) { //will only proceded when input is correct
        cout << "1: Conquest\n2: Hands\n3: Coins\n0: Exit\n";
        int decorator;
        cout << "Which Decorator would you like to remove?" << endl;
        cin >> ws;
        cin >> decorator;
        if(cin.fail()){
            cin.clear(); // clears error flags
            cin.ignore(999,'\n'); // the first parameter is just some arbitrarily large value, the second param being the character to ignore till
            cout << "Please enter a valid number" << endl;
            continue;
        }
        switch(decorator){
            case 1:{
                removeDecorator("conquest");
                decorators[0] = false;
            } break;
            case 2:{
                removeDecorator("hand");
                decorators[1]=false;
            } break;
            case 3:{
                removeDecorator("coins");
                decorators[2]=false;
            } break;
            case 0:{
                repeat = false;
            }break;
        }

    }
    string input;
    cout << "Would you like to be shown this prompt again?" << endl;
    while(true) {
        cin >> ws;
        cin >> input;
        if(input == "y")
            break;
        if(input =="n"){
            showDecoratorOptions = false;
            break;
        }
    }
}
