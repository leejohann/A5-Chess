#include "board.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
  Board b;
  cout << b << endl << "it is White's turn" << endl;
  string cmd;
  bool isWhite = true;
  while (true) {
    cin >> cmd;
    if (cmd == "quit" || cmd == "q") break;
    else if (cmd == "move") {
      int startx, starty, destx, desty;
      cin >> startx;
      cin >> starty;
      cin >> destx;
      cin >> desty;
      //cout << "input taken" << endl;
      try {
        b.move(Posn{startx,starty}, Posn{destx,desty}, isWhite);
        isWhite = !isWhite;
      } catch (InvalidMove&) {
        cout << "that move is invalid; try again" << endl;
      }
      cout << b << endl;
      if (isWhite) cout << "it is White's turn" << endl;
      else cout << "it is Black's turn" << endl;
    }
    else if (cmd == "setup") {
      string mode, dest, colour;
      char piece;
      while (true) {
        cin >> mode;
        if (mode == "done") {
          if (b.setupCheck()) break;
          else { 
            cout << "There is something wrong, cannot exit setup mode." << endl;
          }
        }
        else if (mode == "+") {
          cin >> piece;
          cin >> dest;
          Posn destPos{0,0};
          Posn startPos{0,0};
          // convert dest to Posn
          b.findPiece(piece, startPos);
          // move(startPos, destPos, isWhite); ahhhh !!!
        } else if (mode == "-") {
          cin >> dest;
          Posn destPos{0,0};
          // convert dest to Posn
          b.removePiece(destPos);
        } else if (mode == "=") {
          cin >> colour;
          if ((colour == "black") && isWhite) { isWhite = !isWhite; }
          else if ((colour == "white" && !isWhite)) { isWhite = !isWhite; }
          cout << "I am changing colours." << endl;
          }
        } cout << b << endl;
        if (isWhite) cout << "it is White's turn" << endl;
        else cout << "it is Black's turn" << endl;
      }
    }
  return 0;
}