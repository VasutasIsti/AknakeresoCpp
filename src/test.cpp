#include "gtest_lite.h"
#include "game.hpp"
#include "cell.hpp"

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
		EXPECT_STREQ("{1,0,0,-1}", oss.str().c_str());
		std::ostringstream oss2;
		Cell c2(2);
		oss2 << c2;
		EXPECT_STREQ("{0,0,0, 2}", oss2.str().c_str());
	} END

	TEST(Cell, read) {
		Cell c;
		std::istringstream iss;
		iss.str("{1,0,0,-1}");
		iss >> c;
		EXPECT_TRUE(c.GetIsBomb());
		EXPECT_FALSE(c.GetIsFlaged());
		EXPECT_FALSE(c.GetIsVisited());
		EXPECT_EQ(-1, c.GetNeighbourCount());
		Cell c2;
		std::istringstream iss2;
		iss2.str("{0,0,0, 2}");
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
		EXPECT_EQ(25,b.Size());
		EXPECT_EQ(floor(25*0.2), b.DiffToBombCount());
	} END

	TEST(Board, ctorCustom) {
		Board b(10, 10, 0.3);
		EXPECT_EQ(100,b.Size());
		EXPECT_EQ(floor(100*0.3), b.DiffToBombCount());
	} END

	TEST(Game, ctor) {
		Game g;
		EXPECT_EQ(false, g.getUndoHandler().getUndoEnabled());
		EXPECT_EQ(25, g.getBoard().Size());
		EXPECT_EQ(floor(25*0.2), g.getBoard().DiffToBombCount());
		EXPECT_STREQ("Player", g.getUsername().c_str());
		EXPECT_EQ(INGAME, g.getState());
		EXPECT_EQ(g.getBoard().DiffToBombCount(), g.getFlagsRemaining());
		EXPECT_EQ(g.getBoard().Size(), g.getNotVisiteds());
	} END

	TEST(Game, ctorCustom) {
		Game g(10, 10, 0.3, "Stefan", true);
		EXPECT_EQ(true, g.getUndoHandler().getUndoEnabled());
		EXPECT_EQ(100, g.getBoard().Size());
		EXPECT_EQ(floor(100*0.3), g.getBoard().DiffToBombCount());
		EXPECT_STREQ("Stefan", g.getUsername().c_str());
		EXPECT_EQ(INGAME, g.getState());
		EXPECT_EQ(g.getBoard().DiffToBombCount(), g.getFlagsRemaining());
		EXPECT_EQ(g.getBoard().Size(), g.getNotVisiteds());
	} END

	TEST(Game, Flaging) {
		Game g;
		g.Flaging(0, 0);
		EXPECT_EQ(true, g.getBoard().getCell(0, 0).GetIsFlaged());
		EXPECT_EQ(g.getBoard().DiffToBombCount()-1, g.getFlagsRemaining());
		g.Flaging(0, 0);
		EXPECT_EQ(false, g.getBoard().getCell(0, 0).GetIsFlaged());
		EXPECT_EQ(g.getBoard().DiffToBombCount(), g.getFlagsRemaining());
	} END

	// A cella latogatas elesben nem csak egy cellat fedez fel
	TEST(Game, VisitCell) {
		Game g;
		g.VisitCell(0, 0);
		EXPECT_EQ(true, g.getBoard().getCell(0, 0).GetIsVisited());
		EXPECT_LT(g.getBoard().Size()-1, g.getNotVisiteds());
	} END

	TEST(Undo, inside) {
		UndoHandler local;
		local.EnableUndo();
		CellChange c1(0, 0, true, true);
		local.LogFlaging(0, 0);
		CellChange c2 = local.Undo();
		EXPECT_EQ(c1, c2);
	} END




	return 0;
}