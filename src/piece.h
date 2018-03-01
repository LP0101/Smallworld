//
// Created by luca on 28/02/18.
//

#ifndef PROJECT_PIECE_H
#define PROJECT_PIECE_H

#include <iostream>

using namespace std;

class piece {

};

class vCoin : public piece{
private:
    int value;
public:
    vCoin(int v);
    int getValue();
};

class Race : public piece{
private:
   string name;
   int tokens;
public:
    Race(string n, int i);
    string getName();
    int getTokens();
};

class Power : public piece{
private:
   string name;
   int tokens;
public:
    Power(string n, int i);
    string getName();
    int getTokens();
};

class Token : public piece{
private:
    string race;
public:
    Token(string r);
    string getRace();
};

class Modifier : public piece{
private:
    string name;
    int effect; //1 increases cost of node by 1, 2 makes node immune
public:
    Modifier(string n, int e);
    int getEffect();
    string getName();
};


#endif //PROJECT_PIECE_H
