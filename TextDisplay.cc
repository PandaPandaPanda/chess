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
  for (int r = 7; r >= 0; r--) {
    out << r + 1 << " "; // index to number
    out << "|";
    for (auto& cell : td.theDisplay[r]) {
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
