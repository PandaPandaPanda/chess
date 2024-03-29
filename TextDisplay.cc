#include "TextDisplay.h"
#include "Cell.h"
#include "ChessPiece.h"
#include <iostream>
#include <vector>
using namespace std;

TextDisplay::TextDisplay()
{
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

void
TextDisplay::notify(Cell& c)
{
  int row = c.getRow();
  int col = c.getCol();
  if (c.getChessPiece()) {
    theDisplay[row][col] =
      emojiMap[c.getChessPiece()->getType()][c.getChessPiece()->getColor()] +
      " ";
    c.drawPiece();
  } else {
    c.resetCell();
    theDisplay[row][col] = "  ";
  }
}

ostream&
operator<<(ostream& out, const TextDisplay& td)
{
  for (int r = 0; r < 8; ++r) {
    out << 8 - r << " "; // index to number
    out << "|";
    for (auto& cell : td.theDisplay[r]) {
      out << cell;
      out << "|";
    }
    out << '\n';
  }

  out << "   ";
  char toOutput = 'a';
  for (int i = 0; i < 8; i++) {
    out << toOutput << "  ";
    toOutput += 1;
  }
  out << endl;
  return out;
}
