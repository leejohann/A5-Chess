#ifndef TILE_H
#define TILE_H

#include "subject.h"
#include "observer.h"
#include <iostream>
#include <vector>

enum Colour;
class Piece;

class Tile : public Subject, public Observer {
  bool occupied;
  Piece *piece;
  Posn pos{0,0};
  

  public:
    //Tile();
    Tile(Posn);
    Tile(const Tile&);
    void setPiece(Piece*);
    void removePiece();
    bool isOccupied() const;
    void pieceCaptured();
    
    virtual void notify(Subject&);
    virtual Info getInfo() const;

    // accessors
    Piece * getPiece() const;
    const Colour getColour() const;
    Posn getPos() const;

    friend std::ostream& operator<<(std::ostream&, const Tile&);
};

std::ostream & operator<<(std::ostream&, const Tile&);

#endif