//
// Created by Popesco, Luca on 2018-04-03.
//

#ifndef PROJECT_STRATEGY_H
#define PROJECT_STRATEGY_H
#include <random>
class Player;
#include "player.h"

using namespace std;

class Strategy {
public:
    Strategy(Player* player);
    Strategy();
    virtual void Execute(int reinforce)=0;
    virtual ~Strategy();
};

class RandomStrategy : public Strategy {
public:
    RandomStrategy();
    RandomStrategy(Player* player);
    ~RandomStrategy();
    void Execute(int reinforce);
private:
    Player* _player;

};

class ModerateStrategy : public Strategy {
public:
    ModerateStrategy();
    ModerateStrategy(Player* player);
    ~ModerateStrategy();
    void Execute(int reinforce);
private:
    Player* _player;
};

#endif //PROJECT_STRATEGY_H
