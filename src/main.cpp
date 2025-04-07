#include <iostream>
#include "game.hpp"

// Amiket ugymond kotelezo. A pelda NHF fajlaibol all,
// ezek elvileg 2022-es modositasuk, remelem ez az a verzio ami kell
#define MEMTRACE

int main() {
    Cell cell1 = Cell(true);
    Cell cell2 = Cell(5);
    std::cout << cell1 << cell2 << std::endl;
    Cell cell3;
    std::cin >> cell3;
    std::cout << cell3 << std::endl;

    return 0;
}
