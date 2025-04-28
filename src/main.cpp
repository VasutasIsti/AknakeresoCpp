#include <iostream>
#include "game.hpp"

// Amiket ugymond kotelezo. A pelda NHF fajlaibol all,
// ezek elvileg 2022-es modositasuk, remelem ez az a verzio ami kell
#define MEMTRACE

int main() {
    Game game(5, 10, 0.3, "Stefan", true);
    std::cout << game;
    game.Flaging(0, 0);
    std::cout << game;
    game.Undo();
    std::cout << game;


    return 0;
}
