#include "TextDisplay.h"
#include "Cell.h"
#include "ChessPiece.h"
#include <vector>
#include <iostream>
using namespace std;

TextDisplay::TextDisplay() {
      theDisplay = vector<vector<string>>(8, vector<string>(8, " "));
      emojiMap[ChessType::PAWN][Color::Black] = "♟";
      emojiMap[ChessType::ROOK][Color::Black] = "♜";
      emojiMap[ChessType::KNIGHT][Color::Black] = "♞";
      emojiMap[ChessType::BISHOP][Color::Black] = "♝";
      emojiMap[ChessType::QUEEN][Color::Black] = "♛";
      emojiMap[ChessType::KING][Color::Black] = "♚";
      emojiMap[ChessType::PAWN][Color::White] = "♙";
      emojiMap[ChessType::ROOK][Color::White] = "♖";
      emojiMap[ChessType::KNIGHT][Color::White] = "♘";
      emojiMap[ChessType::BISHOP][Color::White] = "♗";
      emojiMap[ChessType::QUEEN][Color::White] = "♕";
      emojiMap[ChessType::KING][Color::White] = "♔";
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
