#ifndef GAME_H
#define GAME_H

#include "board.hpp"
#include "timer.hpp"
#include "undo.hpp"
#include "memtrace.h"

/// @brief A jatek allapotanak leirasara szolgalo enum.
enum GameState {
    INGAME,
    WIN,
    LOSE
};

/// Maga a jatek, a jatekos altal eloidezheto esemenyeket megvalosito fuggvenyek,
/// jatek statisztikak lakohelye.
class Game {
    UndoHandler undo;   ///< Visszavonas-kezelo
    Board board;    ///< A cellakat tartalmazo palya
    Timer timer;    ///< Egyszerusitett idomero
    std::string username;   ///< A felhasznalo neve, def. "Player"
    GameState state;    ///< Milyen allapotban van a jatek
    int flagsRemaining; ///< Hany zaszlot lehet meg elhelyezni a palyan
    int notVisiteds;    ///< Meg hany cellat kell 
    
    static std::string defUser; ///< Alapertelmezett felhasznalonev
public:
    /// Default Konstruktor
    Game();
    /// Teljes Konstruktor
    /// @param x a palya szelessege
    /// @param y a palya magassaga
    /// @param diff az aknak aranya (0.0 - 1.0)
    /// @param username A felhasznalo neve
    /// @param undoEnabled Be van-e kapcsolva a visszavonas? Ha igen, akkor a jatekot nem lehet befejezni.
    Game(int x, int y, double diff, std::string username, bool undoEnabled = false);


    /// @brief A jatekhoz tartozo visszavonas-kezelo elerese
    /// @return A jatekhoz tartozo Visszavonas-kezelo
    UndoHandler& GetUndoHandler() { return undo; }
    /// @brief A jatekhoz tartozo palya elerese
    /// @return A jatekhoz tartozo palya
    Board& GetBoard() { return board; }
    /// @brief A jatekhoz tartozo idomero elerese
    /// @return A jatekhoz tartozo idomero
    Timer& GetTimer() { return timer; }
    /// @brief A jatekhoz tartozo felhasznalonev elerese
    /// @return A jatekhoz tartozo felhasznalonev
    std::string GetUsername() const { return username; }
    /// @brief A jatekhoz tartozo allapot elerese
    /// @return A jatekhoz tartozo allapot
    GameState GetState() const { return state; }
    /// @brief A jatekban meg kiosztando zaszlok szamanak elerese
    /// @return A flagsRemaining erteke
    int GetFlagsRemaining() const { return flagsRemaining; }
    /// @brief A jatekban meg nem latogatott cellak szamanak elerese
    /// @return A notVisiteds erteke
    int GetNotVisiteds() const { return notVisiteds; }
    /// @brief A jatek alapertelmezett felhasznalonevenek elerese
    /// @return defUser erteke
    static std::string GetDefUser() {return defUser;} 

    // A fo, jatekmenetbeli funkciok

    /// Egy cella zaszlozottsaganak megvaltoztatasa
    /// @param x Az oszlop sorszama
    /// @param y A sor sorszama
    void Flaging(int x, int y);
    /// Egy cella felfedezese
    /// @param x Az oszlop sorszama
    /// @param y A sor sorszama
    void VisitCell(int x, int y, bool direct = true);
    /// Mar felfedezett, akna szomszednyi zaszlos szomszeddal rendelkezo cellara kattintva
    /// felfedezi a szomszedos nem felfedezett, nem zaszlos cellakat. Ha az ures cella, akkor
    /// felderiti az egybefuggo ures teruletet is.
    /// @param x Az oszlop sorszama
    /// @param y A sor sorszama
    void VisitedSelected(int x, int y);
    /// Visszavonas eseten a Game szintjen elvegzendo feladatokat valositja meg.
    void Undo();
    /// Nyeres eseten szukseges feladatok megvalositasa (pl. fajlmuvelet, stb.)
    void Win();
    /// Vesztes eseten szukseges feladatok megvalositasa
    void Lose();
    /// A befejezes elotti kilepeskori teendok megvalositasa
    void SaveMidGame();



    /// Kiiro fuggveny ostream-mekre
    friend std::ostream& operator<<(std::ostream& os, const Game& game);
    /// Beolvaso fuggveny istream-mekkel
    friend std::istream& operator>>(std::istream& is, Game& game);

};

std::ostream& operator<<(std::ostream& os, const Game& game);
std::istream& operator>>(std::istream& is, Game& game);

#endif //GAME_H
