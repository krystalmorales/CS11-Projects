#include "game.h"
#include <iostream>

using namespace std;


int main(int argc, char* argv[]) {
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " filename" << endl;
    exit(EXIT_FAILURE);
  }

  Game racko(argv[1]);
  racko.play();

  return 0;
}
