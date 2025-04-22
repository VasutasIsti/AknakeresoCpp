#ifndef UNDO_HPP
#define UNDO_HPP

#include <ostream>
#include <vector>

class CellChange {
public:
    int x, y;   ///< A cella koordinatai
    bool changedByPlayer;   ///< Igaz, ha az adott cella kezdte a valtozas sort.
    bool flagedOrVisited;   ///< Igaz, ha zaszlozas, hamis, ha felfedezes
    CellChange() : x(0), y(0), changedByPlayer(false), flagedOrVisited(false) {}
    CellChange(int x, int y, bool changedByPlayer, bool flagedOrVisited)
        : x(x), y(y), changedByPlayer(changedByPlayer), flagedOrVisited(flagedOrVisited) {}
};

class UndoHandler {
    bool undoEnabled = false;
    std::vector<CellChange> cellChanges;
public:
    void EnableUndo() {undoEnabled = true;}
    /// Visszaadja a legutobbi valtozast, majd azt torli a listabol
    /// @return A legutolso valtozas parametereit
    CellChange Undo();
    void LogFlaging(int x, int y);
    void LogVisiting(int x, int y, bool changedByPlayer);

    friend std::ostream& operator<<(std::ostream& os, const UndoHandler& undoHandler);
    friend std::istream& operator>>(std::istream& is, UndoHandler& undoHandler);

};
#endif //UNDO_HPP
