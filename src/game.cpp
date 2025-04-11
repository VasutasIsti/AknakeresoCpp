#include "game.hpp"

#include <utility>

Game::Game() :  board(Board()),
                timer(Timer()),
                username("Player"),
                state(INGAME),
                undoEnabled(false),
                flagsRemaining(board.DiffToBombCount()),
                notVisited(board.Size()) {}

Game::Game(const int x, const int y, const double diff, std::string username, const bool undo) :
    board(x, y, diff),
    timer(Timer()),
    username(std::move(username)),  // itt engedtem a clang-nek meg az ide-nek
    state(INGAME),
    undoEnabled(undo),
    flagsRemaining(board.DiffToBombCount()),
    notVisited(x*y) {}

void Game::Flaging(const int x, const int y) {
    if (undoEnabled)
        undo.LogFlaging(x, y);

    //TODO
}

void Game::VisitCell(const int x, const int y) {
    if (undoEnabled)
        undo.LogVisiting(x, y, true);

    //TODO
}

void Game::VisitedSelected(const int x, const int y) {
    //TODO undo logging szempontbol
}
