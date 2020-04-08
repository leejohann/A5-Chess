#include "posn.h"

using namespace std;

Posn::Posn(int x, int y) : x{x}, y{y} {}
Posn::Posn() : x{0}, y{0} {}

Posn::Posn(const Posn &other) {
  //cout << "posn copy ctor" << endl;
  this->x = other.x;
  this->y = other.y;
  //cout << "bottom posn copy ctor" << endl;
}

bool Posn::operator==(const Posn &other) {
  //cout << "posn eq op top" << endl;
  //cout << this->x << "," << other.x << endl;
  if (this->x == other.x && this->y == other.y) {
    //cout << "op== true" << endl;
    return true;}
  else {
    //cout << "op== false" << endl;
    return false;}
}

/*
istream & operator>>(istream &in, Posn &p) {
  int x_, y_;
  std::cin >> y_;
  std::cin >> x_;
  p.x = x_;
  p.y = y_;
  return in;
}*/