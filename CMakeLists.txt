cmake_minimum_required(VERSION 3.9)
project(project)

set(CMAKE_CXX_STANDARD 17)

add_executable(project src/main.cpp src/map.cpp src/map.h src/MapLoader.cpp src/MapLoader.h src/rDice.cpp src/rDice.h src/factions.cpp src/factions.h src/faction.cpp src/faction.h src/player.cpp src/player.h src/gamebox.cpp src/gamebox.h src/piece.cpp src/piece.h  src/gameEngine.cpp src/gameEngine.h src/observer.cpp src/observer.h src/subject.cpp src/subject.h src/PhaseSubject.cpp src/PhaseSubject.h src/PhaseObserver.cpp src/PhaseObserver.h src/statsobserver.cpp src/statsobserver.h src/statssubject.cpp src/statssubject.h src/StatsDecorator.cpp src/StatsDecorator.h src/ConquestDecorator.cpp src/ConquestDecorator.h src/undecoratedObserver.cpp src/undecoratedObserver.h src/HandDecorator.cpp src/HandDecorator.h src/CoinsDecorator.cpp src/CoinsDecorator.h src/Strategy.cpp src/Strategy.h src/RandomStrategy.cpp src/ModerateStrategy.cpp)