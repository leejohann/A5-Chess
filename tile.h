#ifndef TILE_H
#define TILE_H

#include "subject.h"
#include <iostream>
#include <vector>

enum Colour;
class Piece;

class Tile : public Subject {
  bool occupied;
  Piece *piece;
  

  public:
    Tile();
    void setPiece(Piece*);
    void removePiece();
    bool isOccupied() const;
    
    const Colour getColour() const;

    // accessors
    Piece * getPiece() const;

    friend std::ostream& operator<<(std::ostream&, const Tile&);
};

std::ostream & operator<<(std::ostream&, const Tile&);

#endif