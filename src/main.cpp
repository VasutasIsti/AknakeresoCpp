#include <iostream>

#include "templates.hpp"
#include "game.hpp"
#include "cli.hpp"
#include <fstream>

// Amiket ugymond kotelezo. A pelda NHF fajlaibol all,
// ezek elvileg 2022-es modositasuk, remelem ez az a verzio ami kell
//#define MEMTRACE

// Csak es kizarolag a (nem automatizalt) tesztelesre hasznalt makro. 
// #define NOTREADY
#ifndef CPORTA
int main() {
#ifdef NOTREADY
    Game game(5, 10, 0.3, "Stefan", true);
    std::cout << game << "\n---------------------------------\n\n";
    game.Flaging(0, 0);
    std::cout << game << "\n---------------------------------\n\n";
    game.Undo();
    std::cout << game;
#endif

#ifndef NOTREADY
    std::string user = "Player";
    int x = 0, y = 0;
    double diff = 0.0;
    bool undo;
    Game* game;

    std::ifstream file("GameState.txt");
    if (file.good() && askBoolean("Do you want to continue the last unfinished game? [y/n]: ")) {
        game = new Game();
        file >> *game;
    }
    else {
        askQuestion<std::string>(user, "Username", Game::GetDefUser());
        askQuestion<int>(x, "Width", Board::GetDefaultX());
        askQuestion<int>(y, "Height", Board::GetDefaultY());
        askQuestion<double>(diff, "Difficulty (0.0 - 0.9)", Board::GetDefaultDiff());
        // stilus valtas, ez hamarabb volt, mint a tobbi...
        undo = askBoolean("enable undo [y/n]: ");
        game = new Game(x, y, diff, user, undo);
    }
    file.close();
    // Innentol ncurses kiirasokat lehet csak hasznalni
    CLIRenderer gameRen(game);

    while (game->GetState() == INGAME || game->GetUndoHandler().GetUndoEnabled()) {
        gameRen.RefreshStats();
        int ch = wgetch(gameRen.gameWindow);
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
                break;
            case 'q':
                game->SaveMidGame();
                delete game;
                return 0;
            default:
                break;
        }
    }

    // A win es lose fuggvenyeket mar a visitCell meghivta, azokkal itt nem kell torodni.
    if (game->GetState() == WIN && !game->GetUndoHandler().GetUndoEnabled()) {
        gameRen.WinWindow();
    }
    else if (/* game->GetState() == LOSE || */ !game->GetUndoHandler().GetUndoEnabled()) {
        gameRen.LoseWindow();
    }
#endif  // NOTREADY

    delete game;

    return 0;
}
#endif  // CPORTA
