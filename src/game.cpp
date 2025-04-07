#include "game.hpp"

#include <utility>

Game::Game() :  board(Board()),
                timer(Timer()),
                username("Player"),
                state(INGAME),
                flagsRemaining(board.DiffToBombCount()),
                notVisited(board.Size()) { }

Game::Game(int x, int y, double diff, std::string username) :
    board(x, y, diff),
    timer(Timer()),
    username(std::move(username)),  // itt engedtem a clang-nek meg az ide-nek
    state(INGAME),
    flagsRemaining(board.DiffToBombCount()),
    notVisited(x*y) { }

