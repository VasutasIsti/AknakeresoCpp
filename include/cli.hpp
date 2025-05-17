#ifndef CLI_HPP
#define CLI_HPP

#include "game.hpp"

// Itt volt egy majdnem 10 oranyi fejfajas, mivel a clion es az msys nem
// tudott egymassal mit kezdeni, vagy linkelni nem tudott, vagy az ncurses
// mukodese szunt meg teljesen. Ugyhogy ettol a ponttol IDE-valtas, valamint
// teljeskoru linux developementbe valtas tortent. Funy az egeszben, hogy nativ
// linux alatt is makogott csak a clion, szoval en nem ertem mi van szegeny ide-vel...
#include <ncurses.h>

enum Direction {
	LEFT,
	UP,
	RIGHT,
	DOWN
};

struct Cursor {
public:
	int x = 0, y = 0;	///< A kurzor poziciojat leiro parameterek
	int NormalX() const { return 2 + (2 * x); }
	int NormalY() const { return 1 + y; }
};

//ncurses

class CLIRenderer {
	Game* game;

	char CharToDisplay(Cursor local) const;

public:
	Cursor cursor;
	WINDOW* gameWindow;
	WINDOW* statsWindow;
	WINDOW* endingWindow;

	explicit CLIRenderer(Game* game);

	void EraseCursor() const;
	void WriteCursor() const;
	void WriteContent() const;
	void MoveCursor(Direction dir);
	void MoveCursor(int x, int y);
	void RefreshStats() const;
	void WinWindow() const;

	~CLIRenderer();
};

#endif //CLI_HPP
