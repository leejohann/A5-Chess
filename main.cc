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
  }

  return 0;
}