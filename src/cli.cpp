#include "cli.hpp"

CLIRenderer::CLIRenderer(Game &game) {
	initscr();
}



CLIRenderer::~CLIRenderer() {
	endwin();
}
