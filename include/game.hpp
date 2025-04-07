#ifndef GAME_H
#define GAME_H

#include "board.hpp"
#include "timer.h"


enum GameState {
    INGAME,
    WIN,
    LOSE
};

class Game {
    Board board;
    Timer timer;
    std::string username;
    GameState state;
    int flagsRemaining;
    int notVisited;
public:
    Game();
    Game(int x, int y, double diff, std::string username);


    // A fo, jatekmenetbeli funkciok
    void Flaging(int x, int y);
    void VisitCell(int x, int y);
    void VisitedSelected(int x, int y);
    void Win();
    void Lose();

    friend std::ostream& operator<<(std::ostream& os, const Game& game);
    friend std::istream& operator>>(std::istream& is, Game& game);

};

#endif //GAME_H
