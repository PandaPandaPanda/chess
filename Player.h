#ifndef __Player_h__
#define __Player_h__
#include "ChessPiece.h"

class Player {
  virtual void doPlay() = 0;
protected:
  Player();
public:
  virtual ~Player() = 0;
  void play();
};
#endif
