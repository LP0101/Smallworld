//
// Created by luca on 15/02/18.
//

#include "player.h"

Player::Player(string n, Factions *f, Map *m){
    name = n;
    primary = nullptr;
    secondary = nullptr;
    spirit = nullptr;
    deck = f;
    map = m;
    dice = new rDice();
    summarySheet = "Rules and stuff";
}
//picks a race, paying the appropriate price for it. Also increases the player's victory points by the race's value
//Moves the player's primary race to secondary, and gives the secondary race back to the deck.
//If the secondary race has the "Spirit" power, it is instead moved to a third spirit slot.
void Player::picks_race(int i) {
    if(oneP.size()<i)
        throw new exception;
//    vp-=i;
//    vp+=deck->requestValue(i);
    Faction *choice = deck->take(i);
    if(primary == nullptr)
        primary = choice;
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
}
//sets a node to the player's race and adds the given number of tokens to that node. Also removes that many tokens from the player's primary race
void Player::conquers(string node,int i) {
    map->setFaction(node,primary->getRace()->getName());
    map->setReinforcements(node,i);
//    primary->setTokens(primary->getTokens()-i);
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
//    int points=nodes.size(); //incomplete - needs proper rule engine to check for bonus scores
//    if(points >= 10){
//
//    }
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
vCoin* Player::removeVp(int i) {
    vector<vCoin*> coins;
    for(int j=0;j<i;j++){
        coins.push_back(oneP[0]);
        oneP.erase(oneP.begin() + i);
    }
}
int Player::getVp(){
    return oneP.size() + threeP.size() * 3 + fiveP.size() * 5 + tenP.size() * 10;
}
//Because we need a summarySheet ¯\_(ツ)_/¯
string Player::readSummarySheet() {return summarySheet;}
