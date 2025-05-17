#include "undo.hpp"

CellChange UndoHandler::Undo() {
	CellChange current = cellChanges.back();
	cellChanges.pop_back();
	return current;
}

std::ostream& operator<<(std::ostream& os, const CellChange& c) {
	os << "{" << c.x << "," <<
				 c.y << "," <<
				 c.changedByPlayer << "," <<
				 c.flagedOrVisited << "}";
	return os;
}

void CellChange::ValidateInputs(const char* format, const int* data) {
	if (format[0] != '{' || format[4] != '}')
		throw std::invalid_argument("CellChange: Invalid format!");
	if (format[1] != ',' || format[2] != ',' || format[3] != ',')
		throw std::invalid_argument("CellChange: Invalid format!");
	for (int i = 2; i < 4; i++)
		if (data[i] != 0 && data[i] != 1)
			throw std::invalid_argument("CellChange: Invalid data!");
}

std::istream& operator>>(std::istream& is, CellChange& c) {
	char format[5];
	int data[4];
	is >> format[0] >> data[0] >>
		  format[1] >> data[1] >>
		  format[2] >> data[2] >>
		  format[3] >> data[3] >>
		  format[4];
	CellChange::ValidateInputs(format, data);
	c.x = data[0];
	c.y = data[1];
	c.changedByPlayer = data[2];
	c.flagedOrVisited = data[3];
	return is;
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
	os << "CellChanges=" << undoHandler.cellChanges.size() << std::endl;
	for (CellChange c : undoHandler.cellChanges)
		os << c << " ";
	os << "\n";
	return os;
}

std::istream& operator>>(std::istream& is, UndoHandler& undoHandler) {
	std::string line;
	std::getline(is, line);
	int count = std::stoi(line.substr(12));
	if (count < 0)
		throw std::invalid_argument("Undo: Invalid data!");
	for (int i = 0; i < count; i++) {
		CellChange current;
		is >> current;
		undoHandler.cellChanges.push_back(current);
	}
	return is;
}