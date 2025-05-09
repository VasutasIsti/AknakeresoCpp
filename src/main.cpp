#include <iostream>
#include "game.hpp"
#include "cli.hpp"

// Amiket ugymond kotelezo. A pelda NHF fajlaibol all,
// ezek elvileg 2022-es modositasuk, remelem ez az a verzio ami kell
//#define MEMTRACE

int main() {
    Game game(5, 10, 0.3, "Stefan", true);
    std::cout << game << "\n---------------------------------\n\n";
    game.Flaging(0, 0);
    std::cout << game << "\n---------------------------------\n\n";
    game.Undo();
    std::cout << game;


    return 0;
}
