#ifndef __Game_h__
#define __Game_h__
#include "Board.h"
#include "TextDisplay.h"

class Game {
  Board b;
public:
  void playTurn();
};
#endif
