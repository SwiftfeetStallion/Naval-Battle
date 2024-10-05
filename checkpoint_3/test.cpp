#include "src/game.hpp"
#include <gtest/gtest.h>

class WHITE_TEST : public ::testing::Test {
 protected:
  void SetUp() {
    std::vector<std::vector<std::unique_ptr<Cell>>> cells(Map::size_);
    for (size_t i = 0; i < Map::size_; ++i) {
      for (size_t j = 0; j < Map::size_; ++j) {
        cells[i].emplace_back(std::move(std::make_unique<Cell>()));
      }
    }
    map = Map(cells);
    for (int i = 0; i < 4; ++i) {
      map.markColor(i, 0, "green");
      map.getCell(i, 0).empty = false;
    }
    map.whiteSurround(ship_1);
    map.whiteSurround(ship_2);
    map.markColor(4, 4, "red");
    map.getCell(4, 4).empty = false;
  }
  void TearDown() {
  }
  std::vector<std::vector<std::unique_ptr<Cell>>> cells;
  Map map = Map(cells);
  Ship ship_1 = Ship(Coord(0, 0), Coord(3, 0), 4);
  Ship ship_2 = Ship(Coord(4, 4), Coord(4, 4), 1);
};

TEST_F(WHITE_TEST, at_the_corner) {
  ASSERT_EQ(map.getCell(0, 1).getColor(), "white");
  ASSERT_EQ(map.getCell(1, 1).getColor(), "white");
  ASSERT_EQ(map.getCell(2, 1).getColor(), "white");
  ASSERT_EQ(map.getCell(3, 1).getColor(), "white");
  ASSERT_EQ(map.getCell(4, 1).getColor(), "white");
  ASSERT_EQ(map.getCell(4, 0).getColor(), "white");
}

TEST_F(WHITE_TEST, at_the_center) {
  ASSERT_EQ(map.getCell(4, 3).getColor(), "white");
  ASSERT_EQ(map.getCell(3, 3).getColor(), "white");
  ASSERT_EQ(map.getCell(5, 3).getColor(), "white");
  ASSERT_EQ(map.getCell(3, 4).getColor(), "white");
  ASSERT_EQ(map.getCell(5, 4).getColor(), "white");
  ASSERT_EQ(map.getCell(3, 5).getColor(), "white");
  ASSERT_EQ(map.getCell(4, 5).getColor(), "white");
  ASSERT_EQ(map.getCell(5, 5).getColor(), "white");
}

TEST_F(WHITE_TEST, all_crashed) {
  ASSERT_TRUE(map.isCrashed(ship_2));
  ASSERT_FALSE(map.isCrashed(ship_1));
  ASSERT_FALSE(map.isAllCrashed());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
