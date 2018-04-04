//
// Created by Popesco, Luca on 2018-04-03.
//

#include "Strategy.h"

ModerateStrategy::ModerateStrategy() {}
ModerateStrategy::ModerateStrategy(Player *player) {_player=player;}
ModerateStrategy::~ModerateStrategy() {}

void ModerateStrategy::Execute(bool reinforce, bool conquer) {
    vector<string> temp = _player->getNodes();
    vector<string> temp2;
    shuffle(temp.begin(), temp.end(), std::default_random_engine(time(NULL)));
    if(!reinforce){
        if(!conquer) {
            //check for how many nodes primary has
            int owned = 0;
            for (auto node : _player->getNodes()) {
                if (_player->getMap()->getFaction(node) == _player->getPrimary()->getRace()->getName())
                    owned++;
            }
            if (owned > 4){
                cout << "Go into decline" << endl;
                return;
            }
        }
        //conquer/reinforce randomly

        for (auto node : temp) {
            if (_player->getMap()->getFaction(node) == _player->getPrimary()->getRace()->getName()) {
                temp2 = _player->getMap()->getAdjacent(node);
                shuffle(temp2.begin(), temp2.end(), std::default_random_engine(time(NULL) + 4));
                for (auto adj : temp2) {
                    if (_player->getMap()->getFaction(adj) != _player->getPrimary()->getRace()->getName()) {
                        if (_player->getPrimary()->getPower()->getName() != "Seafaring" &&
                            _player->getMap()->getTerrain(adj) == "Water")
                            continue;
                        cout << "You should conquer " << adj << endl;
                        return;
                    }
                }
            }
        }
        cout << "Conquer any edge" << endl;
    }
    else{
        for(auto node : temp){
            if(_player->getMap()->getFaction(node) == _player->getPrimary()->getRace()->getName()){
                cout << "Reinforce " << node << endl;
                return;
            }
        }
    }

}
