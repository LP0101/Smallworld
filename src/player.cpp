//
// Created by luca on 15/02/18.
//

#include "player.h"

Player::Player(string n, Factions *f, Map *m, Gamebox *g){
    name = n;
    primary = nullptr;
    secondary = nullptr;
    spirit = nullptr;
    deck = f;
    map = m;
    dice = new rDice();
    box = g;
    summarySheet = "Rules and stuff";

    //TEST FUNCTION IGNORE
//    for(int i=0; i<20;i++){
//        oneP.push_back(new vCoin(1));
//    }
//    powerMods.push_back(new Modifier("Dragon",2));
}
//picks a race, paying the appropriate price for it. Also increases the player's victory points by the race's value
//Moves the player's primary race to secondary, and gives the secondary race back to the deck.
//If the secondary race has the "Spirit" power, it is instead moved to a third spirit slot.
void Player::picks_race(int i) {
    if(oneP.size()<i)
        throw new exception;
    vector<vCoin*> payment;
    for(int j=0;j<i;j++){
        payment.push_back(oneP[0]);
        oneP.erase(oneP.begin());
    }
    Faction *choice = deck->take(i,payment);
    if(primary == nullptr) {
        primary = choice;
        primaryTokens.clear();
        vector<Token*> tokens = box->giveTokens(primary->getRace()->getName(),primary->getTokens());
        for(auto token : tokens){
           primaryTokens.push_back(token);
        }
    }
    else{
        if(secondary == nullptr){
            secondary = primary;
            primary = choice;
        }
        else{
            if(secondary->getPower()->getName() == "spirit"){
                spirit = secondary;
                secondary = primary;
                primary = choice;
            }
            else{
                deck->giveBack(secondary);
                secondary=primary;
                primary=choice;
            }
        }
    }
    for(auto coin : box->transfer()){
        oneP.push_back(coin);
    }
}
//sets a node to the player's race and adds the given number of tokens to that node. Also removes that many tokens from the player's primary race
void Player::conquers(string node,int i) {
    map->setFaction(node,primary->getRace()->getName());
    vector<Token*> temp;
    for(int j=0;j<i;j++){
        temp.push_back(primaryTokens[i]);
    }
    for(int j=0;j<i;j++){
        primaryTokens.erase(primaryTokens.begin());
    }
    map->clearReinforcements(node);
    map->setReinforcements(node,temp);
    map->setPlayer(node,this->name);

    nodes.push_back(node);
}

//adds player's tokens to a node
void Player::reinforce(string node, int i) {
    vector<Token *> temp;
    for(int j = 0;j<i;j++){
       temp.push_back(primaryTokens[j]);
    }
    for(int j = 0;j<i;j++){
        primaryTokens.erase(primaryTokens.begin());
    }
    map->addReinforcements(node,temp);
}

//Invoked when a player loses a node. If the controlling race of the token is equal to the player's primary race, the tokens minus 1 are returned.
void Player::loses(string node) {
    if(map->getFaction(node) == primary->getRace()->getName()) {
        vector<Token *> tokens = map->clearReinforcements(node);
        for(int i = 0; i<tokens.size()-1;i++)
            primaryTokens.push_back(tokens[i]);
        vector<Token *> lost = vector<Token *>(1);
        lost[0] = tokens[tokens.size()-1];
        box->returnTokens(lost);
        cout << tokens.size() << " tokens returned" << endl;
    }
    if(secondary!=nullptr) {
        if (map->getFaction(node) == secondary->getRace()->getName())
            box->returnTokens(map->clearReinforcements(node));
    }
    map->setFaction(node,"");
    map->setPlayer(node,"");
    nodes.erase( std::remove(nodes.begin(), nodes.end(), std::string(node)), nodes.end() );
}

//Gives points based on the nodes controlled
int Player::scores(int i) {
    int lands = nodes.size();
    bool forest, human, merchant, hill, orc, pillaging, underworld, wizard, dwarf, swamp;
    string power,race;
    if(primary != nullptr) {
        power = primary->getPower()->getName();
        race = primary->getRace()->getName();
    }else {
        power = "";
        race = "";
    }
    if(power == "Alchemist")
        lands+=2;
    for (auto node : nodes) {
        string terrain = map->getTerrain(node);
        vector<string> mods = map->getModifiers(node);
        if (terrain == "Forest" && power == "Forest") {
            lands += 1;
        }
        if (terrain == "Swamp" && power == "Swamp") {
            lands += 1;
        }
        if (terrain == "Hill" && power == "Hill") {
            lands += 1;
        }
        if (terrain == "Farmland" && race == "Humans") {
            lands += 1;
        }
        if (power == "Merchant") {
            lands += 1;
        }
        if (power == "Underworld" && std::find(mods.begin(), mods.end(), "Cave") != mods.end())
            lands += 1;
        if (race == "Wizards" && std::find(mods.begin(), mods.end(), "Magic") != mods.end())
            lands += 1;
        if (race == "Dwarves" && std::find(mods.begin(), mods.end(), "Mine") != mods.end())
            lands+=1;
        else if(secondary != nullptr){
           if(secondary->getRace()->getName() == "Dwarves" && std::find(mods.begin(), mods.end(), "Mine") != mods.end()) {
              lands += 1;
            }
        }
        }
        if (race=="Orcs")
            lands += i;
        if (power=="Pillaging")
            lands += i;
    vector<vCoin*> points = box->giveCoins(lands);
    addVp(points);
    return lands;
}
void Player::addVp(vector<vCoin*> points) {
    for(vCoin* coin : points){
        if(coin->getValue() == 1)
            oneP.push_back(coin);
        if(coin->getValue() == 3)
            threeP.push_back(coin);
        if(coin->getValue() == 5)
            fiveP.push_back(coin);
        if(coin->getValue() == 10)
            tenP.push_back(coin);
    }
}
vector<vCoin*> Player::removeVp(int i) {
    vector<vCoin*> coins;
    for(int j=0;j<i;j++){
        coins.push_back(oneP[0]);
        oneP.erase(oneP.begin());
    }
    return coins;
}
int Player::getVp(){
    return oneP.size() + threeP.size() * 3 + fiveP.size() * 5 + tenP.size() * 10;
}
//Because we need a summarySheet ¯\_(ツ)_/¯
string Player::readSummarySheet() {return summarySheet;}

int Player::getTokens() {return primaryTokens.size();}

void Player::addMod(string node) {map->addscoreMod(node,powerMods[0]); powerMods.erase(powerMods.begin());}
void Player::removeMod(string node) {powerMods.push_back(map->removescoreMod(node));}

void Player::abandon(string node) {
    vector<Token *> temp= map->clearReinforcements(node);
    for(auto tok : temp)
        primaryTokens.push_back(tok);
}

Faction * Player::getPrimary() {return primary;}

string Player::getName(){ return name;}

vector<Token *> * Player::getTokenRef() {return &primaryTokens;}

void Player::prepare() { //leaves each zone with just 1 token
    for(auto node : nodes){
       vector<Token *> temp;
        if(map->getFaction(node) == primary->getRace()->getName()) {
            temp = map->clearReinforcements(node);
            vector<Token *> otherTemp;
            otherTemp.push_back(temp[temp.size()-1]);
            temp.erase(temp.begin()+temp.size()-1);
            map->setReinforcements(node,otherTemp);
            for(auto token : temp)
                primaryTokens.push_back(token);
        }
    }
}

void Player::decline(){
    if(secondary != nullptr) {
        for (auto node : nodes) {
            if (map->getFaction(node) == secondary->getRace()->getName()) {
                loses(node);
            }
        }
        deck->giveBack(secondary);
    }
    prepare();
    box->returnTokens(primaryTokens);
    primaryTokens.clear();
    secondary = primary;
    primary = nullptr;
}

int Player::roll() {return dice->roll();}

Faction* Player::getSecondary() {return secondary;}