//
// Created by Popesco, Luca on 2018-04-03.
//

#ifndef PROJECT_STRATEGY_H
#define PROJECT_STRATEGY_H
#include <random>
class Player;
#include "player.h"

using namespace std;

/**
 * Lots of Code duplication going on in here. Need to clean up.
 */

class Strategy {
public:
    Strategy(Player* player);
    Strategy();
    virtual void Execute(bool reinforce, bool conquer)=0;
    virtual ~Strategy();

};

class RandomStrategy : public Strategy {
public:
    RandomStrategy();
    RandomStrategy(Player* player);
    ~RandomStrategy();
    void Execute(bool reinforce, bool conquer);
private:
    Player* _player;

};

class ModerateStrategy : public Strategy {
public:
    ModerateStrategy();
    ModerateStrategy(Player* player);
    ~ModerateStrategy();
    void Execute(bool reinforce, bool conquer);
private:
    Player* _player;
};
class DefensiveStrategy : public Strategy {
public:
    DefensiveStrategy();
    DefensiveStrategy(Player* player);
    ~DefensiveStrategy();
    void Execute(bool reinforce, bool conquer);
private:
    Player* _player;
};

class AggressiveStrategy : public Strategy {
public:
    AggressiveStrategy();
    AggressiveStrategy(Player* player);
    ~AggressiveStrategy();
    void Execute(bool reinforce, bool conquer);
private:
    Player* _player;
};

#endif //PROJECT_STRATEGY_H
