#include "gtest_lite.h"
#include "game.hpp"

int main() {
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

	return 0;
}