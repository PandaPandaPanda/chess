#ifndef __TextDisplay_h__
#define __TextDisplay_h__
#include <iostream>
#include <vector>

class Cell;

class TextDisplay {
  std::vector<std::vector<char>> theDisplay;
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
