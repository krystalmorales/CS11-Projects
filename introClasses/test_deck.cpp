#include "deck.h"
#include <iostream>
#include <fstream>

using namespace std;


int main(int argc, char* argv[]) {
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " filename" << endl;
    exit(EXIT_FAILURE);
  }
  string deckFileName(argv[1]);

  ifstream deckFile(deckFileName);
  if (deckFile.fail()) {
    cerr << "Failed to open deck file: " << deckFileName << endl;
    exit(EXIT_FAILURE);
  }

  int deck_contents[Deck::MAX_DECK_SIZE];
  for (int i = 0; i < Deck::MAX_DECK_SIZE; i++) {
    deckFile >> deck_contents[i];

    if (deckFile.eof()) {
      cerr << "File does not contain " << Deck::MAX_DECK_SIZE << " cards!" << endl;
      exit(EXIT_FAILURE);
    } else if (deckFile.fail()) {
      cerr << "Failed to read from file: " << deckFileName << endl;
      exit(EXIT_FAILURE);
    }
  }


  Deck deck(deckFileName);

  for (int i = 0; i < Deck::MAX_DECK_SIZE; i++) {
    if (deck.isEmpty()) {
      cout << "FAILED: deck is prematurely empty at card " << i << endl;
    }

    Card* card = deck.draw();

    if (card == NULL) {
      cout << "FAILED: card " << i << " returned NULL!  Expected: "
           << deck_contents[i] << endl;

    } else if (card->getNum() != deck_contents[i]) {
      cout << "FAILED: card " << i << " did not match! Got " << card->getNum()
           << " but expected " << deck_contents[i] << endl;
    }

    if (card != NULL) {
      delete card;
    }
  }

  if (!deck.isEmpty()) {
    cout << "FAILED: deck is *not* empty after drawing "
         << Deck::MAX_DECK_SIZE << " cards!" << endl;
  }

  cout << "Failed tests are listed above. If there is no output, "
       << "then it all succeeded!" << endl;
  return 0;
}
