#include "posn.h"

using namespace std;

Posn::Posn(int x, int y) : x{x}, y{y} {}
//Posn::Posn() : x{0}, y{0} {}
/*
istream & operator>>(istream &in, Posn &p) {
  int x_, y_;
  std::cin >> y_;
  std::cin >> x_;
  p.x = x_;
  p.y = y_;
  return in;
}*/