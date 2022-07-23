#ifndef __Player_h__
#define __Player_h__
#include "ChessPiece.h"

enum PlayerType {
  H,
  C
};

class Player {
  virtual void doPlay() = 0;
  virtual PlayerType doGetType() = 0;
protected:
  Player();
public:
  virtual ~Player() = 0;
  void play();
  PlayerType getType();
};
#endif
