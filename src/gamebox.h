//
// Created by luca on 28/02/18.
//

#ifndef PROJECT_GAMEBOX_H
#define PROJECT_GAMEBOX_H

#include "piece.h"
#include <vector>


class Gamebox {
public:
    vector<vCoin*> giveCoins(int i);
    Gamebox();

private:
    vector<vCoin*> oneCoins;
    vector<vCoin*> threeCoins;
    vector<vCoin*> fiveCoins;
    vector<vCoin*> tenCoins;
    vector<Token*> tokens;
    vector<Modifier*> modifiers;
};


#endif //PROJECT_GAMEBOX_H
