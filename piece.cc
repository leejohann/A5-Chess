#include "piece.h"
#include "subject.h"

Piece::Piece(char c) : name{c}, captured{false} {}

char Piece::getName() { return this->name; }

void Piece::notify(Subject& whoFrom) {
  if (whoFrom.getState().type == StateType::Request) {
    this->captured = true;
  }
}