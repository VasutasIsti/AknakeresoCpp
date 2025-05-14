#include <iostream>
#include <limits>

#include "game.hpp"
#include "cli.hpp"

// Amiket ugymond kotelezo. A pelda NHF fajlaibol all,
// ezek elvileg 2022-es modositasuk, remelem ez az a verzio ami kell
//#define MEMTRACE

//#define READY

bool askBoolean(const char* question) {
    std::string answer;
    while (true) {
        std::cout << question;
        std::getline(std::cin, answer);
        if (answer.empty()) return true;
        if (answer.length() == 1) {
            if (answer[0] == 'Y' || answer[0] == 'y')
                return true;
            if (answer[0] == 'N' || answer[0] == 'n')
                return false;
        }
        std::cout << "Invalid input. Please try again." << std::endl;
    }
}

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
    std::string user;
    int x = 0, y = 0;
    double diff = 0;
    bool undo;
    Game* game;

    std::cout << "Username: ";               std::cin >> user;
    std::cout << "width: ";                  std::cin >> x;
    std::cout << "height: ";                 std::cin >> y;
    std::cout << "difficulty (0.0 - 0.9): "; std::cin >> diff;

    // Hogy ne vegye be az elozo kerdes enteret mint ervenyes igen valasz
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    undo = askBoolean("enable undo [y/n]: ");

    if (x == 0 || y == 0 || diff == 0.0)
        game = new Game();
    else
        game = new Game(x, y, diff, user, undo);

    // Innentol ncurses kiirasokat lehet csak hasznalni
    CLIRenderer renderer(game);

    wprintw(renderer.window, "maybe it's workin'");
    wrefresh(renderer.window);

#endif

    return 0;
}
