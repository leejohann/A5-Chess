#ifndef STATE_H
#define STATE_H

#include "posn.h"
#include <vector>

enum StateType { Request, Reply, Affirmative, Negative };
enum Colour { Black, White, None };

struct State {
  Posn destination;
  Posn start;
  std::vector<Posn> path;
  StateType type;
  char name;
};

struct Info {
  Posn pos;
  char name;
};

#endif