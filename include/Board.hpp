//
// Created by istin on 2025. 04. 03..
//

#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <memory>

#include "Cell.hpp"

class Board {
    static int defaultx, defaulty;  ///< Alap palyameretek
    static double defaultdiff;      ///< Alap nehezseg

    Cell** cells;   ///<
    int sizeX, sizeY;
    double difficulty;
    int bombs;
public:

    /// Default Konstruktor
    Board();

    ~Board() {delete[][] cells;};
};



#endif //BOARD_HPP
