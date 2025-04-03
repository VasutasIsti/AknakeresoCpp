//
// Created by istin on 2025. 04. 03..
//

#include "Cell.hpp"

Cell::Cell(int neighbourCount) : isBomb(false), isFlaged(false), isVisited(false) {
    if (neighbourCount < 0 || neighbourCount > 8)
        throw "NeighbourCount out of range!";

    this->neighbourCount = neighbourCount;
}

bool Cell::Flag() {
    isFlaged = !isFlaged;
    return isFlaged;
}

bool Cell::Visit() {
    isVisited = true;
    return isBomb;
}

std::ostream & operator<<(std::ostream &os, const Cell &cell) {
    os << '{' << cell.isBomb << ',' <<
                 cell.isFlaged << ',' <<
                 cell.isVisited << ',' <<
                 cell.neighbourCount << '}' <<
                 std::endl;
    return os;
}

/// Ha az adatfolyamon erkezo adat rossz formatumu, akkor hibat
/// dob, hiba eseten a program nem folytathato (mashol van lekezelve)
void validateInputs(char* format, int* data) {
    if (format[0] != '{' || format[4] != '}')
        throw "Invalid format!";
    if (format[1] != ',' || format[2] != ',' || format[3] != ',')
        throw "Invalid format!";
    for (int i = 0; i < 3; i++)
        if (data[i] != 0 && data[i] != 1)
            throw "Invalid format!";
    if (data[3] < -1 || data[3] > 8)
        throw "Invalid format!";
}

// Itt megszivattam magam a fancy kiirassal...
std::istream& operator>>(std::istream& is, Cell& cell) {
    char format[5];
    int data[4];
    is >> format[0] >> data[0] >> format[1] >> data[1] >> format[2] >> data[2] >> format[3] >> data[3] >> format[4];
    validateInputs(format, data);
    cell.isBomb = data[0];
    cell.isFlaged = data[1];
    cell.isVisited = data[2];
    cell.neighbourCount = data[3];
    return is;
}