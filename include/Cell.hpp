//
// Created by istin on 2025. 04. 03.
//

#ifndef CELL_HPP
#define CELL_HPP

#include <iostream>

/// A palyat alkoto cellak
class Cell {
    bool isBomb;    ///< Az adott cella Akna-e
    bool isFlaged;  ///< Az adott cella meg van-e jelolve
    bool isVisited; ///< Az adott cella fel van-e mar fedve
    int neighbourCount; ///< Hany szomszedos Akna cella van
public:

    /// Default konstruktor\n
    /// Alapvetoen egy "nemAkna", "nullaAknaSzomszed"-dal rendelkezo cellat hoz letre
    /// @param isBomb Az adott cella Akna legyen-e
    /// @param neighbourCount Az adott cellanak hany Akna szomszedja van
    Cell() : isBomb(false), isFlaged(false), isVisited(false), neighbourCount(0) {};
    Cell(bool isBomb) : isBomb(isBomb), isFlaged(false), isVisited(false), neighbourCount(-1) {};
    Cell(int neighbourCount);

    /// Megvaltoztatja a cella zaszlozasi allapotat
    /// @return A zaszla beallitas utani allapotat
    bool Flag();

    /// Felfedi a cellat
    /// @return A felfedett cella akna voltat
    bool Visit();

    /// Beallitja a neigbourCount erteket
    /// @param n A szomszedos aknak szama
    void setNeighbourCount(const int n) {neighbourCount = n;}

    /// Lekeri a neigbourCount erteket
    /// @return A szomszedos Aknak darabszamat
    int getNeighbourCount() const {return neighbourCount;}

    /// Cella teljes tartalmanak kiirasa
    friend std::ostream& operator<<(std::ostream& os, const Cell& cell);

    /// Cella tartalmanak feltoltese adatfolyambol
    friend std::istream& operator>>(std::istream& is, Cell& cell);
};


#endif //CELL_HPP
