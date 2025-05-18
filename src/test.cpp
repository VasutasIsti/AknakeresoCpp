#include "gtest_lite.h"
#include "game.hpp"
#include "cell.hpp"
#include "unistd.h"

#define CPORTA

#ifdef CPORTA
int main() {
	UndoHandler undo;

	TEST(Cell, ctor) {
		Cell c;
		EXPECT_FALSE(c.GetIsBomb());
		EXPECT_FALSE(c.GetIsFlaged());
		EXPECT_FALSE(c.GetIsVisited());
		EXPECT_EQ(0, c.GetNeighbourCount());
	} END

	TEST(Cell, ctorBomb) {
		Cell c(true);
		EXPECT_TRUE(c.GetIsBomb());
		EXPECT_FALSE(c.GetIsFlaged());
		EXPECT_FALSE(c.GetIsVisited());
		EXPECT_EQ(-1, c.GetNeighbourCount());
		Cell c2(false);
		EXPECT_FALSE(c2.GetIsBomb());
		EXPECT_FALSE(c2.GetIsFlaged());
		EXPECT_FALSE(c2.GetIsVisited());
		EXPECT_EQ(0, c2.GetNeighbourCount());
	} END

	TEST(Cell, ctorNeighbour) {
		Cell c(2);
		EXPECT_FALSE(c.GetIsBomb());
		EXPECT_FALSE(c.GetIsFlaged());
		EXPECT_FALSE(c.GetIsVisited());
		EXPECT_EQ(2, c.GetNeighbourCount());
	} END

	TEST(Cell, write) {
		Cell c(true);
		std::ostringstream oss;
		oss << c;
		EXPECT_STREQ("{0,0,-1}", oss.str().c_str());
		std::ostringstream oss2;
		Cell c2(2);
		oss2 << c2;
		EXPECT_STREQ("{0,0, 2}", oss2.str().c_str());
	} END

	TEST(Cell, read) {
		Cell c;
		std::istringstream iss;
		iss.str("{0,0,-1}");
		iss >> c;
		EXPECT_TRUE(c.GetIsBomb());
		EXPECT_FALSE(c.GetIsFlaged());
		EXPECT_FALSE(c.GetIsVisited());
		EXPECT_EQ(-1, c.GetNeighbourCount());
		Cell c2;
		std::istringstream iss2;
		iss2.str("{0,0, 2}");
		iss2 >> c2;
		EXPECT_FALSE(c2.GetIsBomb());
		EXPECT_FALSE(c2.GetIsFlaged());
		EXPECT_FALSE(c2.GetIsVisited());
		EXPECT_EQ(2, c2.GetNeighbourCount());
	} END

	// A palya teszteles, mivel az aknak veletlenszeruen vannak lerakva, elegge szegenyes
	// TODO Egy nem a veletlenre bizott aknalerako fuggveny megalkotasa tesztelesi cellal

	TEST(Board, ctor) {
		Board b;
		// Amig nem valtozik meg a default meret es
		EXPECT_EQ(25, b.Size());
		EXPECT_EQ(floor(25*0.2), b.DiffToBombCount());
	} END

	TEST(Board, ctorCustom) {
		Board b(10, 10, 0.3);
		EXPECT_EQ(100,b.Size());
		EXPECT_EQ(floor(100*0.3), b.DiffToBombCount());
	} END

	TEST(Game, ctor) {
		Game g;
		EXPECT_EQ(false, g.GetUndoHandler().GetUndoEnabled());
		EXPECT_EQ(25, g.GetBoard().Size());
		EXPECT_EQ(floor(25*0.2), g.GetBoard().DiffToBombCount());
		EXPECT_STREQ("Player", g.GetUsername().c_str());
		EXPECT_EQ(INGAME, g.GetState());
		EXPECT_EQ(g.GetBoard().DiffToBombCount(), g.GetFlagsRemaining());
		EXPECT_EQ(g.GetBoard().Size() - g.GetFlagsRemaining(), g.GetNotVisiteds());
	} END

	TEST(Game, ctorCustom) {
		Game g(10, 10, 0.3, "Stefan", true);
		EXPECT_EQ(true, g.GetUndoHandler().GetUndoEnabled());
		EXPECT_EQ(100, g.GetBoard().Size());
		EXPECT_EQ(floor(100*0.3), g.GetBoard().DiffToBombCount());
		EXPECT_STREQ("Stefan", g.GetUsername().c_str());
		EXPECT_EQ(INGAME, g.GetState());
		EXPECT_EQ(g.GetBoard().DiffToBombCount(), g.GetFlagsRemaining());
		EXPECT_EQ(g.GetBoard().Size() - g.GetFlagsRemaining(), g.GetNotVisiteds());
	} END

	TEST(Game, Flaging) {
		Game g;
		g.Flaging(0, 0);
		EXPECT_EQ(true, g.GetBoard().GetCell(0, 0).GetIsFlaged());
		EXPECT_EQ(g.GetBoard().DiffToBombCount()-1, g.GetFlagsRemaining());
		g.Flaging(0, 0);
		EXPECT_EQ(false, g.GetBoard().GetCell(0, 0).GetIsFlaged());
		EXPECT_EQ(g.GetBoard().DiffToBombCount(), g.GetFlagsRemaining());
	} END

	// A cella latogatas elesben nem csak egy cellat fedez fel
	TEST(Game, VisitCell) {
		Game g;
		g.VisitCell(0, 0);
		EXPECT_EQ(true, g.GetBoard().GetCell(0, 0).GetIsVisited());
		EXPECT_GT(g.GetBoard().Size()-1, g.GetNotVisiteds());
	} END

	TEST(Undo, inside) {
		UndoHandler local;
		local.EnableUndo();
		CellChange c1(0, 0, true, true);
		local.LogFlaging(0, 0);
		CellChange c2 = local.Undo();
		EXPECT_EQ(c1, c2);
	} END

	// VAN SLEEP
	TEST(Timer, ReadWrite) {
		Timer t1;
		std::stringstream ss;
		ss << t1;
		time_t t1delta = t1.GetDeltaTime();
		sleep(2);
		Timer t2;
		ss >> t2;
		EXPECT_LT(t1.GetT0(), t2.GetT0());
		EXPECT_EQ(t1delta, t2.GetDeltaTime());
	} END

	TEST(Game, ReadWrite) {
		Game game1(10, 12, 0.2345, "Jatekos", true);
		std::stringstream ss;
		ss << game1;
		Game game2;
		ss >> game2;
		// Legalabb az elso sor stimmel-e
		for (size_t i = 0; i < 10; i++)
			EXPECT_EQ(game1.GetBoard().GetCell(i, 0).GetNeighbourCount(), game2.GetBoard().GetCell(i, 0).GetNeighbourCount());
		
		EXPECT_STREQ(game1.GetUsername().c_str(), game2.GetUsername().c_str());
	} END

	return 0;
}

#endif