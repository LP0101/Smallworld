//
// Created by luca on 15/02/18.
//

#include "rDice.h"

rDice::rDice(){
    fill_n(rolls,4,0);
    srand(time(NULL));
}

int rDice::roll() {
    int randnum=rand()%(6-1+1)+1;
    if(randnum > 3)
        randnum = 0;
    rolls[randnum]+=1;
    return randnum;
}

float rDice::getPercentage(int value) {
    int total=0;
    for(int i=0;i<4;i++){
        total+=rolls[i];
    }
    cout << "Total is " + to_string(total) << endl;
    if(total > 0) {
        return float(rolls[value]) / float(total);
    }
    else
        return 0;
}