#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include "tile.h"

typedef std::vector<std::vector<Tile>> matrix;

class Board {
    matrix grid;

    public:
        Board();
        void move(const Posn &, const Posn &, bool);
        friend std::ostream &operator<<(std::ostream&, const Board&);


};

std::ostream & operator<<(std::ostream&, const Board&);

#endif