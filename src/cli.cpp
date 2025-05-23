#include "cli.hpp"
#include <sstream>

#ifndef CPORTA

CLIRenderer::CLIRenderer(Game* game): cursor(Cursor()) {
	this->game = game;
    initscr();			  // Ncurses inicializalasa
    cbreak();             // Nyers beviteli mod
    noecho();             // Ne jelentse meg a beirt karaktereket
	gameWindow = newwin(this->game->GetBoard().GetHeight() + 2,
                   (this->game->GetBoard().GetWidth() * 2) + 3,
                   0, 0);
    wborder(gameWindow, 0, 0, 0, 0, 0, 0, 0, 0);
    statsWindow = newwin(5, 20,
        0, (this->game->GetBoard().GetWidth() * 2) + 3 + 5);
    endingWindow = newwin(3, 37,
        this->game->GetBoard().GetHeight() + 2 + 1, 0);
    wborder(statsWindow, 0, 0, 0, 0, 0, 0, 0, 0);
    keypad(gameWindow, true); // Engedelyezzuk a specialis billentyuket
	// wprintw(window, "Hello World!\n");
    // wrefresh(window);            // Frissitjuk a képernyot
    WriteContent();
    RefreshStats();
    cursor.x = game->GetBoard().GetWidth() / 2;
    cursor.y = game->GetBoard().GetHeight() / 2;
    MoveCursor(cursor.x, cursor.y);
}

char CLIRenderer::CharToDisplay(Cursor local) const {
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

void CLIRenderer::WriteContent() const {
    Cursor local;
    for (local.x = 0; local.x < game->GetBoard().GetWidth(); local.x++)
        for (local.y = 0; local.y < game->GetBoard().GetHeight(); local.y++) {
            wmove(gameWindow, local.NormalY(), local.NormalX());
            waddch(gameWindow, CharToDisplay(local));
            wrefresh(gameWindow);
        }
    wmove(gameWindow, 0, 0);
    wrefresh(gameWindow);
}

void CLIRenderer::WriteCursor() const {
    wmove(gameWindow, cursor.NormalY(), cursor.NormalX() - 1);
    waddch(gameWindow, '<');
    wrefresh(gameWindow);
    wmove(gameWindow, cursor.NormalY(), cursor.NormalX() + 1);
    waddch(gameWindow, '>');
    wrefresh(gameWindow);
    wmove(gameWindow, 0, 0);
    wrefresh(gameWindow);
}

void CLIRenderer::EraseCursor() const {
    wmove(gameWindow, cursor.NormalY(), cursor.NormalX() -1);
    waddch(gameWindow, ' ');
    wrefresh(gameWindow);
    wmove(gameWindow, cursor.NormalY(), cursor.NormalX() + 1);
    waddch(gameWindow, ' ');
    wrefresh(gameWindow);
    wmove(gameWindow, 0, 0);
    wrefresh(gameWindow);
}

void CLIRenderer::MoveCursor(Direction dir) {
    if (dir == LEFT && cursor.x > 0)
        MoveCursor(cursor.x - 1, cursor.y);
    else if (dir == RIGHT && cursor.x < game->GetBoard().GetWidth() - 1)
        MoveCursor(cursor.x + 1, cursor.y);
    else if (dir == UP && cursor.y > 0)
        MoveCursor(cursor.x, cursor.y - 1);
    else if (dir == DOWN && cursor.y < game->GetBoard().GetHeight() - 1)
        MoveCursor(cursor.x, cursor.y + 1);
}

void CLIRenderer::MoveCursor(const int x, const int y) {
    EraseCursor();
    cursor.x = x;
    cursor.y = y;
    WriteCursor();
}

void CLIRenderer::RefreshStats() const {
    std::stringstream ss1, ss2, ss3;    // valamiert atmentodnek a vegere ha csak egy valtozot hasznalok
    std::string str1, str2, str3;

    wmove(statsWindow, 1, 1);
    wprintw(statsWindow, "time: ");
    ss1 << game->GetTimer().GetDeltaTime();
    ss1 >> str1;
    waddstr(statsWindow, str1.c_str());
    waddstr(statsWindow, "    ");
    wrefresh(statsWindow);
    wmove(statsWindow, 2, 1);
    wprintw(statsWindow, "flags: ");
    ss2 << game->GetFlagsRemaining();
    ss2 >> str2;
    waddstr(statsWindow, str2.c_str());
    waddstr(statsWindow, "    ");
    wrefresh(statsWindow);
    wmove(statsWindow, 3, 1);
    wprintw(statsWindow, "notVisited: ");
    ss3 << game->GetNotVisiteds();
    ss3 >> str3;
    waddstr(statsWindow, str3.c_str());
    waddstr(statsWindow, "    ");
    wrefresh(statsWindow);
}

void CLIRenderer::WinWindow() const {
    wborder(endingWindow, 0, 0, 0, 0, 0, 0, 0, 0);
    wmove(endingWindow, 0, 0);
    wprintw(endingWindow, "You won! (Press a key to continue)");
    wrefresh(endingWindow);

    wgetch(gameWindow);
}

void CLIRenderer::LoseWindow() const {
    wborder(endingWindow, 0, 0, 0, 0, 0, 0, 0, 0);
    wmove(endingWindow, 0, 0);
    wprintw(endingWindow, "You lost! (Press a key to continue)");
    wrefresh(endingWindow);
    wgetch(gameWindow);
    wclear(endingWindow);
    wborder(endingWindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(endingWindow);
}

void CLIRenderer::InformationWindow(const)

CLIRenderer::~CLIRenderer() {
    // wclear(window);
    delwin(endingWindow);
    delwin(statsWindow);
	delwin(gameWindow);
    clear();
	endwin();
}

#endif //CPORTA