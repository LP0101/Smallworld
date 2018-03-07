#include <iostream>
#include "rDice.h"
#include "map.h"
#include "factions.h"
#include "player.h"
#include "gameEngine.h"

using namespace std;

int main() {
    GameEngine engine = GameEngine();
    engine.init();
    engine.gameLoop();
}
