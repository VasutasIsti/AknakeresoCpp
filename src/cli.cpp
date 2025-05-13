#include "cli.hpp"

CLIRenderer::CLIRenderer(Game* game): cursor(Cursor()) {
	this->game = game;
    initscr();			  // Ncurses inicializalasa
    cbreak();             // Nyers beviteli mod
    noecho();             // Ne jelentse meg a beirt karaktereket
	window = newwin(10, 20, 0, 0);
    keypad(window, true); // Engedelyezzuk a specialis billentyuket
	wprintw(window, "Hello World!\n");
    wrefresh(window);            // Frissitjuk a képernyot
}



CLIRenderer::~CLIRenderer() {
	delwin(window);
	endwin();
}