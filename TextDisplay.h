#ifndef __TextDisplay_h__
#define __TextDisplay_h__
#include <iostream>
#include <vector>

class Cell;

class TextDisplay {
  std::vector<std::vector<char>> theDisplay;
public:
  TextDisplay();
  ~TextDisplay();

  void notify(Cell &c);

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
