#ifndef PIECE_H
#define PIECE_H

#include "state.h"
#include "observer.h"
#include <vector>

class Subject;

class Piece : public Observer {
  char name;
  bool captured;
  Posn pos;
  std::vector<Posn> range; // movement range

  public:
    Piece(char);
    Piece(char, Posn);
    ~Piece() {}
    virtual void notify(Subject&) override;
    bool inRange(Posn dest) const;

    // accessors
    char getName();
    Posn getPos();
};

#endif