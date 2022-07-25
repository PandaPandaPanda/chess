#ifndef __TextDisplay_h__
#define __TextDisplay_h__

#include "ChessPiece.h"
#include "Color.h"

#include <iostream>
#include <unordered_map>
#include <vector>

class Cell;

class TextDisplay
{
  std::vector<std::vector<std::string>> theDisplay;
  std::unordered_map<ChessType, std::unordered_map<Color, std::string>>
    emojiMap;

  // K = King
  // Q = Queen
  // R = Rook
  // B = Bishop
  // N = Knight
  // P = Pawn
public:
  TextDisplay();

  void notify(Cell& c);

  friend std::ostream& operator<<(std::ostream& out, const TextDisplay& td);
};
#endif
