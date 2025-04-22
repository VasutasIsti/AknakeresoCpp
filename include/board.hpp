#ifndef BOARD_HPP
#define BOARD_HPP

#include <cmath>
#include <vector>
#include <array>

#include "cell.hpp"
#include "undo.hpp"


class Board {
    static int defaultx, defaulty;  ///< Alap palyameretek
    static double defaultdiff;      ///< Alap nehezseg

    UndoHandler& undo;
    Cell** cells;   ///< Maga a palya, indexei sorrendben: oszlop, sor
    int sizeX, sizeY;   ///< A palya szelessege, magassaga
    double difficulty;  ///< Az Aknak aranya (0.0 - 1.0)

    // segito fuggvenyek, mashol nem hasznalandok

    /// Az adott indexek a palyan vannak-e meg
    /// @param x Az oszlop sorszama
    /// @param y A sor sorszama
    /// @return Jok-e az indexek
    bool IsOnBoard(int x, int y) const;
    /// Megszamolja, hany akna szomszedja van
    /// @param x Az oszlop sorszama
    /// @param y A sor sorszama
    /// @return A szomszedos akna mezok szamat
    int NeighbourCount( int x, int y) const;

    static bool IsEmptyListed(int x, int y, const std::vector<std::array<int, 2>>& empties) ;

    int NeighbouringFlags(int x, int y) const;

    void PlaceBombs() const;

    static void ValidateInput(std::istream& input, int& x, int& y, double& diff);
public:

    /// @param undo A jatek visszavonas-kezelojenek referenciaja
    explicit Board(UndoHandler& undo);

    /// @param x A palya szelessege
    /// @param y A palya magassaga
    /// @param diff A palyan talalhato akna mezok aranya (0.0 - 1.0)
    /// @param undo A jatek visszavonas-kezelojenek referenciaja
    Board(int x, int y, double diff, UndoHandler& undo);

    /// Visszaadja a palya teljes meretet
    int Size() const {return sizeX * sizeY;}
    /// A palya nehezsegebol szamolja ki az aknak szamat
    int DiffToBombCount() const {return floor(sizeX*sizeY*difficulty);}

    /// Rekurzivan vegignezi
    /// @param x Az oszlop sorszama
    /// @param y A sor sorszama
    /// @param empties Az osszefuggo ures terulet cellai
    void CheckAdjacents(int x, int y, std::vector<std::array<int, 2>>& empties) const;

    bool Undo(const CellChange &cc) const;

    ~Board();

    Board& operator=(const Board& rhs);

    friend std::ostream& operator<<(std::ostream& os, const Board& board);
    friend std::istream& operator>>(std::istream& is, Board& board);
};



#endif //BOARD_HPP
