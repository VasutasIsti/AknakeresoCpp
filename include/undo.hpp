#ifndef UNDO_HPP
#define UNDO_HPP

#include <iostream>
#include <vector>

/// Egy cella valtozasat roggzito adatstruktura
class CellChange {
    /// CellChange-ek streamrol erkezo adatok ervenyesitese
    static void ValidateInputs(const char* format, const int* data);
public:
    int x, y;   ///< A cella koordinatai
    bool changedByPlayer;   ///< Igaz, ha az adott cella kezdte a valtozas sort.
    bool flagedOrVisited;   ///< Igaz, ha zaszlozas, hamis, ha felfedezes
    /// Default Konstruktor
    CellChange() : x(0), y(0), changedByPlayer(false), flagedOrVisited(false) {}
    /// Parameteres konstruktor
    /// @param x Az oszlop sorszama
    /// @param y A sor sorszama
    /// @param changedByPlayer A valtozast a jatekos kozvetlenul idezte elo
    /// @param flagedOrVisited Igaz, ha zaszlozas volt, hamis, ha felfedezes
    CellChange(const int x, const int y, const bool changedByPlayer, const bool flagedOrVisited)
        : x(x), y(y), changedByPlayer(changedByPlayer), flagedOrVisited(flagedOrVisited) {}

    /// Egyenloseg operator, mert sirt erta az ide...
    bool operator==(const CellChange& rhs_c) const {
        return x==rhs_c.x &&
               y==rhs_c.y &&
               changedByPlayer==rhs_c.changedByPlayer &&
               flagedOrVisited==rhs_c.flagedOrVisited;
    }
    /// Kiiro fuggveny ostream-mekre
    friend std::ostream& operator<<(std::ostream& os, const CellChange& c);
    /// Beolvaso fuggveny istream-mekkel
    friend std::istream& operator>>(std::istream& is, CellChange& c);
};

/// A visszavonasokat kezelo adatstruktura, es a hozza kapcsolodo vezerlo fuggvenyek
class UndoHandler {
    bool undoEnabled = false;   ///< A fokapcsolo
    std::vector<CellChange> cellChanges;    ///< A valtozasokat kronologikus sorrendben gyujto lista
public:
    /// A visszavonas-kezeles eletbeleptetese
    void EnableUndo() {undoEnabled = true;}
    /// A visszavonas-kezeles aktivaltsagat adja vissza
    bool GetUndoEnabled() const {return undoEnabled;}

    /// Visszaadja a legutobbi valtozast, majd azt torli a listabol
    /// @return A legutolso valtozas parametereit
    CellChange Undo();
    /// Zaszlo valtozas felvetele
    /// @param x Az oszlop sorszama
    /// @param y A sor sorszama
    void LogFlaging(int x, int y);
    /// Egy cella felfedezesenek rogzitese
    /// @param x Az oszlop sorszama
    /// @param y A sor sorszama
    /// @param changedByPlayer A cellat a jatekos fedezte fel, vagy a program fedte fel neki proceduralisan
    void LogVisiting(int x, int y, bool changedByPlayer);
    /// Kiiro fuggveny ostrem-mekre
    friend std::ostream& operator<<(std::ostream& os, const UndoHandler& undoHandler);
    /// Beolvaso fuggveny istream-mekrol
    friend std::istream& operator>>(std::istream& is, UndoHandler& undoHandler);

};

std::ostream& operator<<(std::ostream& os, const CellChange& c);
std::istream& operator>>(std::istream& is,       CellChange& c);
std::ostream& operator<<(std::ostream& os, const UndoHandler& undoHandler);
std::istream& operator>>(std::istream& is,       UndoHandler& undoHandler);

#endif //UNDO_HPP
