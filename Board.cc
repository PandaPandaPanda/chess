#include "Board.h"
#include "Bishop.h"
#include "Cell.h"
#include "Color.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include "TextDisplay.h"
#include "sdl_wrap.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool
Board::checkInCheck(Color c, const ChessPiece* king) const
{
  for (auto row : grid) {
    for (auto cell : row) {
      const ChessPiece* p = cell.getChessPiece();
      if (p != nullptr && p->getColor() != c) {
        if (p->canMove(king->getPosition(), *this)) {
          return true;
        }
      }
    }
  }
  return false;
}

bool
Board::verify()
{
  // exactly 1 white and black king
  //  no pawns are in first or last
  // both kings are not in check
  int wKing = 0;
  int bKing = 0;
  for (auto row : grid) {
    for (auto cell : row) {
      if ((cell.getRow() == 0 || cell.getRow() == 7) && cell.getChessPiece() &&
          cell.getChessPiece()->getType() == ChessType::PAWN) {
        return false;
      }
      if (cell.getChessPiece() && cell.getChessPiece()->getType() == ChessType::KING) {

        if (cell.getChessPiece()->getColor() == Color::White) {
          ++wKing;
          if (checkInCheck(Color::White, cell.getChessPiece())) {
            return false;
          };
        } else if (cell.getChessPiece()->getColor() == Color::Black) {
          ++bKing;
          if (checkInCheck(Color::Black, cell.getChessPiece())) {
            return false;
          };
        }
      }
    }
  }
  // todo
  if (wKing != 1 || bKing != 1) {
    return false;
  }
  return true;
}
void
Board::loadAllChessPieces()
{
  scr->add_img("BP", "ChessPieces/BPawn.png");
  scr->add_img("WP", "ChessPieces/WPawn.png");
  scr->add_img("BB", "ChessPieces/BBishop.png");
  scr->add_img("WB", "ChessPieces/WBishop.png");
  scr->add_img("BN", "ChessPieces/BKnight.png");
  scr->add_img("WN", "ChessPieces/WKnight.png");
  scr->add_img("BR", "ChessPieces/BRook.png");
  scr->add_img("WR", "ChessPieces/WRook.png");
  scr->add_img("BQ", "ChessPieces/BQueen.png");
  scr->add_img("WQ", "ChessPieces/WQueen.png");
  scr->add_img("BK", "ChessPieces/BKing.png");
  scr->add_img("WK", "ChessPieces/WKing.png");
}

Board::Board(TextDisplay* td, Screen* scr)
  : td{ td }
  , scr{ scr }
{

  const Color b = Color::Black;
  const Color w = Color::White;
  grid = { { { new Rook{ b, 0, 0 } },
             { new Knight{ b, 0, 1 } },
             { new Bishop{ b, 0, 2 } },
             { new Queen{ b, 0, 3 } },
             { new King{ b, 0, 4 } },
             { new Bishop{ b, 0, 5 } },
             { new Knight{ b, 0, 6 } },
             { new Rook{ b, 0, 7 } } },
           { { new Pawn{ b, 1, 0 } },
             { new Pawn{ b, 1, 1 } },
             { new Pawn{ b, 1, 2 } },
             { new Pawn{ b, 1, 3 } },
             { new Pawn{ b, 1, 4 } },
             { new Pawn{ b, 1, 5 } },
             { new Pawn{ b, 1, 6 } },
             { new Pawn{ b, 1, 7 } } },
           { {}, {}, {}, {}, {}, {}, {}, {} },
           { {}, {}, {}, {}, {}, {}, {}, {} },
           { {}, {}, {}, {}, {}, {}, {}, {} },
           { {}, {}, {}, {}, {}, {}, {}, {} },
           { { new Pawn{ w, 6, 0 } },
             { new Pawn{ w, 6, 1 } },
             { new Pawn{ w, 6, 2 } },
             { new Pawn{ w, 6, 3 } },
             { new Pawn{ w, 6, 4 } },
             { new Pawn{ w, 6, 5 } },
             { new Pawn{ w, 6, 6 } },
             { new Pawn{ w, 6, 7 } } },
           { { new Rook{ w, 7, 0 } },
             { new Knight{ w, 7, 1 } },
             { new Bishop{ w, 7, 2 } },
             { new Queen{ w, 7, 3 } },
             { new King{ w, 7, 4 } },
             { new Bishop{ w, 7, 5 } },
             { new Knight{ w, 7, 6 } },
             { new Rook{ w, 7, 7 } } } };
  loadAllChessPieces();
  bool isWhiteCell = true;
  for (int i = 0; i < 8; ++i) {
    isWhiteCell = !isWhiteCell;
    for (int j = 0; j < 8; ++j) {
      grid[i][j].setCoords(i, j, scr, 80, isWhiteCell);
      grid[i][j].attach(td);
      grid[i][j].drawCell();
      grid[i][j].notifyTextObserver();
      isWhiteCell = !isWhiteCell;
    }
  }
}

const ChessPiece*
Board::getChessPiece(int r, int c) const
{
  return grid[r][c].getChessPiece();
}

void
Board::move(std::pair<int, int> start, std::pair<int, int> dest)
{
  grid[start.first][start.second].movePieceTo(grid[dest.first][dest.second]);
}

pair<int, int>
Board::stringToCoords(string s)
{
  int r = 7 - (s[1] - '1');
  int c = s[0] - 'a';
  if (r < 0 || r > 7 || c < 0 || c > 7) {
    return make_pair(-1, -1);
  }
  return make_pair(r, c);
}

void
Board::addPiece(Color pieceColor, char type, string pos)
{

  pair<int, int> position = stringToCoords(pos);

  int r = position.first;
  int c = position.second;
  addPiece(pieceColor, type, r, c);
}

void
Board::addPiece(Color pieceColor, char type, int r, int c)
{
  if (r == -1) {
    cout << "invalid coordinates" << endl;
    return;
  }
  switch (type) {
    case 'P':
      grid[r][c].setChessPiece(new Pawn{ pieceColor, r, c });
      break;
    case 'R':
      grid[r][c].setChessPiece(new Rook{ pieceColor, r, c });
      break;
    case 'N':
      grid[r][c].setChessPiece(new Knight{ pieceColor, r, c });
      break;
    case 'B':
      grid[r][c].setChessPiece(new Bishop{ pieceColor, r, c });
      break;
    case 'Q':
      grid[r][c].setChessPiece(new Queen{ pieceColor, r, c });
      break;
    case 'K':
      grid[r][c].setChessPiece(new King{ pieceColor, r, c });
      break;
    default:
      cout << "invalid piece" << endl;
      return;
  }
}

void
Board::addPiece(Color pieceColor, ChessType type, int r, int c)
{
  if (r == -1) {
    cout << "invalid coordinates" << endl;
    return;
  }
  switch (type) {
    case ChessType::PAWN:
      grid[r][c].setChessPiece(new Pawn{ pieceColor, r, c });
      break;
    case ChessType::ROOK:
      grid[r][c].setChessPiece(new Rook{ pieceColor, r, c });
      break;
    case ChessType::KNIGHT:
      grid[r][c].setChessPiece(new Knight{ pieceColor, r, c });
      break;
    case ChessType::BISHOP:
      grid[r][c].setChessPiece(new Bishop{ pieceColor, r, c });
      break;
    case ChessType::QUEEN:
      grid[r][c].setChessPiece(new Queen{ pieceColor, r, c });
      break;
    case ChessType::KING:
      grid[r][c].setChessPiece(new King{ pieceColor, r, c });
      break;
    default:
      cout << "invalid piece" << endl;
      return;
  }
}

void
Board::removePiece(int r, int c)
{
  grid[r][c].setChessPiece(nullptr);
}

void
Board::removePiece(string pos)
{
  pair<int, int> position = stringToCoords(pos);
  int r = position.first;
  int c = position.second;
  removePiece(r, c);
}
