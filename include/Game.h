//
// Created by vasutasisti on 2025.04.04..
//

#ifndef GAME_H
#define GAME_H

#include "Board.hpp"
#include "Timer.h"

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
    Game(int x, int y, double diff, std::string username);

};

#endif //GAME_H
