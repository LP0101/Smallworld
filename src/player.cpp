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
    vp = 20;
    map = m;
    dice = new rDice();
}
void Player::picks_race(int i) {
    if(vp<i)
        throw new exception;
    vp-=i;
    vp+=deck->requestValue(i);
    Faction *choice = deck->take(i);
    if(primary == nullptr)
        primary = choice;
    else{
        if(secondary == nullptr){
            secondary = primary;
            primary = choice;
        }
        else{
            if(secondary->getRaw()[0][0] == "spirit"){
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
void Player::conquers(string node,int i) {
    map->setFaction(node,primary->getRaw()[1][0]);
    map->setReinforcements(node,i);
    primary->setTokens(primary->getTokens()-i);
    nodes.push_back(node);
}
void Player::loses(string node) {
    if(map->getFaction(node) == primary->getRaw()[1][0])
        primary->setTokens(primary->getTokens()+map->getReinforcements(node)-1); //incomplete - need to mark that territory was lost
    map->setFaction(node,"");
    nodes.erase( std::remove(nodes.begin(), nodes.end(), std::string(node)), nodes.end() );
}

void Player::scores() {
    vp+=nodes.size(); //incomplete - needs proper rule engine to check for bonus scores
}
void Player::addVp(int i) {vp+=i;}
void Player::removeVp(int i) {vp-=i;}
int Player::getVp(){return vp;}
