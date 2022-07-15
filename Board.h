#ifndef __Board_h__
#define __Board_h__
#include <vector>
#include "Cell.h"

class Board {
  std::vector<std::vector<Cell>> grid;
public:
  void move(int startRow, int startCol, int destRow, int destCol);
};
#endif
