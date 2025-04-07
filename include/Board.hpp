//
// Created by istin on 2025. 04. 03..
//

#ifndef BOARD_HPP
#define BOARD_HPP

#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "Cell.hpp"

class Board {
    static int defaultx, defaulty;  ///< Alap palyameretek
    static double defaultdiff;      ///< Alap nehezseg

    Cell** cells;   ///< Maga a palya, indexei sorrendben: oszlop, sor
    int sizeX, sizeY;   ///< A palya szelessege, magassaga
    double difficulty;  ///< Az Aknak aranya (0.0 - 1.0)
    int bombs;  ///< Az Aknak szama

    // segito fuggvenyek, mashol nem hasznalandok
    /// A palya nehezsegebol szamolja ki az aknak szamat
    inline int diffToBombCount() const {return floor(sizeX*sizeY*difficulty);}
    /// Az aknak szamabol adja meg a nehezseget
    inline double bombCountToDiff() const  {return (double)bombs/sizeX*sizeY;}

    /// Az adott indexek a palyan vannak-e meg
    /// @param x Az oszlop sorszama
    /// @param y A sor sorszama
    /// @return Jok-e az indexek
    bool isOnBoard(const int x, const int y) const;
    /// Megszamolja, hany akna szomszedja van
    /// @param x Az oszlop sorszama
    /// @param y A sor sorszama
    /// @return A szomszedos akna mezok szamat
    int neighbourCount( int x, int y) const;
    bool isEmptyListed(int x, int y, const std::vector<std::array<int, 2>>& empties) const;

public:

    /// Default Konstruktor
    Board();

    /// Parameteres Konstruktor
    /// @param x A palya szelessege
    /// @param y A palya magassaga
    /// @param diff A palyan talalhato akna mezok aranya (0.0 - 1.0)
    Board(int x, int y, double diff);

    /// Rekurzivan vegignezi
    /// @param x Az oszlop sorszama
    /// @param y A sor sorszama
    void CheckAdjacents(int x, int y, std::vector<std::array<int, 2>>& empties) const;

    ~Board();
};



#endif //BOARD_HPP
