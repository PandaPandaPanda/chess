#ifndef __Board_h__
#define __Board_h__
#include <vector>
#include <iostream>

class Cell;
class ChessPiece;
class TextDisplay;
class Board {
  std::vector<std::vector<Cell>> grid;
  TextDisplay* td;
  bool verify();
public:
  Board(TextDisplay* td);
  const ChessPiece* getChessPiece(int r, int c) const;
  void move(std::pair<int, int> start, std::pair<int, int> dest);
  void setup();
};
#endif
