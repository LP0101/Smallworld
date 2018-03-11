// // Created by luca on 15/02/18.
//

//This is a bit unintuitive, Factions represents the deck itself (which is power card + race cards).
// These cards are vectors containing the name (string) and the token number.

#include <algorithm>
#include <random>
#include <chrono>
#include "factions.h"

//Factions are built using the two files in GameConfig. Each power/race has its token value beside it.

Factions::Factions(string r, string p, Gamebox *gamebox){
    string line, name;
    int toks;
    ifs.open("../"+r);
    while(getline(ifs,line)){
        name = (line.substr(0, line.find(" ")));
        line.erase(0, line.find(" ") + 1);
        toks = stoi(line);

        races.push_back(new Race(name,toks));
    }
    ifs.close();
    ifs.open("../"+p);
    while(getline(ifs,line)){
        name = (line.substr(0, line.find(" ")));
        line.erase(0, line.find(" ") + 1);
        toks = stoi(line);
        Power *a = new Power(name, toks);
        powers.push_back(a);
    }
    ifs.close();

    shuffle(powers.begin(),powers.end(),std::default_random_engine(time(NULL)));
    shuffle(races.begin(),races.end(),std::default_random_engine(time(NULL)+420)); //different random seeds as they run at the same time

    for (int i=0;i<6;i++){
        values.push_back(new vector<vCoin*>);
    }
    g = gamebox;
}

vector<string> Factions::topDecks() {
    vector<string> topdecks;
    string combo;
    for(int i = 0;i<6;i++){
        combo = to_string(i) + ": " + powers[i]->getName() + " " + races[i]->getName() + " (" + to_string(values[i]->size()) + ")";
        topdecks.push_back(combo);
    }
   return topdecks;
}
//Takes a card from the "deck" and returns a faction object. Also adds 1 to the value of every card above it, and shifts the value array down by 1
Faction *Factions::take(int i, vector<vCoin*> cost) {
    Faction *request = new Faction(powers[i],races[i]);
    for(int j=0; j<i; j++){
        values[j]->push_back(cost[j]);
    }
    g->transfer(values[i]);
    delete values[i];
    values.erase(values.begin()+i);
    powers.erase(powers.begin()+i);
    races.erase(races.begin()+i);
    values.push_back(new vector<vCoin *>);
    return request;
}

//Decomposes a faction object back into its two vectors, adds them to the bottom of the deck, then deletes them
void Factions::giveBack(Faction* f) {
    powers.push_back(f->getPower());
    races.push_back(f->getRace());
    delete f;
}
//int Factions::requestValue(int i) {return values[i];}
