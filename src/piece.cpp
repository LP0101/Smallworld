//
// Created by luca on 28/02/18.
//

#include "piece.h"

vCoin::vCoin(int v) {value = v;}
int vCoin::getValue() {return value;}

Race::Race(string n, int i) {name = n; tokens=i;}
string Race::getName() {return name;}
int Race::getTokens() {return tokens;}

Power::Power(string n, int i) {name = n; tokens = i;}
int Power::getTokens() {return tokens;}
string Power::getName() {return name;}

Token::Token(string r) {race = r;}
string Token::getRace() {return race;}

Modifier::Modifier(string n, int e) {
    name = n; effect = e;
    if(effect != 1 && effect != 2)
        throw exception();
}
string Modifier::getName() {return name;}
int Modifier::getEffect() {return effect;}
