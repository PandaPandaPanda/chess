#include "Board.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Board::Board()
{
  // To create chess pieces here and initialize cell with them inside?
  grid = vector<vector<Cell>>(8, vector<Cell>(8, Cell()));
}

void
Board::move(std::pair<int, int> start, std::pair<int, int> dest)
{
  if (grid[start.first][start.second].canMove(dest, *this)) {
    grid[start.first][start.second].movePieceTo(grid[dest.first][dest.second]);
  } else {
    cout << "Cannot place piece here";
  }
}

ostream&
operator<<(ostream& o, Board& b)
{
  // temporary for testing purposes before implementing observer pattern
  for (auto& row : b.grid) {
    for (auto& cell : row) {
      o << cell << '|';
    }
    o << '\n';
  }
  return o;
}
