#ifndef PIECE_H
#define PIECE_H

#include "state.h"
#include "observer.h"
#include "subject.h"
#include <vector>

class Subject;

class Piece : public Observer, public Subject {
  char name;
  bool captured;
  Posn pos;
  std::vector<Posn> range; // movement range

  public:
    Piece(char);
    Piece(char, Posn);
    ~Piece() {}
    virtual void notify(Subject&) override;
    virtual Info getInfo() const override;
    bool inRange(Posn dest) const;
    void isCaptured();

    // accessors
    char getName();
    Posn getPos();
};

#endif