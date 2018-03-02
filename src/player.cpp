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
    for(int i=0; i<20;i++){
        oneP.push_back(new vCoin(1));
    }
    powerMods.push_back(new Modifier("Dragon",2));
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
    map->setReinforcements(node,temp);

    nodes.push_back(node);
}
//Invoked when a player loses a node. If the controlling race of the token is equal to the player's primary race, the tokens minus 1 are returned.
void Player::loses(string node) {
    if(map->getFaction(node) == primary->getRace()->getName())
//        primary->setTokens(primary->getTokens()+map->getReinforcements(node)-1); //incomplete - need to mark that territory was lost
    map->setFaction(node,"");
    nodes.erase( std::remove(nodes.begin(), nodes.end(), std::string(node)), nodes.end() );
}

//Gives points based on the nodes controlled
void Player::scores() {
    int lands = nodes.size();
    vector<vCoin*> points = box->giveCoins(lands);
    addVp(points);
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