#ifndef GAME_H
#define GAME_H

#include "board.hpp"
#include "timer.hpp"
#include "undo.hpp"


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
    
    static std::string defUser;
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


    // CSAK TESZTELESRE (egyenlore)
    UndoHandler& GetUndoHandler() { return undo; }
    Board& GetBoard() { return board; }
    Timer& GetTimer() { return timer; }
    std::string GetUsername() const { return username; }
    GameState GetState() const { return state; }
    int GetFlagsRemaining() const { return flagsRemaining; }
    int GetNotVisiteds() const { return notVisiteds; }
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
