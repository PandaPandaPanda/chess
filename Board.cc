#include "Board.h"
#include <iostream>
#include <string>
#include <vector>
#include <string>

using namespace std;

bool Board::verify() {
  // todo
  return true;
}

Board::Board()
{
  // To create chess pieces here and initialize cell with them inside?
  grid = vector<vector<Cell>>(8, vector<Cell>(8, Cell()));
}

const ChessPiece *Board::getChessPiece(int r, int c) const {
  return grid[r][c].getChessPiece();
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

void Board::setup() {
  string cmd;
  while (true) {
    cin >> cmd;
    if (cmd == "+") {
      char t;
      string pos;
      cin >> t >> move;
      // todo
    } else if (cmd == "-") {
      string pos;
      cin >> pos;
      // todo
    } else if (cmd == "=") {
      string color;
      cin >> color;
      // todo
    } else if (cmd == "done") {
      if (verify()) {
        break;
      } else {
        cout << "The state of the board is not valid. Make sure that" << endl;
        cout << "the board contains exactly one white king and exactly" << endl;
        cout << "one black king; that no pawns are on the first or last" << endl; 
        cout << "row of the board; and that neither king is in check." << endl;
      }
    } else {
      cout << "Invalid setup command: " << cmd << endl;
    }
  }
}
