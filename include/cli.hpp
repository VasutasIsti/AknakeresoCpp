#ifndef CLI_HPP
#define CLI_HPP

#include "game.hpp"
#include <ncurses/ncurses.h>

struct Cursor {
	int x, y;	///< A kurzor poziciojat leiro parameterek
};

//ncurses

class CLIRenderer {
	Game& game;
	Cursor cursor;
public:
	CLIRenderer(Game& game);

	~CLIRenderer();
};

#endif //CLI_HPP
