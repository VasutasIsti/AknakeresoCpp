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
int Board::neighbourCount(const int x, const int y) const {
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

bool Board::isEmptyListed(int x, int y, const std::vector<std::array<int, 2>>& empties) const {
    for (int i = 0; i < empties.size(); i++)
        if (empties[i][0] == x && empties[i][1] == y)
            return true;
    return false;
}

void Board::CheckAdjacents(const int x, const int y, std::vector<std::array<int, 2>>& empties) const {
    empties[empties.size()] = {x,y};
    for (int i = x-1; i <= x+1; i++)
        for (int j = y-1; j <= y+1; j++) {
            if ((i == x && j == y) || !isOnBoard(i, j) || isEmptyListed(i, j, empties))
                continue;
            if (cells[i][j].getNeighbourCount() == 0 && !cells[i][j].getIsVisited())
                CheckAdjacents(i, j, empties);
            else if (cells[i][j].getNeighbourCount() > 0)
                empties[empties.size()] = {i, j};
        }
}

Board::~Board() {
    for (int i = 0; i < defaulty; i++)
        delete[] cells[i];
    delete[] cells;
}
