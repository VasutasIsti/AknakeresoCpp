#include "cli.hpp"

CLIRenderer::CLIRenderer(Game &game): game(game), cursor(Cursor()) {
	std::cout << "InitScreen" << std::endl;
	window = initscr();
	printw("cbreak");
	cbreak();
	printw("noecho");
	noecho();
	printw("keypad");
	keypad(stdscr, true);
	printw("clear");
	getch();
}



CLIRenderer::~CLIRenderer() {

	endwin();
}
