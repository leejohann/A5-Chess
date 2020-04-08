#ifndef POSN_H
#define POSN_H

#include <iostream>

class Posn {
  public:
    int x, y;
    Posn();
    Posn(int x, int y);
    Posn(const Posn&);
    bool operator==(const Posn&);
    //Posn();
};

//std::istream & operator>>(std::istream&, Posn&);

#endif