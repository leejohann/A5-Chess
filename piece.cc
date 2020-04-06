#include "piece.h"
#include "subject.h"

using namespace std;

vector<Posn> calculateRange(char c) {
  vector<Posn> retval;
  if (c == 'r' || c == 'R') {
    for (int i = -8; i < 16; i++) {
      retval.emplace_back(Posn{i,0});
      retval.emplace_back(Posn{0,i});
    }
  }
  else if (c == 'n' || c == 'N') {
    retval.emplace_back(Posn{2,1});
    retval.emplace_back(Posn{1,2});
    retval.emplace_back(Posn{-2,1});
    retval.emplace_back(Posn{-1,2});
    retval.emplace_back(Posn{2,-1});
    retval.emplace_back(Posn{1,-2});
    retval.emplace_back(Posn{-1,-2});
    retval.emplace_back(Posn{-2,-1});
  }
  else if (c == 'k' || c == 'K') {
    retval.emplace_back(Posn{0,1});
    retval.emplace_back(Posn{1,0});
    retval.emplace_back(Posn{1,1});
    retval.emplace_back(Posn{-1,-1});
    retval.emplace_back(Posn{1,-1});
    retval.emplace_back(Posn{-1,1});
    retval.emplace_back(Posn{0,-1});
    retval.emplace_back(Posn{-1,0});
  }
  else if (c == 'q' || c == 'Q') {
    for (int i = -8; i < 16; i++) {
      retval.emplace_back(Posn{i,0});
      retval.emplace_back(Posn{0,i});
      retval.emplace_back(Posn{i,i});
    }
  }
  else if (c == 'b' || c == 'B') {
    for (int i = -8; i < 16; i++) {
      retval.emplace_back(Posn{i,i});
    }
  }
  else if (c == 'p' || c == 'P') {
    retval.emplace_back(Posn{0,1});
    retval.emplace_back(Posn{0,2});
  }
  return retval;
}

Piece::Piece(char c) : name{c}, captured{false}, pos{Posn{0,0}}, range{calculateRange(c)} {}
Piece::Piece(char c, Posn p) : name{c}, captured{false}, pos{p}, range{calculateRange(c)} {}

char Piece::getName() { return this->name; }

void Piece::notify(Subject& whoFrom) {
  if (whoFrom.getState().type == StateType::Request) {
    this->captured = true;
  }
}

bool Piece::inRange(Posn dest) const {
  for (unsigned int i = 0; i < this->range.size(); i++) {
    int x = this->pos.x + this->range[i].x;
    int y = this->pos.y + this->range[i].y;
    if (x == dest.x && y == dest.y) return true;
  }
  return false;
}

Posn Piece::getPos() { return this->pos; }