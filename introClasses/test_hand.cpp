#include "hand.h"
#include <iostream>
#include <fstream>

using namespace std;


const int CARDS_TO_READ = 5;

void bubbleSort(int arr[], int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

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

  int deck_contents[CARDS_TO_READ];
  for (int i = 0; i < CARDS_TO_READ; i++) {
    deckFile >> deck_contents[i];

    if (deckFile.eof()) {
      cerr << "File does not contain " << CARDS_TO_READ << " cards!" << endl;
      exit(EXIT_FAILURE);
    } else if (deckFile.fail()) {
      cerr << "Failed to read from file: " << deckFileName << endl;
      exit(EXIT_FAILURE);
    }
  }
  bubbleSort(deck_contents, CARDS_TO_READ);

  Hand hand(new Card(deck_contents[0]),
            new Card(deck_contents[1]),
            new Card(deck_contents[2]),
            new Card(deck_contents[3]),
            new Card(deck_contents[4]));

  // TODO: write code that tests the Hand
  // particularly the isWinningHand() and replaceCard() methods

  Hand winningHand(new Card(1), new Card(2), new Card(3), new Card(4), new Card(5));
  Hand nonWinningHand(new Card(5), new Card(4), new Card(3), new Card(2), new Card(1));

  Card* newCard = new Card(55); // Create a new card to replace the existing card
  Card* discardedCard = hand.replaceCard(newCard);

  //Test is a winning hand
  if (winningHand.isWinningHand()) {
    cout << "Test with a Winning Hand: PASSED" << endl;
  } else {
    cout << "Test with a Winning Hand: FAILED" << endl;
  }
  //Not a winning hand
  if (!nonWinningHand.isWinningHand()) {
    cout << "Test with a Non-Winning Hand: PASSED" << endl;
  } else {
    cout << "Test with a Non-Winning Hand: FAILED" << endl;
  }

  //Discard card 
  if(discardedCard) {
    cout << "Replaced card: " << discardedCard->getNum() << endl;
    delete discardedCard; // to avoid memory leaks
  } else {
    cout << "Invalid index. No card replaced." << endl;
    delete newCard; // Since the card was not used, delete it to avoid memory leaks
  }
  
  hand.print();

  return 0;
}
