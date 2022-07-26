#ifndef __Board_h__
#define __Board_h__
#include "ChessPiece.h"
#include "Color.h"
#include <iostream>
#include <string>
#include <vector>

class Cell;
class ChessPiece;
class TextDisplay;
class Screen;
class Board
{
  std::vector<std::vector<Cell>> grid;
  TextDisplay* td;
  Screen* scr;
  std::pair<int, int> stringToCoords(std::string);
  void loadAllChessPieces();

public:
  Board(TextDisplay* td, Screen* scr);
  ~Board();
  const ChessPiece* getChessPiece(int r, int c) const;
  bool checkInCheck(Color c, const ChessPiece* king) const;
  void move(std::pair<int, int> start, std::pair<int, int> dest);
  void addPiece(Color pieceColor, char type, int r, int c);
  void addPiece(Color pieceColor, ChessType type, int r, int c);
  void addPiece(Color pieceColor, char type, std::string pos);
  void removePiece(int r, int c);
  void removePiece(std::string pos);
  bool verify();
};
#endif
