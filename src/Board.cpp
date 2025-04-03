//
// Created by istin on 2025. 04. 03..
//

#include "Board.hpp"

int Board::defaultx = 10;
int Board::defaulty = 10;
double Board::defaultdiff = 0.2;

Board::Board() {
    cells = new Cell*[defaulty];
    for (int i = 0; i < defaulty; i++)
        cells[i] = new Cell[defaultx];
}