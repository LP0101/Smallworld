cmake_minimum_required(VERSION 3.9)
project(project)

set(CMAKE_CXX_STANDARD 11)

add_executable(project src/main.cpp src/map.cpp src/map.h src/MapLoader.cpp src/MapLoader.h src/rDice.cpp src/rDice.h src/factions.cpp src/factions.h src/faction.cpp src/faction.h src/player.cpp src/player.h)