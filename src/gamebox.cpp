//
// Created by luca on 28/02/18.
//

#include "gamebox.h"

Gamebox::Gamebox() {
    for(int i=0;i<35;i++){
        oneCoins.push_back(new vCoin(1));
    }
    for(int i=0;i<20;i++){ threeCoins.push_back(new vCoin(3));}
    for(int i=0;i<24;i++){ fiveCoins.push_back(new vCoin(5));}
    for(int i=0;i<24;i++){ tenCoins.push_back(new vCoin(10));}

    for(int i=0;i<15;i++){ tokens.push_back(new Token("Amazons"));}
    for(int i=0;i<8;i++){ tokens.push_back(new Token("Dwarves"));}
    for(int i=0;i<11;i++){ tokens.push_back(new Token("Elves"));}
    for(int i=0;i<13;i++){ tokens.push_back(new Token("Ratmen"));}
    for(int i=0;i<20;i++){ tokens.push_back(new Token("Skeletons"));}
    for(int i=0;i<18;i++){ tokens.push_back(new Token("Sorcerers"));}
    for(int i=0;i<11;i++){ tokens.push_back(new Token("Tritons"));}
    for(int i=0;i<11;i++){ tokens.push_back(new Token("Giants"));}
    for(int i=0;i<11;i++){ tokens.push_back(new Token("Halflings"));}
    for(int i=0;i<10;i++){ tokens.push_back(new Token("Humans"));}
    for(int i=0;i<10;i++){ tokens.push_back(new Token("Orcs"));}
    for(int i=0;i<10;i++){ tokens.push_back(new Token("Trolls"));}
    for(int i=0;i<10;i++){ tokens.push_back(new Token("Wizards"));}
    for(int i=0;i<10;i++){ tokens.push_back(new Token("Lost Tribes"));}
}

vector<vCoin*> Gamebox::giveCoins(int i) {
    vector<vCoin*> coins;
    while(i>0){
        if(i>=10){
           coins.push_back(tenCoins[0]);
            tenCoins.erase(tenCoins.begin());
            i-=10;
            continue;
        }
        if(i>=5){
            coins.push_back(fiveCoins[0]);
            fiveCoins.erase(fiveCoins.begin());
            i-=5;
            continue;
        }
        if(i>=3){
            coins.push_back(threeCoins[0]);
            threeCoins.erase(threeCoins.begin());
            i-=3;
            continue;
        }
        coins.push_back(oneCoins[0]);
        oneCoins.erase(oneCoins.begin());
        i-=1;
    }
    return coins;
}
