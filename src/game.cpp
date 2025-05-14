#include "game.hpp"
#include <utility>      // string Masolasok miatt

std::string Game::defUser = "Player";

Game::Game() :
    undo(UndoHandler()),
    board(Board()),
    timer(Timer()),
    username(defUser),
    state(INGAME),
    flagsRemaining(board.DiffToBombCount()),
    notVisiteds(board.Size()) {}

Game::Game(const int x, const int y, const double diff, std::string username, const bool undoEnabled) :
    undo(UndoHandler()),
    board(Board(x, y, diff)),
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
    bool flaged = board.getCell(x, y).Flag();
    if (flaged) flagsRemaining--;
    else        flagsRemaining++;
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
    do {
        current = undo.Undo();
        // Igaz, ha a visszavonas utan zaszlo lett a cellan
        bool flagstate = board.Undo(current);
        if (current.flagedOrVisited) {
            if (flagstate) flagsRemaining++;
            else           flagsRemaining--;
        }
        else notVisiteds++;
    } while (!current.changedByPlayer);
}

void Game::Win() {
    // TODO
    std::cout << username << " wins!\n";
}

void Game::Lose() {
    // TODO
    std::cout << username << " loses!\n";
}

void Game::SaveMidGame() {
    // TODO
}

std::ostream& operator<<(std::ostream& os, const Game& game) {
    os << "username=" << game.username << "\n";
    os << "state=" << game.state << "\n";
    os << "flagsRemaining=" << game.flagsRemaining << "\n";
    os << "notVisiteds=" << game.notVisiteds << "\n\n";
    os << "TIMER\n" << game.timer << "\n";
    os << "BOARD\n" << game.board << "\n";
    os << "UNDOHANDLER\n" << game.undo << "\n";

    return os;
}


// Ez egy picit nagyon hosszu lett... nem tudom mit cseszek el a template irasoknal, de ott sem usztam meg eddig
// rovidebben, minthogy minden valtozo tipusra specifikalnom kelljen a konvertalasok miatt...
std::istream& operator>>(std::istream& is, Game& game) {
    // TODO
    std::string line;

    std::getline(is, line);
    if (line.find("username") != std::string::npos)
        game.username = line.substr(line.find('=') + 1);
    else
        throw std::invalid_argument("Incorrect file content!");

    std::getline(is, line);
    if (line.find("state") != std::string::npos)
        game.state = static_cast<GameState>(std::stoi(line.substr(line.find('=') + 1)));
    else
        throw std::invalid_argument("Incorrect file content!");
    
    std::getline(is, line);
    if (line.find("flagsRemaining") != std::string::npos)
        game.flagsRemaining = std::stoi(line.substr(line.find('=') + 1));
    else
        throw std::invalid_argument("Incorrect file content!");
    
    std::getline(is, line);
    if (line.find("notVisiteds") != std::string::npos)
        game.notVisiteds = std::stoi(line.substr(line.find('=') + 1));
    else
        throw std::invalid_argument("Incorrect file content!");
    
    std::getline(is, line); // ures

    std::getline(is, line);
    if (line.find("TIMER") != std::string::npos)
        is >> game.timer;
    else
        throw std::invalid_argument("Incorrect file content!");
    
    std::getline(is, line); // ures

    std::getline(is, line);
    if (line.find("BOARD") != std::string::npos)
        is >> game.board;
    else
        throw std::invalid_argument("Incorrect file content!");
    
    std::getline(is, line); std::getline(is, line); // nem getline-os a board olvasas
    
    std::getline(is, line);
    if (line.find("UNDOHANDLER") != std::string::npos)
        is >> game.undo;
    else
        throw std::invalid_argument("Incorrect file content!");

    return is;
}