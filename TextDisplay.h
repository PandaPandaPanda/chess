#ifndef __TextDisplay_h__
#define __TextDisplay_h__
#include "vector"

class TextDisplay {
  std::vector<std::vector<char>> theDisplay;
public:
  TextDisplay(int n);
  ~TextDisplay();

  void notify(Cell &c) override;

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
