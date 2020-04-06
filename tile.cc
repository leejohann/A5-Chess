#include "tile.h"
#include "piece.h"

using namespace std;

Tile::Tile() : occupied{false}, piece{nullptr} {}

void Tile::setPiece(Piece *p) {
  this->piece = p;
  this->occupied = true;

  // Make the piece an observer of this tile
  this->attach(this->piece);
}

ostream & operator<<(ostream &out, const Tile &t) {
  if (t.occupied) out << t.piece->getName();
  return out;
}

void Tile::removePiece() {
  this->occupied = false;
  //if(this->piece != nullptr) delete this->piece;
  //cout << "pointer deleted" << endl;
}

bool Tile::isOccupied() const {
  return occupied;
}

bool isCapital(char c) {
  if (c >= 65 && c <= 90) {
    /*cout << "capital: ";
    int num = c;
    cout << num << endl;*/
    return true;
  }
  else {
    /*cout << "lower case: ";
    int num = c;
    cout << num << endl;*/
    return false;
  }
}

const Colour Tile::getColour() const {
  if (this->occupied) {
    if (isCapital(this->piece->getName())) return Colour::Black;
    else return Colour::White;
  }
  else return Colour::None;
}

Piece * Tile::getPiece() const { return this->piece; }