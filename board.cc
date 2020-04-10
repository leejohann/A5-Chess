#include "board.h"
#include "piece.h"
#include "state.h"
  
using namespace std;

Board::Board() {
  for (int i = 0; i < 8; i++) {
    vector<Tile> row;
    for (int j = 0; j < 8; j++) {
      row.emplace_back(Tile(Posn{j,i}));
      //cout << "initialized tile" << endl;
    }
    this->grid.emplace_back(row);
  }

  //cout << "grid initialized" << endl;

  // Initialize the board
  this->grid[0][0].setPiece(new Piece{'R', Posn{0,0}});
  this->grid[0][1].setPiece(new Piece{'N', Posn{1,0}});
  this->grid[0][2].setPiece(new Piece{'B', Posn{2,0}});
  this->grid[0][3].setPiece(new Piece{'Q', Posn{3,0}});
  this->grid[0][4].setPiece(new Piece{'K', Posn{4,0}});
  this->grid[0][5].setPiece(new Piece{'B', Posn{5,0}});
  this->grid[0][6].setPiece(new Piece{'N', Posn{6,0}});
  this->grid[0][7].setPiece(new Piece{'R', Posn{7,0}});
  for (unsigned int i = 0; i < this->grid.size(); i++) {
    this->grid[1][i].setPiece(new Piece{'P', Posn{(signed) i,1}});
    this->grid[6][i].setPiece(new Piece{'p', Posn{(signed) i,6}});
  }

  this->grid[7][0].setPiece(new Piece{'r', Posn{0,7}});
  this->grid[7][1].setPiece(new Piece{'n', Posn{1,7}});
  this->grid[7][2].setPiece(new Piece{'b', Posn{2,7}});
  this->grid[7][3].setPiece(new Piece{'q', Posn{3,7}});
  this->grid[7][4].setPiece(new Piece{'k', Posn{4,7}});
  this->grid[7][5].setPiece(new Piece{'b', Posn{5,7}});
  this->grid[7][6].setPiece(new Piece{'n', Posn{6,7}});
  this->grid[7][7].setPiece(new Piece{'r', Posn{7,7}});

  // Initialize observers
  // attach each tile to each of its 8-directional neighbours
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      this->grid[i][j].attach(this);
      //cout << "attached tile to grid" << endl;
      if (i > 0 && j > 0) {
        this->grid[i][j].attach(&this->grid[i-1][j-1]);
        this->grid[i-1][j-1].attach(&this->grid[i][j]);
        //cout << "NW attached" << endl;
      }
      if (i > 0 && j < 7) {
        this->grid[i][j].attach(&this->grid[i-1][j+1]);
        this->grid[i-1][j+1].attach(&this->grid[i][j]);
        //cout << "NE attached" << endl;
      }
      if (i < 7 && j < 7) {
        //cout << "SE: (" << i << "," << j << ")" << endl;
        this->grid[i][j].attach(&this->grid[i+1][j+1]);
        this->grid[i+1][j+1].attach(&this->grid[i][j]);
        //cout << "SE attached" << endl;
      }
      if (i < 7 && j > 0) {
        this->grid[i][j].attach(&this->grid[i+1][j-1]);
        this->grid[i+1][j-1].attach(&this->grid[i][j]);
        //cout << "SW attached" << endl;
      }
      if (i > 0) {
        this->grid[i][j].attach(&this->grid[i-1][j]);
        this->grid[i-1][j].attach(&this->grid[i][j]);
        //cout << "N attached" << endl;
      }
      if (i < 7) {
        this->grid[i+1][j].attach(&this->grid[i][j]);
        this->grid[i][j].attach(&this->grid[i+1][j]);
        //cout << "S attached" << endl;
      }
      if (j > 0) {
        this->grid[i][j].attach(&this->grid[i][j-1]);
        this->grid[i][j-1].attach(&this->grid[i][j]);
        //cout << "W attached" << endl;
      }
      if (j < 7) {
        this->grid[i][j].attach(&this->grid[i][j+1]);
        this->grid[i][j+1].attach(&this->grid[i][j]);
        //cout << "E attached" << endl;
      }
    }
  }
}

void Board::notify(Subject &whoFrom) {
  //cout << "board notify" << endl;
  if (whoFrom.getState().type == StateType::Affirmative) {
    //cout << "removing a piece" << endl;
    Posn dest = whoFrom.getState().destination;
    Posn start = whoFrom.getState().start;
    this->grid[dest.y][dest.x] = this->grid[start.y][start.x];
    this->grid[start.y][start.x].removePiece();
  }
}

// finds the locations of the spaces between the piece and its intended
//   destination
vector<Posn> findPath(char c, const Posn &start, const Posn &dest) {
  vector<Posn> retval;
  //cout << "findPath - start: " << start.x << "," << start.y << endl;
  //cout << "findPath - dest: " << dest.x << "," << dest.y << endl;
  if (c == 'r' || c == 'R' || c == 'p' || c == 'P') {
    //cout << "findPath: rook/pawn" << endl;
    if (start.x == dest.x && start.y < dest.y) {
      for (int i = start.y+1; i < dest.y; i++) retval.emplace_back(Posn{start.x,i});
    }
    else if (start.x == dest.x && start.y > dest.y) {
      for (int i = start.y-1; i > dest.y; i--) retval.emplace_back(Posn{start.x,i});
    }
    else if (start.y == dest.y && start.x < dest.y) {
      for(int i=start.x+1; i<start.y; i++) retval.emplace_back(Posn{i,start.y});
    }
    else if (start.y == dest.y && start.x > dest.y) {
      for(int i=start.x-1; i<start.y; i++) retval.emplace_back(Posn{i,start.y});
    }
  }
  else if (c == 'b' || c == 'B') {
    if (start.x < dest.x && start.y < dest.y) {
      for (int i=start.x+1; i<dest.x; i++) {
        retval.emplace_back(Posn{i,start.y-start.x+i});
      }
    }
    else if (start.x < dest.x && start.y > dest.y) {
      for (int i=start.x+1, j=start.y-1; i<dest.x; i++, j--) {
        retval.emplace_back(Posn{i,j});
      }
    }
    else if (start.x > dest.x && start.y > dest.y) {
      for (int i=start.x-1, j=start.y-1; i>dest.x; i--, j--) {
        retval.emplace_back(Posn{i,j});
      }
    }
    else if (start.x > dest.x && start.y < dest.y) {
      for (int i=start.x-1, j=start.y+1; i>dest.x; i--, j++) {
        retval.emplace_back(Posn{i,j});
      }
    }
  }
  else if (c == 'q' || c == 'Q') {
    if (start.x < dest.x && start.y < dest.y) {
      for (int i=start.x+1; i<dest.x; i++) {
        retval.emplace_back(Posn{i,start.y-start.x+i});
      }
    }
    else if (start.x < dest.x && start.y > dest.y) {
      for (int i=start.x+1, j=start.y-1; i<dest.x; i++, j--) {
        retval.emplace_back(Posn{i,j});
      }
    }
    else if (start.x > dest.x && start.y > dest.y) {
      for (int i=start.x-1, j=start.y-1; i>dest.x; i--, j--) {
        retval.emplace_back(Posn{i,j});
      }
    }
    else if (start.x > dest.x && start.y < dest.y) {
      for (int i=start.x-1, j=start.y+1; i>dest.x; i--, j++) {
        retval.emplace_back(Posn{i,j});
      }
    }
    else if (start.x == dest.x && start.y < dest.y) {
      for (int i = start.y+1; i < dest.y; i++) retval.emplace_back(Posn{start.x,i});
    }
    else if (start.x == dest.x && start.y > dest.y) {
      for (int i = start.y-1; i > dest.y; i--) retval.emplace_back(Posn{start.x,i});
    }
    else if (start.y == dest.y && start.x < dest.y) {
      for(int i=start.x+1; i<start.y; i++) retval.emplace_back(Posn{i,start.y});
    }
    else if (start.y == dest.y && start.x > dest.y) {
      for(int i=start.x-1; i<start.y; i++) retval.emplace_back(Posn{i,start.y});
    }
  }
  else if (c == 'n' || c == 'N') {
    if (start.x == dest.x-2) {
      retval.emplace_back(Posn{start.x+1,start.y});
      retval.emplace_back(Posn{start.x+2,start.y});
    }
    else if (start.x == dest.x+2) {
      retval.emplace_back(Posn{start.x-1,start.y});
      retval.emplace_back(Posn{start.x-2,start.y});
    }
    else if (start.y == dest.y-2) {
      retval.emplace_back(Posn{start.x,start.y+1});
      retval.emplace_back(Posn{start.x,start.y+2});
    }
    else if (start.y == dest.y+2) {
      retval.emplace_back(Posn{start.x,start.y-1});
      retval.emplace_back(Posn{start.x,start.y-2});
    }
  }
  return retval;
}

// move(start, dest, isWhite) moves the piece located at start to dest
//   isWhite indicates if it is the turn of the player playing for White or not
//   if the move fails due to violating the rules, an InvalidMove exception 
//   will be thrown
// Effects: Mutates this->grid
// Efficiency: O(n)
// Requires: 0 <= start.x, start.y, dest.x, dest.y <= 7
void Board::move(const Posn &start, const Posn &dest, bool isWhite) { 
  if (this->grid[start.y][start.x].isOccupied() == false) throw InvalidMove{};
  if ((this->grid[start.y][start.x].getColour() == Colour::White && isWhite) ||
      (this->grid[start.y][start.x].getColour() == Colour::Black && !isWhite)){
    vector<Posn> path = findPath(this->grid[start.y][start.x].getPiece()->getName(),start,dest);
    this->grid[start.y][start.x].setState(State{dest, start, path, StateType::Request,
        this->grid[start.y][start.x].getPiece()->getName()});
    //cout << "requesting from board" << endl;
    this->grid[start.y][start.x].notifyObservers();
    capture(start, dest, isWhite);
  } else throw InvalidMove{};
}

// capture(start, dest, isWhite) checks if a move would result in a capture, returns void
//    if not, captures piece on dest tile, and removes piece from dest tile
void Board::capture(const Posn &start, const Posn &dest, bool isWhite) {
  // if dest tile is unoccupied, return void
  if (this->grid[dest.y][dest.x].isOccupied() ==  false) { 
    cout << "dest tile is unoccupied, no capture possible" << endl;
    return; }
  // check if start piece is player's piece, dest piece is opponent's piece
  if (this->grid[start.y][start.x].isOccupied() == false) throw InvalidMove{};
  if (isWhite) {
    if ((this->grid[start.y][start.x].getColour() == Colour::White) &&
        (this->grid[dest.y][dest.x].getColour() == Colour::White)) {
          cout << "you're trying to capture your own piece (white)" << endl;
          throw InvalidMove{};
        }
  } if (!isWhite) {
    if ((this->grid[start.y][start.x].getColour() == Colour::Black) &&
        (this->grid[dest.y][dest.x].getColour() == Colour::Black)) {
          cout << "you're trying to capture your own piece (black)" << endl;
          throw InvalidMove{};
        }
  } // removing piece from dest tile, capture piece
  this->grid[dest.y][dest.x].pieceCaptured();

}

// setupCheck() returns a boolean value indicating if the following are true:
//    1. There is exactly 1 black K and 1 white K on the board
//    2. There are no Pawns on the first or last row of the board
//    3. Neither of the Ks are in check
bool Board::setupCheck() {
  // checking 1
  int blackK = 0;
  int whiteK = 0; 
  bool pawnCheck = false;
  bool kingInCheck = false;
  for (int i=0; i<8; i++) {
    for (int j=0; j<8; j++) {
      if (this->grid[i][j].isOccupied()) {
        // checking condition 1
        if (this->grid[i][j].getPiece()->getName() == 'K') {
          ++whiteK;
        } else if (this->grid[i][j].getPiece()->getName() == 'k') {
          ++blackK;
        }
        // checking condition 2
        if (i==0 || i==7) {
          if ((this->grid[i][j].getPiece()->getName() == 'P') ||
              (this->grid[i][j].getPiece()->getName() == 'p')) {
                pawnCheck = true;
              }
        }
      }
    }
  } 
  // check condition 3
  if (blackK==1 && whiteK==1 && !pawnCheck && !kingInCheck) { return true; }
  else {
    cout << "There are " << blackK << " black Kings." << endl;
    cout << "There are " << whiteK << " white Kings." << endl;
    if (pawnCheck) {
      cout << "There is a pawn on the first/last row of the board." << endl;
    } if (kingInCheck) {
      cout << "A King is in check." << endl;
    }
  } return false;
}

// findPiece(char c) finds the piece on the board and returns its Posn
void Board::findPiece(char c, Posn &start) {
  for (int i=0; i<8; ++i) {
    for (int j=0; j<8; ++j) {
      if (this->grid[i][j].getPiece()->getName() == c) {
        start = this->grid[i][j].getPiece()->getPos();
        return;
      }
    }
  } cout << "Piece " << c << " is not on the Board." << endl;
}

// removePiece(Posn &) removes the piece at pos, if there is no piece at pos, it does nothing
void Board::removePiece(Posn &pos) {
  if (this->grid[pos.x][pos.y].isOccupied()) {
    this->grid[pos.x][pos.y].removePiece();
  } else { return; }
}

// operator<<(out, b) outputs the board to out int the following format:
//   black pieces are represented by capital letters
//   white pieces are represented by lower case letters
//   free white spaces are blank spaces
//   free black spaces are underscores
// Requires: none
// Effects: outputs to out
// Efficiency: O(n^2)
ostream & operator<<(ostream &out, const Board &b) {
  for (unsigned int i = 0; i < b.grid.size(); i++) {
    for (unsigned int j = 0; j < b.grid[i].size(); j++) {
      if(b.grid[i][j].isOccupied()) out << b.grid[i][j];
      else if (i % 2 != j % 2) out << "_";
      else out << " ";
    }
    out << endl;
  }
  return out;
}