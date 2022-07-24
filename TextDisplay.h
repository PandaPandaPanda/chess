#ifndef __TextDisplay_h__
#define __TextDisplay_h__

#include "Color.h"

#include <iostream>
#include <vector>
#include <unordered_map>

class Cell;

class TextDisplay {
  std::vector<std::vector<std::string>> theDisplay;
  std::unordered_map<char, std::unordered_map<Color, std::string>> emojiMap;

  //K = King
  //Q = Queen
  //R = Rook
  //B = Bishop
  //N = Knight
  //P = Pawn
public:
  TextDisplay();
  ~TextDisplay();

  void notify(Cell &c);

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
