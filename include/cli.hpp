#ifndef CLI_HPP
#define CLI_HPP

#include "game.hpp"

// Megkattant az msys es a clion, nem tudom hogy normalisan belinkelni, hogy egy szinten legyenek
#include <ncurses.h>

struct Cursor {
	int x, y;	///< A kurzor poziciojat leiro parameterek
};

//ncurses

class CLIRenderer {
	Game* game;

public:
	Cursor cursor;

	WINDOW* window;

	explicit CLIRenderer(Game* game);

	~CLIRenderer();
};

#endif //CLI_HPP
