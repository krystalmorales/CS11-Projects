#include "card.h"
#include "hand.h"
#include <iostream>

using namespace std;


Hand::Hand(Card* c1, Card* c2, Card* c3, Card* c4, Card* c5) {
  cards[0] = c1;
  cards[1] = c2;
  cards[2] = c3;
  cards[3] = c4;
  cards[4] = c5;
}


Hand::~Hand() {
  for (int i = 0; i < HAND_SIZE; i++) {
    delete cards[i];
  }
}


bool Hand::isWinningHand() {
  for (int i = 1; i < HAND_SIZE; i++) {
    if (cards[i] == nullptr || cards[i]->getNum() <= cards[i - 1]->getNum()) {
      return false;
    }
  }
  return true;
}


Card* Hand::replaceCard(Card* newCard) {
   int index;

  while (true) {
    cout << "\nEnter the index of the card you'd like to discard: ";
    cin >> index;

    if (index >= 0 && index < HAND_SIZE) {
      break; // Valid input, exit the loop
    }
  }
  
  Card* discardedCard = cards[index];
  cards[index] = newCard;
  return discardedCard;
}


void Hand::print() {
  for (int i = 0; i < HAND_SIZE; i++) {
    if (cards[i] == NULL) {
      cerr << "ERROR: hand does not have " << HAND_SIZE << " cards!" << endl;
      exit(EXIT_FAILURE);
    }
  }

  // print Top Edge
  for (int i = 0; i < HAND_SIZE; i++) {
    if (i > 0) {
      cout << "  ";
    }
    cout << cards[i]->getTopEdge();
  }
  cout << endl;

  // print Blank Line
  for (int i = 0; i < HAND_SIZE; i++) {
    if (i > 0) {
      cout << "  ";
    }
    cout << cards[i]->getBlankLine();
  }
  cout << endl;

  // print Number Line
  for (int i = 0; i < HAND_SIZE; i++) {
    if (i > 0) {
      cout << "  ";
    }
    cout << cards[i]->getNumberLine();
  }
  cout << endl;

  // print Blank Line
  for (int i = 0; i < HAND_SIZE; i++) {
    if (i > 0) {
      cout << "  ";
    }
    cout << cards[i]->getBlankLine();
  }
  cout << endl;

  // print Bottom Edge
  for (int i = 0; i < HAND_SIZE; i++) {
    if (i > 0) {
      cout << "  ";
    }
    cout << cards[i]->getBottomEdge();
  }
  cout << endl;

  // print index numbers
  for (int i = 0; i < HAND_SIZE; i++) {
    cout << "   ";
    if (i > 0) {
      cout << "    ";
    }
    cout << i;
  }
  cout << endl;
}
