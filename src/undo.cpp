//
// Created by vasutasisti on 2025.04.11..
//

#include "undo.hpp"

CellChange UndoHandler::Undo() {
	CellChange current = cellChanges.back();
	cellChanges.pop_back();
	return current;
}

void UndoHandler::LogFlaging(const int x, const int y) {
	if (undoEnabled)
		cellChanges.push_back((CellChange){x, y, true, true});
}

void UndoHandler::LogVisiting(const int x, const int y, const bool changedByPlayer) {
	if (undoEnabled)
		cellChanges.push_back((CellChange){x, y, changedByPlayer, false});
}

std::ostream& operator<<(std::ostream& os, const UndoHandler& undoHandler) {
	// TODO
	return os;
}

std::istream& operator>>(std::istream& is, UndoHandler& undoHandler) {
	// TODO
	return is;
}