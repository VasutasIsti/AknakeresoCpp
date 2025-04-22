#include "board.hpp"
#include <random>

int Board::defaultx = 5;
int Board::defaulty = 5;
double Board::defaultdiff = 0.2;

bool Board::IsOnBoard(const int x, const int y) const {
    if (x < 0 || y < 0 || x >= Board::sizeX || y >= Board::sizeY)
        return false;
    return true;
}

// Feltetelezve, hogy olyan cellara nem inditjuk el, ami Akna, igy sajat magat
// nem zarjuk ki a kozepso cella vizsgalatat.
int Board::NeighbourCount(const int x, const int y) const {
    if (cells[x][y].GetIsBomb())
        return -1;
    int neighbours = 0;
    if (IsOnBoard(x, y))
        for (int i = x-1; i <= x+1; i++)
            for (int j = y-1; j <= y+1; j++)
                if (IsOnBoard(i, j) && cells[i][j].GetIsBomb())
                    neighbours++;
    return neighbours;
}

Board::Board(UndoHandler& undo) : undo(undo), sizeX(defaultx), sizeY(defaulty), difficulty(defaultdiff) {
    Cell::SetUndoHandler(undo);
    cells = new Cell*[sizeX];
    for (int i = 0; i < sizeX; i++)
        cells[i] = new Cell[sizeY];
    PlaceBombs();
}

Board::Board(int x, int y, double diff, UndoHandler& undo)
    : sizeX(x), sizeY(y), difficulty(diff), undo(undo) {
    Cell::SetUndoHandler(undo);
    cells = new Cell*[sizeX];
    for (int i = 0; i < sizeX; i++)
        cells[i] = new Cell[sizeY];
    PlaceBombs();
}

bool Board::IsEmptyListed(int x, int y, const std::vector<std::array<int, 2>>& empties) {
    for (auto empty : empties)
        if (empty[0] == x && empty[1] == y)
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

void Board::PlaceBombs() const {
    int bombsToBePlaced = DiffToBombCount();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, std::max(sizeX, sizeY) - 1);
    while (bombsToBePlaced > 0) {
        int x = distrib(gen) % sizeX;
        int y = distrib(gen) % sizeY;
        if (!cells[x][y].GetIsBomb()) {
            cells[x][y] = Cell(true);
            bombsToBePlaced--;
        }
    }
    for (int i = 0; i < sizeX; i++)
        for (int j = 0; j < sizeY; j++)
            cells[i][j].SetNeighbourCount(NeighbourCount(i, j));
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
    for (int i = 0; i < board.sizeX; i++) {
        for (int j = 0; j < board.sizeY; j++)
            os << board.cells[i][j];
        os << "\n";
    }
    return os;
}

void Board::ValidateInput(std::istream& is, int& x, int& y, double& diff) {
    std::string line;

    std::getline(is, line);
    x = std::stoi(line.substr(6));
    if (x < 0)
        throw std::invalid_argument("Board: Invalid data!");
    std::getline(is, line);
    y = std::stoi(line.substr(6));
    if (y < 0)
        throw std::invalid_argument("Board: Invalid data!");
    std::getline(is, line);
    diff = std::stod(line.substr(11));
    if (diff < 0.0 || diff > 1.0)
        throw std::invalid_argument("Board: Invalid data!");
}

std::istream& operator>>(std::istream& is, Board& board) {
    int x, y;
    double diff;
    Board::ValidateInput(is, x, y, diff);

    for (int i = 0; i < board.sizeX; i++)
        delete[] board.cells[i];
    delete[] board.cells;

    board.sizeX = x;
    board.sizeY = y;
    board.difficulty = diff;
    board.cells = new Cell*[board.sizeX];
    for (int i = 0; i < board.sizeX; i++) {
        board.cells[i] = new Cell[board.sizeY];
        for (int j = 0; j < board.sizeY; j++)
            is >> board.cells[i][j];
    }
    return is;
}

bool Board::Undo(const CellChange &cc) const {
    cells[cc.x][cc.y].Undo(cc.flagedOrVisited);
    return cells[cc.x][cc.y].GetIsFlaged();
}

Board& Board::operator=(const Board& rhs) {
    if (this == &rhs)
        return *this;

    for (int i = 0; i < sizeX; i++)
        delete[] cells[i];
    delete[] cells;

    undo = rhs.undo;
    sizeX = rhs.sizeX;
    sizeY = rhs.sizeY;
    difficulty = rhs.difficulty;
    cells = new Cell*[sizeX];
    for (int i = 0; i < sizeX; i++) {
        cells[i] = new Cell[sizeY];
        for (int j = 0; j < sizeY; j++)
            cells[i][j] = rhs.cells[i][j];
    }

    return *this;
}
