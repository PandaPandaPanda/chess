#ifndef __Board_h__
#define __Board_h__
#include <vector>
#include <iostream>

class Cell;
class ChessPiece;

class Board {
  std::vector<std::vector<Cell>> grid;
  bool verify();
public:
  Board();
  const ChessPiece* getChessPiece(int r, int c) const;
  void move(std::pair<int, int> start, std::pair<int, int> dest);
  friend std::ostream& operator<<(std::ostream&, Board&); //temporary, to remove later
  void setup();
};
#endif
