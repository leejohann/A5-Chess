#include "tile.h"
#include "piece.h"

using namespace std;

Tile::Tile() : occupied{false}, piece{nullptr} {}

void Tile::setPiece(Piece *p) {
  this->piece = p;
  this->occupied = true;
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
  if ((int) c >= 65 && (int) c <= 90) return true;
  else return false;
}

const Colour Tile::getColour() const {
  if (this->occupied) {
    if (isCapital(this->piece->getName())) return Colour::Black;
    else return Colour::White;
  }
  else return Colour::None;
}