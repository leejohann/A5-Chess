#include "board.h"
#include "piece.h"
#include "state.h"
  
using namespace std;

Board::Board() {
  for (int i = 0; i < 8; i++) {
    vector<Tile> row;
    for (int j = 0; j < 8; j++) {
      row.emplace_back(Tile());
    }
    this->grid.emplace_back(row);
  }

  this->grid[0][0].setPiece(new Piece{'R'});
  this->grid[0][1].setPiece(new Piece{'N'});
  this->grid[0][2].setPiece(new Piece{'B'});
  this->grid[0][3].setPiece(new Piece{'Q'});
  this->grid[0][4].setPiece(new Piece{'K'});
  this->grid[0][5].setPiece(new Piece{'B'});
  this->grid[0][6].setPiece(new Piece{'N'});
  this->grid[0][7].setPiece(new Piece{'R'});
  for (unsigned int i = 0; i < this->grid.size(); i++) {
    this->grid[1][i].setPiece(new Piece{'P'});
    this->grid[6][i].setPiece(new Piece{'p'});
  }

  this->grid[7][0].setPiece(new Piece{'r'});
  this->grid[7][1].setPiece(new Piece{'n'});
  this->grid[7][2].setPiece(new Piece{'b'});
  this->grid[7][3].setPiece(new Piece{'q'});
  this->grid[7][4].setPiece(new Piece{'k'});
  this->grid[7][5].setPiece(new Piece{'b'});
  this->grid[7][6].setPiece(new Piece{'n'});
  this->grid[7][7].setPiece(new Piece{'r'});
}



void Board::move(const Posn &start, const Posn &dest, bool isWhite) {
  if ((this->grid[start.x][start.y].getColour() == Colour::White && isWhite) ||
      (this->grid[start.x][start.y].getColour() == Colour::Black && !isWhite)) { 
    this->grid[dest.y][dest.x] = this->grid[start.y][start.x];
    //cout << "new piece set" << endl;
    this->grid[start.y][start.x].removePiece();
    //cout << "old piece removed" << endl;
  }
}

ostream & operator<<(ostream &out, const Board &b) {
  for (unsigned int i = 0; i < b.grid.size(); i++) {
    for (unsigned int j = 0; j < b.grid[i].size(); j++) {
      if(b.grid[i][j].isOccupied()) out << b.grid[i][j];
      else if (i % 2 != j % 2) out << "_";
      else out << " ";
    }
    out << endl;
  }
  return out;
}