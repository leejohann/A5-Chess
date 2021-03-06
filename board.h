#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include "tile.h"
#include "observer.h"

typedef std::vector<std::vector<Tile>> matrix;

class InvalidMove {};

class Board : public Observer {
    matrix grid;

    public:
        Board();
        void move(const Posn &, const Posn &, bool);
        friend std::ostream &operator<<(std::ostream&, const Board&);
        virtual void notify(Subject &);


};

std::ostream & operator<<(std::ostream&, const Board&);

#endif