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


}
