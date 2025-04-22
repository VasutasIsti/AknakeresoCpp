#include "game.hpp"

#include <utility>

Game::Game() :
    undo(UndoHandler()),
    board(Board(undo)),
    timer(Timer()),
    username("Player"),
    state(INGAME),
    flagsRemaining(board.DiffToBombCount()),
    notVisiteds(board.Size()) {}

Game::Game(const int x, const int y, const double diff, std::string username, const bool undoEnabled) :
    undo(UndoHandler()),
    board(Board(x, y, diff, undo)),
    timer(Timer()),
    username(std::move(username)),
    state(INGAME),
    flagsRemaining(board.DiffToBombCount()),
    notVisiteds(board.Size()) {
    if (undoEnabled)
        undo.EnableUndo();
}

void Game::Flaging(const int x, const int y) {
    undo.LogFlaging(x, y);

    //TODO
}

void Game::VisitCell(const int x, const int y) {
    undo.LogVisiting(x, y, true);

    //TODO
}

void Game::VisitedSelected(const int x, const int y) {
    //TODO undo logging szempontbol
}

void Game::Undo() {
    CellChange current;
    while (current.changedByPlayer) {
        current = undo.Undo();
        // Igaz, ha a visszavonas utan zaszlo lett a cellan
        bool flagstate = board.Undo(current);
        if (current.flagedOrVisited) {
            if (flagstate) flagsRemaining++;
            else           flagsRemaining--;
        }
        else notVisiteds++;
    }
}

void Game::Win() {
    // TODO
    std::cout << username << " wins!\n";
}

void Game::Lose() {
    // TODO
    std::cout << username << " loses!\n";
}

std::ostream& operator<<(std::ostream& os, const Game& game) {
    os << "username=" << game.username << "\n";
    os << "state=" << game.state << "\n";
    os << "flagsRemaining=" << game.flagsRemaining << "\n";
    os << "notVisiteds=" << game.notVisiteds << "\n";
    os << "\nTIMER\n" << game.timer << "\n";
    os << "\nBOARD\n" << game.board << "\n";
    os << "\nUNDOHANDLER\n" << game.undo;

    return os;
}