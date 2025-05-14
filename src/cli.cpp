#include "cli.hpp"

CLIRenderer::CLIRenderer(Game* game): cursor(Cursor()) {
	this->game = game;
    initscr();			  // Ncurses inicializalasa
    cbreak();             // Nyers beviteli mod
    noecho();             // Ne jelentse meg a beirt karaktereket
	window = newwin(this->game->getBoard().GetHeight() + 2,
                   (this->game->getBoard().GetWidth() * 2) + 3,
                   0, 0);
    wborder(window, 0, 0, 0, 0, 0, 0, 0, 0);
    keypad(window, true); // Engedelyezzuk a specialis billentyuket
	// wprintw(window, "Hello World!\n");
    // wrefresh(window);            // Frissitjuk a képernyot
    WriteContent();
    MoveCursor(game->getBoard().GetWidth() / 2, game->getBoard().GetHeight() / 2);
}

char CLIRenderer::charToDisplay() const {
    if (game->getBoard().getCell(cursor.x, cursor.y).GetIsFlaged())
        return '#';
    if (!game->getBoard().getCell(cursor.x, cursor.y).GetIsVisited())
        return '-';
    if (game->getBoard().getCell(cursor.x, cursor.y).GetNeighbourCount() > 0)
        return game->getBoard().getCell(cursor.x, cursor.y).GetNeighbourCount() + '0';
    if (game->getBoard().getCell(cursor.x, cursor.y).GetNeighbourCount() == 0)
        return ' ';
    if (game->getBoard().getCell(cursor.x, cursor.y).GetIsBomb())
        return '*';
    // Barmi mas nagyon problemas
    throw std::invalid_argument("Something went wrong");
}

void CLIRenderer::WriteContent() {
    for (cursor.x = 0; cursor.x < game->getBoard().GetWidth(); cursor.x++)
        for (cursor.y = 0; cursor.y < game->getBoard().GetHeight(); cursor.y++) {
            wmove(window, cursor.NormalY(), cursor.NormalX());
            waddch(window, charToDisplay());
        }
    wmove(window, 0, 0);
    wrefresh(window);
}

void CLIRenderer::WriteCursor() const {
    wmove(window, cursor.NormalY(), cursor.NormalX() - 1);
    waddch(window, '<');
    wmove(window, cursor.NormalY(), cursor.NormalX() + 1);
    waddch(window, '>');
    wmove(window, 0, 0);
}

void CLIRenderer::MoveCursor(Direction dir) {
    if (dir == LEFT && cursor.x > 0)
        MoveCursor(cursor.x - 1, cursor.y);
    else if (dir == RIGHT && cursor.x < game->getBoard().GetWidth() - 1)
        MoveCursor(cursor.x + 1, cursor.y);
    else if (dir == UP && cursor.y > 0)
        MoveCursor(cursor.x, cursor.y - 1);
    else if (dir == DOWN && cursor.y < game->getBoard().GetHeight() - 1)
        MoveCursor(cursor.x, cursor.y + 1);
}

void CLIRenderer::MoveCursor(const int x, const int y) {
    cursor.x = x;
    cursor.y = y;
    WriteCursor();
}

CLIRenderer::~CLIRenderer() {
    // wclear(window);
	delwin(window);
    clear();
	endwin();
}