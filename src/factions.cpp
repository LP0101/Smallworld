// // Created by luca on 15/02/18.
//

//This is a bit unintuitive, Factions represents the deck itself (which is power card + race cards).
// These cards are vectors containing the name (string) and the token number.

#include <algorithm>
#include <random>
#include <chrono>
#include "factions.h"

//Factions are built using the two files in GameConfig. Each power/race has its token value beside it.

Factions::Factions(string r, string p){
    string line;
    ifs.open("../"+r);
    while(getline(ifs,line)){
        vector<string> v;
        v.push_back(line.substr(0, line.find(" ")));
        line.erase(0, line.find(" ") + 1);
        v.push_back(line);
        races.push_back(v);
    }
    ifs.close();
    ifs.open("../"+p);
    while(getline(ifs,line)){
        vector<string> v;
        v.push_back(line.substr(0, line.find(" ")));
        line.erase(0, line.find(" ") + 1);
        v.push_back(line);
        powers.push_back(v);
    }
    ifs.close();

    shuffle(powers.begin(),powers.end(),std::default_random_engine(time(NULL)));
    shuffle(races.begin(),races.end(),std::default_random_engine(time(NULL)+420)); //different random seeds as they run at the same time
    for(int i=0;i<6;i++){
        values.push_back(0);
    }
}

vector<string> Factions::topDecks() {
    vector<string> topdecks;
    string combo;
    for(int i = 0;i<6;i++){
        combo = to_string(i) + ": " + powers[i][0] + " " + races[i][0] + " (" + to_string(values[i]) + ")";
        topdecks.push_back(combo);
    }
   return topdecks;
}
//Takes a card from the "deck" and returns a faction object. Also adds 1 to the value of every card above it, and shifts the value array down by 1
Faction *Factions::take(int i) {
    Faction *request = new Faction(powers[i],races[i]);
    for(int j=0; j<i; j++){
        values[j]+=1;
    }
    for(int j=i; j<4; j++){
        values[j]=values[j+1];
    }
    values[5]=0;
    powers.erase(powers.begin()+i);
    races.erase(races.begin()+i);
    return request;
}

//Decomposes a faction object back into its two vectors, adds them to the bottom of the deck, then deletes them
void Factions::giveBack(Faction* f) {
    powers.push_back(f->getRaw()[0]);
    races.push_back(f->getRaw()[1]);
    delete f;
}
int Factions::requestValue(int i) {return values[i];}
