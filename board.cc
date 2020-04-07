#include "board.h"
#include "piece.h"
#include "state.h"
  
using namespace std;

Board::Board() {
  for (int i = 0; i < 8; i++) {
    vector<Tile> row;
    for (int j = 0; j < 8; j++) {
      row.emplace_back(Tile());
    }
    this->grid.emplace_back(row);
  }

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
  // Each piece sends notifications to each piece in its range of motion

  // (0,0) : Black Rook 1
  for (unsigned int i = 1; i < 8; i++) {
    this->grid[0][0].attach(this->grid[0][i].getPiece());
  }
  this->grid[0][0].attach(this->grid[1][0].getPiece());
  // (0,1) : Black Knight 1
  this->grid[0][1].attach(this->grid[1][3].getPiece());
  // (0,2) : Black Bishop 1
  this->grid[0][2].attach(this->grid[1][1].getPiece());
  this->grid[0][2].attach(this->grid[1][3].getPiece());
  // (0,3) : Black Queen
  this->grid[0][3].attach(this->grid[0][2].getPiece());
  this->grid[0][3].attach(this->grid[0][4].getPiece());
  this->grid[0][3].attach(this->grid[1][2].getPiece());
  this->grid[0][3].attach(this->grid[1][3].getPiece());
  this->grid[0][3].attach(this->grid[1][4].getPiece());
  // (0,4) : Black King
  this->grid[0][4].attach(this->grid[0][3].getPiece());
  this->grid[0][4].attach(this->grid[0][5].getPiece());
  this->grid[0][4].attach(this->grid[1][3].getPiece());
  this->grid[0][4].attach(this->grid[1][4].getPiece());
  this->grid[0][4].attach(this->grid[1][5].getPiece());
  // (0,5) : Black Bishop 2
  this->grid[0][5].attach(this->grid[1][4].getPiece());
  this->grid[0][5].attach(this->grid[1][6].getPiece());
  // (0,6) : Black Knight 2
  this->grid[0][6].attach(this->grid[1][4].getPiece());
  // (0,7) : Black Rook 2
  for (int i = 0; i < 7; i++) {
    this->grid[0][7].attach(this->grid[0][i].getPiece());
  }
  this->grid[0][6].attach(this->grid[1][7].getPiece());

  // (7,0) : White Rook 1
  this->grid[7][0].attach(this->grid[6][0].getPiece());
  this->grid[7][0].attach(this->grid[7][1].getPiece());
  // (7,1) : White Knight 1
  this->grid[7][1].attach(this->grid[6][3].getPiece());
  // (7,2) : White Bishop 1
  this->grid[7][2].attach(this->grid[6][1].getPiece());
  this->grid[7][2].attach(this->grid[6][3].getPiece());
  // (7,3) : White Queen 
  this->grid[7][3].attach(this->grid[7][2].getPiece());
  this->grid[7][3].attach(this->grid[6][2].getPiece());
  this->grid[7][3].attach(this->grid[6][3].getPiece());
  this->grid[7][3].attach(this->grid[6][4].getPiece());
  this->grid[7][3].attach(this->grid[7][4].getPiece());
  // (7,4) : White King
  this->grid[7][4].attach(this->grid[7][3].getPiece());
  this->grid[7][4].attach(this->grid[7][5].getPiece());
  this->grid[7][4].attach(this->grid[6][3].getPiece());
  this->grid[7][4].attach(this->grid[6][4].getPiece());
  this->grid[7][4].attach(this->grid[6][5].getPiece());
  // (7,5) : White Bishop 2
  this->grid[7][5].attach(this->grid[6][4].getPiece());
  this->grid[7][5].attach(this->grid[6][6].getPiece());
  // (7,6) : White Knight 2
  this->grid[7][6].attach(this->grid[6][3].getPiece());
  // (7,7) : White Rook 2
  this->grid[7][7].attach(this->grid[6][7].getPiece());
  this->grid[7][7].attach(this->grid[7][6].getPiece());
}

// finds the locations of the spaces between the piece and its intended
//   destination
vector<Posn> findPath(char c, const Posn &start, const Posn &dest) {
  vector<Posn> retval;
  if (c == 'r' || c == 'R') {
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
  // Special case: moving a pawn
  // White pawn
  if (this->grid[start.y][start.x].getPiece()->getName() == 'p') {
    //cout << "pawn" << endl;
    // Check range : movement
    if (start.x == dest.x && (start.y == dest.y+1 || start.y == dest.y+2)) {
      // Check player's turn
      if ((this->grid[start.y][start.x].getColour() == Colour::White && isWhite) ||
          (this->grid[start.y][start.x].getColour() == Colour::Black && !isWhite)) { 
        this->grid[dest.y][dest.x] = this->grid[start.y][start.x];
        this->grid[start.y][start.x].removePiece();
      } else {
        //cout << "wrong colour" << endl;
        throw InvalidMove{};}
    }
    // Check range : capture
    else if (start.y == dest.y+2 && (start.x == dest.x-2 || start.x == dest.x+2)) {
      // Check for piece to capture
      Tile *capture;
      if (start.x == dest.x-2) capture = &this->grid[start.y-1][start.x+1];
      else if (start.x == dest.x+2) capture = &this->grid[start.y-1][start.x-1];
      if (capture->isOccupied() == false) throw InvalidMove{};
      else capture->removePiece();
    }
    else {
      //cout << "invalid dest" << endl;
      throw InvalidMove{};}
    return;
  }
  // Black Pawn
  else if (this->grid[start.y][start.x].getPiece()->getName() == 'P') {
    //cout << "black pawn" << endl;
    //cout << "pawn" << endl;
    // Check range : movement
    if (start.x == dest.x && (start.y == dest.y-1 || start.y == dest.y-2)) {
      // Check player's turn
      if ((this->grid[start.y][start.x].getColour() == Colour::White && isWhite) ||
          (this->grid[start.y][start.x].getColour() == Colour::Black && !isWhite)) { 
        this->grid[dest.y][dest.x] = this->grid[start.y][start.x];
        this->grid[start.y][start.x].removePiece();
      } else {
        //cout << "wrong colour" << endl;
        throw InvalidMove{};}
    }
    // Check range : capture
    else if (start.y == dest.y-2 && (start.x == dest.x-2 || start.x == dest.x+2)) {
      // Check for piece to capture
      Tile *capture;
      if (start.x == dest.x-2) capture = &this->grid[start.y+1][start.x+1];
      else if (start.x == dest.x+2) capture = &this->grid[start.y+1][start.x-1];
      if (capture->isOccupied() == false) throw InvalidMove{};
      else capture->removePiece();
    }
    else {
      //cout << "invalid dest" << endl;
      throw InvalidMove{};}
    return;
  }

  // path of tiles between start and dest (not including start or dest)
  vector<Posn> path = findPath(this->grid[start.y][start.x].getPiece()->getName(), start, dest);

  // tests if the chosen path is obstructed (for all pieces other than knight)
  if (this->grid[start.y][start.x].getPiece()->getName() != 'n' &&
      this->grid[start.y][start.x].getPiece()->getName() != 'N') {
    for (unsigned int i = 0; i < path.size(); i++) {
      if (this->grid[path[i].y][path[i].x].isOccupied()) throw InvalidMove{};
    }
  }

  // check if the player is chosing a piece of their colour, with a destination
  //   in the appropriate range
  if (((this->grid[start.y][start.x].getColour() == Colour::White && isWhite) ||
      (this->grid[start.y][start.x].getColour() == Colour::Black && !isWhite)) &&
      this->grid[start.y][start.x].getPiece()->inRange(dest)) { 
    this->grid[dest.y][dest.x] = this->grid[start.y][start.x];
    //cout << "new piece set" << endl;
    this->grid[start.y][start.x].removePiece();
    //cout << "old piece removed" << endl;
  } else throw InvalidMove{};
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