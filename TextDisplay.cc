#include "TextDisplay.h"
#include "Cell.h"
#include "ChessPiece.h"
#include <vector>
#include <iostream>
using namespace std;

TextDisplay::TextDisplay() {
      theDisplay = vector<vector<char>>(8, vector<char>(8, ' '));
}

TextDisplay::~TextDisplay() {
  // todo
}

void TextDisplay::notify(Cell &c) {
  // todo
  int row = c.getRow();
  int col = c.getCol();
  if (c.getChessPiece()) {
    theDisplay[row][col] = c.getChessPiece()->getType();
  } else {
    theDisplay[row][col] = ' ';
  }
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  for (auto& row : td.theDisplay) {
    out << "|";
    for (auto& cell : row) {
      out << cell;
      out << "|";
    }
    out << '\n';
  }
  return out;
}
