#ifndef __Board_h__
#define __Board_h__
#include <vector>
#include "Cell.h"

class Board {
  std::vector<std::vector<Cell>> grid;
public:
  void move(std::pair<int, int> start, std::pair<int, int> dest);
};
#endif
