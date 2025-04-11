//
// Created by vasutasisti on 2025.04.11..
//

#ifndef UNDO_HPP
#define UNDO_HPP

#include "cell.hpp"
#include <vector>

class CellChange {
public:
    int x, y;   ///< A cella koordinatai
    bool changedByPlayer;   ///< Igaz, ha az adott cella kezdte a valtozas sort.
    bool flagedOrVisited;   ///< Igaz, ha zaszlozas, hamis, ha felfedezes
    CellChange(int x, int y, bool changedByPlayer, bool flagedOrVisited)
        : x(x), y(y), changedByPlayer(changedByPlayer), flagedOrVisited(flagedOrVisited) {}
};

class UndoHandler {
    std::vector<CellChange> cellChanges;
public:
    UndoHandler() {};
    void Undo();
    void LogFlaging(int x, int y);
    void LogVisiting(int x, int y, bool changedByPlayer);


};
#endif //UNDO_HPP
