#ifndef STATE_H
#define STATE_H

#include "posn.h"

enum StateType { Request, Reply, Affirmative, Negative };
enum Colour { Black, White, None };

struct State {
  Posn destination;
  StateType type;
};

#endif