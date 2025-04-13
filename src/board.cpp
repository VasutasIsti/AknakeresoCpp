#include "board.hpp"

int Board::defaultx = 10;
int Board::defaulty = 10;
double Board::defaultdiff = 0.2;

bool Board::IsOnBoard(const int x, const int y) const {
    if (x < 0 || y < 0 || x >= Board::sizeX || y >= Board::sizeY)
        return false;
    return true;
}

// Feltetelezve, hogy olyan cellara nem inditjuk el, ami Akna, igy sajat magat
// nem zarjuk ki a kozepso cella vizsgalatat.
int Board::NeighbourCount(const int x, const int y) const {
    int neighbours = 0;
    if (IsOnBoard(x, y))
        for (int i = x-1; i <= x+1; i++)
            for (int j = y-1; j <= y+1; j++)
                if (cells[i][j].GetIsBomb())
                    neighbours++;
    return neighbours;
}

Board::Board() : sizeX(defaultx), sizeY(defaulty), difficulty(defaultdiff) {
    cells = new Cell*[sizeX];
    for (int i = 0; i < sizeX; i++)
        cells[i] = new Cell[sizeY];
}

Board::Board(int x, int y, double diff)
    : sizeX(x), sizeY(y), difficulty(diff) {
    cells = new Cell*[sizeX];
    for (int i = 0; i < sizeX; i++)
        cells[i] = new Cell[sizeY];
}

bool Board::IsEmptyListed(int x, int y, const std::vector<std::array<int, 2>>& empties) const {
    for (int i = 0; i < empties.size(); i++)
        if (empties[i][0] == x && empties[i][1] == y)
            return true;
    return false;
}

void Board::CheckAdjacents(const int x, const int y, std::vector<std::array<int, 2>>& empties) const {
    empties[empties.size()] = {x,y};
    for (int i = x-1; i <= x+1; i++)
        for (int j = y-1; j <= y+1; j++) {
            if ((i == x && j == y) || !IsOnBoard(i, j) || IsEmptyListed(i, j, empties))
                continue;
            if (cells[i][j].GetNeighbourCount() == 0 && !cells[i][j].GetIsVisited())
                CheckAdjacents(i, j, empties);
            else if (cells[i][j].GetNeighbourCount() > 0)
                empties[empties.size()] = {i, j};
        }
}

Board::~Board() {
    for (int i = 0; i < defaulty; i++)
        delete[] cells[i];
    delete[] cells;
}

int Board::NeighbouringFlags(const int x, const int y) const {
    int sum = 0;
    for (int i = x-1; i <= x+1; i++)
        for (int j = y-1; j <= y+1; j++)
            if (!(i==x && j == x) && IsOnBoard(i, j) && cells[i][j].GetIsVisited())
                sum++;
    return sum;
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    os << "sizeX=" << board.sizeX << "\nsizeY=" << board.sizeY
       << "\ndifficulty=" << board.difficulty << "\n";
    for (int i = 0; i < board.sizeX; i++)
        for (int j = 0; j < board.sizeY; j++)
            os << board.cells[i][j];
    return os;
}

std::istream& operator>>(std::istream& is, Board& board) {
    char* line = nullptr;
    is.getline(line, 256);

    return is;
}
