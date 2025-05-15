#include <iostream>

#include "templates.hpp"
#include "game.hpp"
#include "cli.hpp"

// Amiket ugymond kotelezo. A pelda NHF fajlaibol all,
// ezek elvileg 2022-es modositasuk, remelem ez az a verzio ami kell
//#define MEMTRACE

#define READY

int main() {
#ifndef READY
    Game game(5, 10, 0.3, "Stefan", true);
    std::cout << game << "\n---------------------------------\n\n";
    game.Flaging(0, 0);
    std::cout << game << "\n---------------------------------\n\n";
    game.Undo();
    std::cout << game;
#endif

#ifdef READY
    std::string user = "Player";
    int x = 0, y = 0;
    double diff = 0.0;
    bool undo;
    Game* game;

    askQuestion<std::string>(user, "Username", Game::getDefUser());
    askQuestion<int>(x, "Width", Board::GetDefaultX());
    askQuestion<int>(y, "Height", Board::GetDefaultY());
    askQuestion<double>(diff, "Difficulty (0.0 - 0.9)", Board::GetDefaultDiff());
    // stilus valtas, ez hamarabb volt, mint a tobbi... a tobbi meg egy kudarc lett xd
    undo = askBoolean("enable undo [y/n]: ");

    // Nem lehet nullas ertek egyik sem. Ha megis az, akkor default ertekekkel indul el a program.
    if (x == 0 || y == 0 || diff == 0.0)
        game = new Game();
        if (undo)
            game->getUndoHandler().EnableUndo();
    else
        game = new Game(x, y, diff, user, undo);

    // Innentol ncurses kiirasokat lehet csak hasznalni
    CLIRenderer renderer(game);
    renderer.WriteContent();
    renderer.WriteCursor();

    while (game->getState() == INGAME) {
        int ch = wgetch(renderer.window);
        switch (ch) {
            case KEY_LEFT:
                renderer.MoveCursor(LEFT);
                break;
            case KEY_RIGHT:
                renderer.MoveCursor(RIGHT);
                break;
            case KEY_UP:
                renderer.MoveCursor(UP);
                break;
            case KEY_DOWN:
                renderer.MoveCursor(DOWN);
                break;
            case 'f':
                game->Flaging(renderer.cursor.x, renderer.cursor.y);
                break;
            case ' ':
                game->VisitCell(renderer.cursor.x, renderer.cursor.y);
                break;
            case 'q':
                game->SaveMidGame();
                return 0;
            default:
                break;
        }
        renderer.WriteContent();
    }

    //wprintw(renderer.window, "maybe it's workin'");
    wrefresh(renderer.window);

#endif

    return 0;
}
