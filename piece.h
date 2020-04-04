#ifndef PIECE_H
#define PIECE_H

#include "state.h"
#include "observer.h"

class Subject;

class Piece : public Observer {
  char name;
  bool captured;

  public:
    Piece(char);
    ~Piece() {}
    char getName();
    virtual void notify(Subject&) override;
};

#endif