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
    void returnCoins(vector<vCoin*>);
    void transfer(vector<vCoin*>*);
    vector<vCoin*> transfer();
    Gamebox();
    vector<Token*> giveTokens(string race, int quantity);
    void returnTokens(vector<Token *> tokens);
    Modifier* giveModifier(string name);

private:
    vector<vCoin*> oneCoins;
    vector<vCoin*> threeCoins;
    vector<vCoin*> fiveCoins;
    vector<vCoin*> tenCoins;
    vector<Token*> tokens;
    vector<Modifier*> modifiers;
    vector<vCoin*> last;
};


#endif //PROJECT_GAMEBOX_H
