#ifndef BOARD_HPP
#define BOARD_HPP

#include <cmath>
#include <vector>
#include <array>

#include "cell.hpp"
#include "undo.hpp"

/// A palyat alkoto cellakat osszefogo osztaly, nagyobb, a jatek belso mukodesehez
/// szukseges fuggvenyek lakohelye. Memoria lokalitast tekintve oszlop osszefuggo.
class Board {
    static int defaultx, defaulty;  ///< Alap palyameretek
    static double defaultdiff;      ///< Alap nehezseg

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
    int NeighbourCount(int x, int y) const;
    /// Osszefuggo ures teruletek felfedezesenek seged fuggvenye, megadja, hogy az adott
    /// cella mar meg lett-e latogatva az ures teruleten.
    /// @param x Az oszlop sorszama
    /// @param y A sor sorszama
    /// @param empties Az ures cellakat gyujto lista
    static bool IsEmptyListed(int x, int y, const std::vector<std::array<int, 2>>& empties);
    /// Megszamolja a cella koruli aknak szamat (0-8)
    /// @param x Az oszlop sorszama
    /// @param y A sor sorszama
    /// @return A cella koruli aknak szama
    int NeighbouringFlags(int x, int y) const;
    /// Elhelyezi az aknakat a palyan.
    void PlaceBombs() const;
    /// Beolvasashoz ervenyesiti az adatokat, amit az istream-rol kapott
    /// @param input A bemeneti istream referenciaja
    /// @param x A beolvasas egyik cel adat mezoje
    /// @param y A beolvasas egyik cel adat mezoje
    /// @param diff A beolvasas egyik cel adat mezoje
    static void ValidateInput(std::istream& input, int& x, int& y, double& diff);
public:
    /// Default Konstruktor
    Board();

    /// @param x A palya szelessege
    /// @param y A palya magassaga
    /// @param diff A palyan talalhato akna mezok aranya (0.0 - 1.0)
    Board(int x, int y, double diff);

    // Egy tarolt cella elerese
    Cell& getCell(const int x, const int y) const {return cells[x][y];}

    /// Visszaadja a palya teljes meretet
    int Size() const {return sizeX * sizeY;}

    int GetWidth() const {return sizeX;}

    int GetHeight() const {return sizeY;}

    static int GetDefaultX() {return defaultx;}
    static int GetDefaultY() {return defaulty;}
    static double GetDefaultDiff() {return defaultdiff;}
    /// A palya nehezsegebol szamolja ki az aknak szamat
    int DiffToBombCount() const {return floor(sizeX*sizeY*difficulty);}

    /// Rekurzivan vegignezi
    /// @param x Az oszlop sorszama
    /// @param y A sor sorszama
    /// @param empties Az osszefuggo ures terulet cellai
    void CheckAdjacents(int x, int y, std::vector<std::array<int, 2>>& empties) const;
    /// A Visszavonas palyaban bekovetkezo valtozasainak gyujto fuggvenye
    /// @param cc Az aktualis valtozast leiro adatstruktura
    /// @return A cella, zaszlozottsagat a valtozas visszaallitasa utan.
    bool Undo(const CellChange &cc) const;
    /// Destruktor
    ~Board();
    /// Ertekado operator
    /// @param rhs az ertekeket szolgaltato Board
    Board& operator=(const Board& rhs);
    /// Kiiro fuggveny ostream-mekre
    friend std::ostream& operator<<(std::ostream& os, const Board& board);
    /// Beolvaso fuggveny istrem-mekrol palyara
    friend std::istream& operator>>(std::istream& is, Board& board);
};

std::ostream& operator<<(std::ostream& os, const Board& board);
std::istream& operator>>(std::istream& is, Board& board);

#endif //BOARD_HPP
