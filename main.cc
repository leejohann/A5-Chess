#include "board.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
  Board b;
  cout << b << endl;
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
      b.move(Posn{startx,starty}, Posn{destx,desty}, isWhite);
      isWhite = !isWhite;
      cout << b << endl;
    }
  }

  return 0;
}