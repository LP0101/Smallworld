//
// Created by luca on 15/02/18.
//

#ifndef PROJECT_RDICE_H
#define PROJECT_RDICE_H

#import <iostream>

using namespace std;


class rDice {
public:
    rDice();
    int roll();
    float getPercentage(int value);

private:
    int rolls[4];

};


#endif //PROJECT_RDICE_H
