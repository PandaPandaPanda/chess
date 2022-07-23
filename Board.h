#ifndef __Board_h__
#define __Board_h__
#include <vector>
#include <ostream>
#include "Cell.h"

class Board {
  std::vector<std::vector<Cell>> grid;
  bool verify();
public:
  Board();
  const ChessPiece* getChessPiece(int r, int c) const;
  void move(std::pair<int, int> start, std::pair<int, int> dest);
  friend ostream& operator<<(ostream&, Board&); //temporary, to remove later
  void setup();
};
#endif
