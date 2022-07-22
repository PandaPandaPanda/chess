#ifndef __Side_h__
#define __Side_h__
#include "Color.h"
#include "Player.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include <vector>
class Team {
  double points;
  Color c;
  Player *p;
  std::vector<ChessPiece *> pieces; // Place king at index 0

public:
  Team(Color c);
<<<<<<< HEAD
  const ChessPiece *getKing();
  const std::vector<ChessPiece *> getPieaces();
=======
>>>>>>> f4affcd18704d4688df403cff1a199aff7d6daa8
  void setPlayer(Player *p);
  void removePiece(ChessPiece *);
  void promotePawn(Pawn *);
};
#endif
