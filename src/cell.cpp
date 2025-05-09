#include "cell.hpp"
#include <iomanip>  // a streamre iras kicsit fancybb megoldasanal hasznalva

Cell::Cell(int neighbourCount)
    : isFlaged(false), isVisited(false) {
    if (neighbourCount < 0 || neighbourCount > 8)
        throw std::invalid_argument("Cell: NeighbourCount out of range!");

    this->neighbourCount = neighbourCount;
}

Cell& Cell::operator=(const Cell& cell) {
    isFlaged = cell.GetIsFlaged();
    isVisited = cell.GetIsVisited();
    neighbourCount = cell.GetNeighbourCount();
    return *this;
}

bool Cell::Flag() {
    isFlaged = !isFlaged;
    return isFlaged;
}

bool Cell::Visit() {
    isVisited = true;
    return GetIsBomb();
}

void Cell::Undo(bool flagedOrVisited) {
    if (flagedOrVisited)
        isFlaged = !isFlaged;
    else
        isVisited = false;
}


std::ostream & operator<<(std::ostream &os, const Cell &cell) {
    os << '{' << cell.isFlaged << ',' <<
                 cell.isVisited << ',' << std::setw(2) <<
                 cell.neighbourCount << '}';
    return os;
}

void Cell::ValidateInputs(const char* format, const int* data) {
    if (format[0] != '{' || format[3] != '}')
        throw std::invalid_argument("Cell: Invalid format!");
    if (format[1] != ',' || format[2] != ',')
        throw std::invalid_argument("Cell: Invalid format!");
    for (int i = 0; i < 2; i++)
        if (data[i] != 0 && data[i] != 1)
            throw std::invalid_argument("Cell: Invalid data!");
    if (data[2] < -1 || data[2] > 8)
        throw std::invalid_argument("Cell: Invalid data!");
}

// Itt megszivattam magam a fancy kiirassal...
std::istream& operator>>(std::istream& is, Cell& cell) {
    char format[4];
    int data[3];
    is >> format[0] >> data[0] >>
          format[1] >> data[1] >>
          format[2] >> data[2] >>
          format[3];
    Cell::ValidateInputs(format, data);
    cell.isFlaged =       data[0];
    cell.isVisited =      data[1];
    cell.neighbourCount = data[2];
    return is;
}