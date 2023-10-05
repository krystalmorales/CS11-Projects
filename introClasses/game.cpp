#include "game.h"
#include <iostream>

using namespace std;


Game::Game(string deckFileName) {
  deck = new Deck(deckFileName);
  for (int i = 0; i < NUM_PLAYERS; i++) {
    hands[i] = new Hand(deck->draw(),
                        deck->draw(),
                        deck->draw(),
                        deck->draw(),
                        deck->draw());
  }
  discard = new DiscardPile(deck->draw());
}


Game::~Game() {
  for (int i = 0; i < NUM_PLAYERS; i++) {
    delete hands[i];
  }
  delete discard;
  delete deck;
}


void Game::play() {
  int playerNum = 0;
  cout << "PLAYER " << playerNum + 1 << "'s TURN:" << endl;
  takeTurn(playerNum);
  cout << endl;

  while (!didPlayerWin(playerNum) && !deck->isEmpty()) {
    playerNum = (playerNum + 1) % NUM_PLAYERS;
    cout << "PLAYER " << playerNum + 1 << "'s TURN:" << endl;
    takeTurn(playerNum);
    cout << endl;
  }

  if (didPlayerWin(playerNum)) {
    cout << "CONGRATULATIONS PLAYER " << playerNum + 1 << "! YOU WIN!!" << endl;
  } else {
    // deck is empty
    cout << "The deck is empty. IT'S A TIE!" << endl;
  }
}


void Game::takeTurn(int playerNum) {
  if (playerNum < 0 || playerNum >= NUM_PLAYERS) {
    cerr << "Invalid player number: " << playerNum << endl;
    exit(EXIT_FAILURE);
  }

  cout << "Your hand:" << endl;
  hands[playerNum]->print();
  cout << "\n";
  cout << "Discard pile:" << endl;
  discard->print();

  int choice;
  
  cout << "\n";

  cout << "Would you like to" << endl;
  cout << " 1. take the top discard?" << endl;
  cout << " 2. draw from the deck?" << endl;
  cout << "Enter the number for your choice: ";

  while(true) {
  cin >> choice;

  if (choice == 1) {
      takeDiscard(playerNum);
      break;
    } else if (choice == 2) {
      drawFromDeck(playerNum);
      break;
    } else {
      cout << "Enter the number for your choice: ";
    }
  }
}


void Game::takeDiscard(int playerNum) {
  cout << endl;
  if (playerNum < 0 || playerNum >= NUM_PLAYERS) {
    cerr << "Invalid player number: " << playerNum << endl;
    exit(EXIT_FAILURE);
  }
  hands[playerNum]->print();

  Card *discardedCard = discard->takeDiscard();
  Card *replacedCard = hands[playerNum]->replaceCard(discardedCard);
  discard->discard(replacedCard);
  cout << "\n";
  cout << "Your new hand:" << endl;
  hands[playerNum]->print();
}


void Game::drawFromDeck(int playerNum) {
  if (playerNum < 0 || playerNum >= NUM_PLAYERS) {
    cerr << "Invalid player number: " << playerNum << endl;
    exit(EXIT_FAILURE);
  }
  Card* drawnCard = deck->draw();
  cout << "\n";
  cout << "You drew:" << endl;
  cout << drawnCard->toString() << endl;

  string choice;
  cout << "Would you like to keep this card? (y/n) ";
  cin >> choice;
  cout << "\n";

  if(choice == "y") {
    hands[playerNum]->print();
    Card *replacedCard = hands[playerNum]->replaceCard(drawnCard);
    discard->discard(replacedCard);
    cout << "\nYour new hand:" << endl;
    hands[playerNum]->print();
  } else if (choice == "n") {
    discard->discard(drawnCard);
    cout << "\n";
    cout << "Your new hand:" << endl;
    hands[playerNum]->print();
  }
}


bool Game::didPlayerWin(int playerNum) {
  if (playerNum < 0 || playerNum >= NUM_PLAYERS) {
    cerr << "Invalid player number: " << playerNum << endl;
    exit(EXIT_FAILURE);
  }

  return hands[playerNum]->isWinningHand();
}
