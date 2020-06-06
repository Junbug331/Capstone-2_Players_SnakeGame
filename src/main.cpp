#include <iostream>
#include "game.h"

int main() {

    Game *game = Game::Instance();
    game->Run();
    Game::Release();
    std::cout << "Game Ended" << std::endl;
    game = nullptr;



    return 0;
}
