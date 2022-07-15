#ifndef __Game_h__
#define __Game_h__
#include "Board.h"
#include "TextDisplay.h"
#include "Color.h"

class Game {
  Board b;
  TextDisplay t;
  Color turn;
public:
  void playTurn();
};
#endif
