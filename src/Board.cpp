//
// Created by istin on 2025. 04. 03..
//

#include "Board.hpp"

int Board::defaultx = 10;
int Board::defaulty = 10;
double Board::defaultdiff = 0.2;

bool Board::isOnBoard(int x, int y) const {
    if (x < 0 || y < 0 || x >= Board::sizeX || y >= Board::sizeY)
        return false;
    return true;
}

// Feltetelezve, hogy olyan cellara nem inditjuk el, ami Akna, igy sajat magat
// nem zarjuk ki a kozepso cella vizsgalatat.
int Board::NeighbourCount(int x, int y) const {
    int neighbours = 0;
    if (isOnBoard(x, y))
        for (int i = x-1; i <= x+1; i++)
            for (int j = y-1; j <= y+1; j++)
                if (cells[i][j].getIsBomb())
                    neighbours++;
    return neighbours;
}

Board::Board() : sizeX(defaultx), sizeY(defaulty), difficulty(defaultdiff), bombs(diffToBombCount()) {
    cells = new Cell*[sizeX];
    for (int i = 0; i < sizeX; i++)
        cells[i] = new Cell[sizeY];
}

Board::Board(int x, int y, double diff)
    : sizeX(x), sizeY(y), difficulty(diff), bombs(diffToBombCount()) {
    cells = new Cell*[sizeX];
    for (int i = 0; i < sizeX; i++)
        cells[i] = new Cell[sizeY];
}

Board::~Board() {
    for (int i = 0; i < defaulty; i++)
        delete[] cells[i];
    delete[] cells;
}
