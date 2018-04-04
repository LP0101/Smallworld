//
// Created by Popesco, Luca on 2018-04-02.
//

#include "StatsDecorator.h"

StatsDecorator::StatsDecorator(StatsObserver *s) {this->_decoratedObserver = s;}
void StatsDecorator::Update(){
    this->_decoratedObserver->Update();
}

