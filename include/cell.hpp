#ifndef CELL_HPP
#define CELL_HPP

#include <iostream>
#include "undo.hpp"

/// A palyat alkoto cellak
class Cell {
    bool isBomb;    ///< Az adott cella Akna-e
    bool isFlaged;  ///< Az adott cella meg van-e jelolve
    bool isVisited; ///< Az adott cella fel van-e mar fedve
    int neighbourCount; ///< Hany szomszedos Akna cella van
    static UndoHandler& undo;   ///< Visszavonas-kezelo referenciaja

    /// Ha az adatfolyamon erkezo adat rossz formatumu, akkor hibat
    /// dob, hiba eseten a program nem folytathato (mashol van lekezelve)
    static void ValidateInputs(const char* format, const int* data);


public:

    /// Default konstruktor\n
    /// Alapvetoen egy "nemAkna", "nullaAknaSzomszed"-dal rendelkezo cellat hoz letre
    Cell() : isBomb(false), isFlaged(false), isVisited(false), neighbourCount(0) {};
    /// Akna konstruktor\n
    /// Akna cellak neighbourCount-ja alapertelmezetten -1
    /// @param isBomb Az adott cella Akna legyen-e
    explicit Cell(bool isBomb)
        : isBomb(isBomb), isFlaged(false), isVisited(false), neighbourCount(isBomb?-1:0) {};
    /// Egyszeru konstruktor\n
    /// Ha esetleg mar tudhato a cella osszes szomszedjanak Akna volta
    /// @param neighbourCount Az adott cellanak hany Akna szomszedja van
    explicit Cell(int neighbourCount);
    /// Ertekado operator
    /// @param cell A masolashoz hasznalatos cella
    Cell& operator=(const Cell& cell);

    /// Megvaltoztatja a cella zaszlozasi allapotat
    /// @return A zaszla beallitas utani allapotat
    bool Flag();
    /// Felfedi a cellat
    /// @return A felfedett cella akna voltat
    bool Visit();

    /// Visszaadja, hogy az adott cella Akna-e
    /// @return isBomb erteke
    bool GetIsBomb() const {return isBomb;}
    /// Visszaadja, hogy a cella zaszlozott-e
    /// @return isFlaged erteke
    bool GetIsFlaged() const {return isFlaged;}
    /// Visszaadja, hogy a cella fel let-e mar fedezve
    /// @return isVisited erteke
    bool GetIsVisited() const {return isVisited;}
    /// Beallitja a neigbourCount erteket
    /// @param n A szomszedos aknak szama
    void SetNeighbourCount(const int n) {neighbourCount = n;}
    /// Lekeri a neigbourCount erteket
    /// @return A szomszedos Aknak darabszamat
    int GetNeighbourCount() const {return neighbourCount;}

    /// A statikus Visszavonas-kezelo beallitasa
    static void SetUndoHandler(const UndoHandler& uh) {undo = uh;}

    /// A visszavonas muveletet megvalosito fuggveny, egy cella
    /// @param flagedOrVisited Igaz, ha zaszlozas volt, hamis, ha felfedes
    void Undo(bool flagedOrVisited);

    /// Cella teljes tartalmanak kiirasa
    /// @param os A kiirast vegzo adatfolyam
    /// @param cell A kiirando cella
    friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
    /// Cella tartalmanak feltoltese adatfolyambol
    /// @param is A beolvasast vegzo adatfolyam
    /// @param cell A cella, aminek erteket akarunk igy adni
    friend std::istream& operator>>(std::istream& is, Cell& cell);
};

#endif //CELL_HPP
