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

    askQuestion<std::string>(user, "Username", Game::GetDefUser());
    askQuestion<int>(x, "Width", Board::GetDefaultX());
    askQuestion<int>(y, "Height", Board::GetDefaultY());
    askQuestion<double>(diff, "Difficulty (0.0 - 0.9)", Board::GetDefaultDiff());
    // stilus valtas, ez hamarabb volt, mint a tobbi...
    undo = askBoolean("enable undo [y/n]: ");

    game = new Game(x, y, diff, user, undo);

    // Innentol ncurses kiirasokat lehet csak hasznalni
    CLIRenderer gameRen(game);

    while (game->GetState() == INGAME) {
        int ch = wgetch(gameRen.gameWindow);
        gameRen.RefreshStats();
        switch (ch) {
            case KEY_LEFT:
                gameRen.MoveCursor(LEFT);
                break;
            case KEY_RIGHT:
                gameRen.MoveCursor(RIGHT);
                break;
            case KEY_UP:
                gameRen.MoveCursor(UP);
                break;
            case KEY_DOWN:
                gameRen.MoveCursor(DOWN);
                break;
            case 'f':
                game->Flaging(gameRen.cursor.x, gameRen.cursor.y);
                gameRen.WriteContent();
                break;
            case ' ':
                if (game->GetBoard().GetCell(gameRen.cursor.x, gameRen.cursor.y).GetIsVisited())
                    game->VisitedSelected(gameRen.cursor.x, gameRen.cursor.y);
                else
                    game->VisitCell(gameRen.cursor.x, gameRen.cursor.y);
                gameRen.WriteContent();
                break;
            case 'z':
                game->Undo();
                gameRen.WriteContent();
            case 'q':
                game->SaveMidGame();
                return 0;
            default:
                break;
        }
    }

    if (game->GetState() == WIN) {
        game->Win();
    }
    else /*if (game->GetState() == LOSE)*/ {
        game->Lose();
    }
#endif

    return 0;
}
