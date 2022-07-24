#include "TextDisplay.h"
#include "Cell.h"
#include "ChessPiece.h"
#include <vector>
#include <iostream>
using namespace std;

TextDisplay::TextDisplay() {
      theDisplay = vector<vector<string>>(8, vector<string>(8, " "));
      emojiMap['P'][Color::Black] = "♟";
      emojiMap['R'][Color::Black] = "♜";
      emojiMap['N'][Color::Black] = "♞";
      emojiMap['B'][Color::Black] = "♝";
      emojiMap['Q'][Color::Black] = "♛";
      emojiMap['K'][Color::Black] = "♚";
      emojiMap['P'][Color::White] = "♙";
      emojiMap['R'][Color::White] = "♖";
      emojiMap['N'][Color::White] = "♘";
      emojiMap['B'][Color::White] = "♗";
      emojiMap['Q'][Color::White] = "♕";
      emojiMap['K'][Color::White] = "♔";
}

TextDisplay::~TextDisplay() {
  // todo
}

void TextDisplay::notify(Cell &c) {
  int row = c.getRow();
  int col = c.getCol();
  if (c.getChessPiece()) {
    theDisplay[row][col] = emojiMap[c.getChessPiece()->getType()][c.getChessPiece()->getColor()] + " ";
  } else {
    theDisplay[row][col] = "  ";
  }
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  int rowCount = 8;
  for (auto& row : td.theDisplay) {
    out << rowCount << " ";
    rowCount--;

    out << "|";
    for (auto& cell : row) {
      out << cell;
      out << "|";
    }
    out << '\n';
  }

  out << "   ";
  for (int i = 0; i < 8; i++) {
    out << (char)(i + 'a') << "  ";
  }
  out << endl;
  return out;
}
