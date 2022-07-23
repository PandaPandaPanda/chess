#include <iostream>
#include <string>
#include <vector>
#include "Bishop.h"
#include "Board.h"
#include "Cell.h"
#include "Color.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

using namespace std;

bool Board::verify() {
  // todo
  return true;
}

Board::Board()
{
  const Color b = Color::Black;
  const Color w = Color::White;
  // grid = vector<vector<Cell>>(8, vector<Cell>(8, Cell()));
  grid = {{{new Rook{b, 0, 0}}, {new Knight{b, 0, 1}}, {new Bishop{b, 0, 2}}, {new Queen{b, 0, 3}}, {new King{b, 0, 4}}, {new Bishop{b, 0, 5}}, {new Knight{b, 0, 6}}, {new Rook{b, 0, 7}}}, 
          {{new Pawn{b, 1, 0}}, {new Pawn{b, 1, 1}}, {new Pawn{b, 1, 2}}, {new Pawn{b, 1, 3}}, {new Pawn{b, 1, 4}}, {new Pawn{b, 1, 5}}, {new Pawn{b, 1, 6}}, {new Pawn{b, 1, 7}}},
          {{}, {}, {}, {}, {}, {}, {}, {}},
          {{}, {}, {}, {}, {}, {}, {}, {}},
          {{}, {}, {}, {}, {}, {}, {}, {}},
          {{}, {}, {}, {}, {}, {}, {}, {}},
          {{new Pawn{w, 6, 0}}, {new Pawn{w, 6, 1}}, {new Pawn{w, 6, 2}}, {new Pawn{w, 6, 3}}, {new Pawn{w, 6, 4}}, {new Pawn{w, 6, 5}}, {new Pawn{w, 6, 6}}, {new Pawn{w, 6, 7}}},
          {{new Rook{w, 7, 0}}, {new Knight{w, 7, 1}}, {new Bishop{w, 7, 2}}, {new Queen{w, 7, 3}}, {new King{w, 7, 4}}, {new Bishop{w, 7, 5}}, {new Knight{w, 7, 6}}, {new Rook{w, 7, 7}}}};
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
      cin >> t >> pos;
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
