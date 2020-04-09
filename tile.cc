#include "tile.h"
#include "piece.h"
#include "board.h"

using namespace std;

//Tile::Tile() : occupied{false}, piece{nullptr} {}
Tile::Tile(Posn p) {
  //cout << "tile ctor" << endl;
  this->occupied = false;
  this->piece = nullptr;
  this->pos = p;
  //cout << "bottom tile ctor" << endl;
}

Tile::Tile(const Tile &other) {
  //cout << "tile copy ctor" << endl;
  this->occupied = other.isOccupied();
  this->piece = other.getPiece();
  this->pos = other.getPos();
  //cout << "bottom tile copy ctor" << endl;
}

void Tile::setPiece(Piece *p) {
  this->piece = p;
  this->occupied = true;

  // Make the piece an observer of this tile
  this->attach(this->piece);
}

ostream & operator<<(ostream &out, const Tile &t) {
  if (t.occupied) out << t.piece->getName();
  return out;
}

void Tile::removePiece() {
  this->occupied = false;
  //if(this->piece != nullptr) delete this->piece;
  //cout << "pointer deleted" << endl;
}

bool inPath(vector<Posn> &path, Posn pos) {
  //cout << "top of inPath" << endl;
  for (unsigned int i = 0; i < path.size(); i++) {
    if (path[i].x == pos.x && path[i].y == pos.y) return true;
  }
  return false;
}

void Tile::notify(Subject& whoFrom) {
  /*
  cout << "current tile: " << this->pos.x << "," << this->pos.y << endl;
  cout << "type: ";
  if (whoFrom.getState().type == StateType::Request) cout << "request" << endl;
  else if (whoFrom.getState().type == StateType::Affirmative) cout << "affirm" << endl;
  else if (whoFrom.getState().type == StateType::Negative) cout << "neg" << endl;
  else if (whoFrom.getState().type == StateType::Reply) cout << "reply" << endl;
  else cout << "none" << endl;*/

  if (whoFrom.getState().type == StateType::Request) {
    
    //cout << "Tile: Request" << endl;
    
    //cout << "path found :";
    //for (unsigned int i = 0; i < whoFrom.getState().path.size(); i++) cout << whoFrom.getState().path[i].x << "," << whoFrom.getState().path[i].y << " ";
    //cout << "]" << endl;
    if (whoFrom.getState().destination == this->getPos()){
      //cout << "Tile: Request - destination reached" << endl;
      State newState = whoFrom.getState();
      newState.type = StateType::Affirmative;
      this->setState(newState);
      //cout << "Tile: Request - destination reached - state set" << endl;
      this->notifyObservers();
    }
    else if (!whoFrom.getState().path.empty() && this->pos == whoFrom.getState().path.front()) {
      //cout << "Tile: Request - on path" << endl;
      if (this->occupied && whoFrom.getState().name != 'n' &&
          whoFrom.getState().name != 'N') { //cout << "dest occupied" << endl;
            throw InvalidMove{};}
      State newState = whoFrom.getState();
      // erase this tile from the path
      newState.path.erase(newState.path.begin()); 
      this->setState(newState);
      this->notifyObservers();
    }
    else {
      //cout << "Tile: Request - off path" << endl;
      State newState = this->getState();
      newState.type = StateType::Negative;
      this->setState(newState);
      //cout << "Tile: Request - off path - state set" << endl;
      //this->notifyObservers();
    }
  }
}

Info Tile::getInfo() const {
  //cout << "Tile getInfo - Pos.x: " << this->pos.x << endl;
  if (this->piece) return this->piece->getInfo();
  else return Info{this->pos, ' '};
}

bool Tile::isOccupied() const {
  return occupied;
}

bool isCapital(char c) {
  if (c >= 65 && c <= 90) {
    /*cout << "capital: ";
    int num = c;
    cout << num << endl;*/
    return true;
  }
  else {
    /*cout << "lower case: ";
    int num = c;
    cout << num << endl;*/
    return false;
  }
}

const Colour Tile::getColour() const {
  if (this->occupied) {
    if (isCapital(this->piece->getName())) return Colour::Black;
    else return Colour::White;
  }
  else return Colour::None;
}

Piece * Tile::getPiece() const { return this->piece; }
Posn Tile::getPos() const { return this->pos; }