//
// Created by Popesco, Luca on 2018-03-29.
//

#include "PhaseSubject.h"

void PhaseSubject::setPlayer(string player) {this->player = player;}
void PhaseSubject::setAction(string action) {this->action = action;}

string PhaseSubject::getPlayer() {return player;}
string PhaseSubject::getAction() {return action;}

PhaseSubject::PhaseSubject(): player(""),  action("") {}
PhaseSubject::~PhaseSubject() {}
