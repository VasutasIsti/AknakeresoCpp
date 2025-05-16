#include "cli.hpp"

CLIGameRenderer::CLIGameRenderer(Game* game): cursor(Cursor()) {
	this->game = game;
    initscr();			  // Ncurses inicializalasa
    cbreak();             // Nyers beviteli mod
    noecho();             // Ne jelentse meg a beirt karaktereket
	window = newwin(this->game->GetBoard().GetHeight() + 2,
                   (this->game->GetBoard().GetWidth() * 2) + 3,
                   0, 0);
    wborder(window, 0, 0, 0, 0, 0, 0, 0, 0);
    keypad(window, true); // Engedelyezzuk a specialis billentyuket
	// wprintw(window, "Hello World!\n");
    // wrefresh(window);            // Frissitjuk a képernyot
    WriteContent();
    cursor.x = game->GetBoard().GetWidth() / 2;
    cursor.y = game->GetBoard().GetHeight() / 2;
    MoveCursor(cursor.x, cursor.y);
}

char CLIGameRenderer::CharToDisplay(Cursor local) const {
    if (game->GetBoard().GetCell(local.x, local.y).GetIsFlaged())
        return '#';
    if (!game->GetBoard().GetCell(local.x, local.y).GetIsVisited())
        return '-';
    if (game->GetBoard().GetCell(local.x, local.y).GetNeighbourCount() > 0)
        return game->GetBoard().GetCell(local.x, local.y).GetNeighbourCount() + '0';
    if (game->GetBoard().GetCell(local.x, local.y).GetNeighbourCount() == 0)
        return ' ';
    if (game->GetBoard().GetCell(local.x, local.y).GetIsBomb())
        return '*';
    // Barmi mas nagyon problemas
    throw std::invalid_argument("Something went wrong");
}

void CLIGameRenderer::WriteContent() const {
    Cursor local;
    for (local.x = 0; local.x < game->GetBoard().GetWidth(); local.x++)
        for (local.y = 0; local.y < game->GetBoard().GetHeight(); local.y++) {
            wmove(window, local.NormalY(), local.NormalX());
            waddch(window, CharToDisplay(local));
            wrefresh(window);
        }
    wmove(window, 0, 0);
    wrefresh(window);
}

void CLIGameRenderer::WriteCursor() const {
    wmove(window, cursor.NormalY(), cursor.NormalX() - 1);
    waddch(window, '<');
    wrefresh(window);
    wmove(window, cursor.NormalY(), cursor.NormalX() + 1);
    waddch(window, '>');
    wrefresh(window);
    wmove(window, 0, 0);
    wrefresh(window);
}

void CLIGameRenderer::EraseCursor() const {
    wmove(window, cursor.NormalY(), cursor.NormalX() -1);
    waddch(window, ' ');
    wrefresh(window);
    wmove(window, cursor.NormalY(), cursor.NormalX() + 1);
    waddch(window, ' ');
    wrefresh(window);
    wmove(window, 0, 0);
    wrefresh(window);
}

void CLIGameRenderer::MoveCursor(Direction dir) {
    if (dir == LEFT && cursor.x > 0)
        MoveCursor(cursor.x - 1, cursor.y);
    else if (dir == RIGHT && cursor.x < game->GetBoard().GetWidth() - 1)
        MoveCursor(cursor.x + 1, cursor.y);
    else if (dir == UP && cursor.y > 0)
        MoveCursor(cursor.x, cursor.y - 1);
    else if (dir == DOWN && cursor.y < game->GetBoard().GetHeight() - 1)
        MoveCursor(cursor.x, cursor.y + 1);
}

void CLIGameRenderer::MoveCursor(const int x, const int y) {
    EraseCursor();
    cursor.x = x;
    cursor.y = y;
    WriteCursor();
}

CLIGameRenderer::~CLIGameRenderer() {
    // wclear(window);
	delwin(window);
    clear();
	endwin();
}