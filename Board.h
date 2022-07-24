#ifndef __Board_h__
#define __Board_h__
#include <vector>
#include <iostream>
#include <string>
#include "Color.h"

class Cell;
class ChessPiece;
class TextDisplay;
class Board {
  std::vector<std::vector<Cell>> grid;
  TextDisplay* td;
  std::pair<int,int> stringToCoords(std::string);
  bool checkInCheck(Color c, const ChessPiece* king) const;
public:
  Board(TextDisplay* td);
  const ChessPiece* getChessPiece(int r, int c) const;
  void move(std::pair<int, int> start, std::pair<int, int> dest);
  void addPiece(  Color pieceColor, char type, std::string pos);
  void removePiece(std::string pos);
  bool verify();
};
#endif
