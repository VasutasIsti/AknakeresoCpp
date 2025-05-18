#ifndef CLI_HPP
#define CLI_HPP

#ifndef CPORTA

#include "game.hpp"

// Itt volt egy majdnem 10 oranyi fejfajas, mivel a clion es az msys nem
// tudott egymassal mit kezdeni, vagy linkelni nem tudott, vagy az ncurses
// mukodese szunt meg teljesen. Ugyhogy ettol a ponttol IDE-valtas, valamint
// teljeskoru linux developementbe valtas tortent. Funy az egeszben, hogy nativ
// linux alatt is makogott csak a clion, szoval en nem ertem mi van szegeny ide-vel...
#include <ncurses.h>
#include "memtrace.h"

/// A kurzor mozgas iranyat olvashatobba tevo enumerator 
enum Direction {
	LEFT,
	UP,
	RIGHT,
	DOWN
};

/// A ncurses kurzor es a palya koordinatait kozos nevezore hozo struktura
struct Cursor {
public:
	int x = 0, y = 0;	///< A kurzor poziciojat leiro parameterek
	/// Palya oszlopszamot alakit az ncurses szamara hasznalatos x koordinata ertekre
	/// @return Megjelenitendo cella oszlopszamanak kijelzon ertelmezett pozicioja 
	int NormalX() const { return 2 + (2 * x); }
	/// Palya sorszamot alakit az ncurses szamara hasznalatos y koordinata ertekre
	/// @return Megjelenitendo cella sorszamanak kijelzon ertelmezett pozicioja
	int NormalY() const { return 1 + y; }
};

//ncurses
/// A ncurses palya kirajzolo osztaly, ami a jatek megjelenitesert felel
class CLIRenderer {
	Game* game;	///< A jatek objektum, ami a kirajzolando palyat es a statisztikakat tartalmazza

	/// @brief A cella tartalmanak megfelelo karaktert adja vissza a megjelenites szamara
	/// @param local A megjelenitendo cella koordinatait tarolo struktura
	/// @return A cella tartalmanak megfelelo karakter
	char CharToDisplay(Cursor local) const;

public:
	Cursor cursor;	///< A kurzor poziciojat leiro struktura
	WINDOW* gameWindow;	///< A palyat kirajzolo ablak
	WINDOW* statsWindow;	///< A statisztikakat kirajzolo ablak
	WINDOW* endingWindow;	///< A jatek vegen a jatek megnyereset vagy elveszteset vizualizalo ablak

	/// @brief Konstruktor, ami inicializalja a ncurses-t es a palyat kirajzolo ablakot
	/// @param game A jatek objektuma, amit megjeleniteni szeretnenk
	explicit CLIRenderer(Game* game);

	/// @brief A kurzor vizualis mozgatasanak kezdese, a kurzor eltuntetese a kijelzorol
	void EraseCursor() const;
	/// @brief A kurzor megjelenitese a kijelzon
	void WriteCursor() const;
	/// @brief A palya kirajzolasa a kijelzon
	void WriteContent() const;
	/// @brief A kurzor mozgatasa a kijelzon
	/// @param dir A kurzor mozgas iranya
	void MoveCursor(Direction dir);
	/// @brief A kurzor mozgatasa a kijelzon
	/// @param x Az oszlop sorszama (0-atol)
	/// @param y A sor sorszama (0-atol)
	void MoveCursor(int x, int y);
	/// @brief A statisztikak kirajzolasa a kijelzon
	void RefreshStats() const;
	/// @brief A nyertes jatek vege ablak kirajzolasa
	void WinWindow() const;
	/// @brief A vesztes jatek vege ablak kirajzolasa
	void LoseWindow() const;

	/// @brief Destruktor, ami felszabaditja az ncurses altal lefoglalt memoriat is
	~CLIRenderer();
};

#endif //CPORTA

#endif //CLI_HPP
