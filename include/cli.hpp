#ifndef CLI_HPP
#define CLI_HPP

#include "game.hpp"

// Itt volt egy majdnem 10 oranyi fejfajas, mivel a clion es az msys nem
// tudott egymassal mit kezdeni, vagy linkelni nem tudott, vagy az ncurses
// mukodese szunt meg teljesen. Ugyhogy ettol a ponttol IDE-valtas, valamint
// teljeskoru linux developementbe valtas tortent. 
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

	char charToDisplay() const;

public:
	Cursor cursor;
	WINDOW* window;

	explicit CLIRenderer(Game* game);

	void WriteCursor() const;
	void WriteContent();
	void MoveCursor(Direction dir);
	void MoveCursor(int x, int y);

	~CLIRenderer();
};

#endif //CLI_HPP
